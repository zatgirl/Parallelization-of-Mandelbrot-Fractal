#include <iostream>
#include <mpi.h>
#include <complex>
#include <vector>
#include "EasyBMP.h"
#include "MathHelpers.h"
#define DEF_MAX_ITERATIONS 1000

/// <summary>
/// Calcula o número de iterações necessárias para determinar se um ponto do plano complexo
/// pertence ao conjunto de Mandelbrot, iterando sobre a fórmula z(n+1) = z(n)^2 + c, onde z(0) = c
/// </summary>
/// <param name="point"></param>
/// <param name="maxIterations"></param>
/// <returns></returns>
int mandelbrot(const std::complex<double>& point, int maxIterations) {
    std::complex<double> z = point;
    for (int i = 0; i < maxIterations; ++i) {
        if (std::abs(z) > 2.0) {
            return i;
        }
        z = z * z + point;
    }
    return maxIterations;
}

std::vector<int> calculate_mandelbrot(Vector2 start, Vector2 end, Int2 imgDim, int max_iter, int start_row, int end_row) {
    Vector2 step = Vector2(((end.x - start.x) / imgDim.x), ((end.y - start.y) / imgDim.y));
    
    std::vector<int> result(imgDim.x * (end_row - start_row));

    for (int i = start_row; i < end_row; ++i) {
        double y = start.y + i * step.y;
        for (int j = 0; j < imgDim.x; ++j) {
            double x = start.x + j * step.x;
            std::complex<double> c(x, y);
            result[(i - start_row) * imgDim.x + j] = mandelbrot(c, max_iter);
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /// Define os parâmetros do conjunto de Mandelbrot
    Vector2 start = Vector2(-2.0, -1.5);
    Vector2 end = Vector2(1.0, 1.5);

    /// Define o tamanho da imagem = matriz
    Int2 imgDim = Int2(800, 600);

    /// Divide a imagem (trabalho) em fatias iguais para cada processo
    int chunckSize = imgDim.y / size;
    int startRow = rank * chunckSize;
    int endRow = startRow + chunckSize;
 
    /// Calcula a fatia recebida, todos os processos vao trabalhar
    std::vector<int> local_result = calculate_mandelbrot(start, end, imgDim, DEF_MAX_ITERATIONS, startRow, endRow);

    /// Coleta os resultados de todos os processos no processo raiz
    std::vector<int> gathered_result(imgDim.x * imgDim.y);
    MPI_Gather(&local_result[0], local_result.size(), MPI_INT, &gathered_result[0], local_result.size(), MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        BMP image;
        image.SetSize(imgDim.x, imgDim.y);

        RGBApixel black;
        black.Red = 0;
        black.Green = 0;
        black.Blue = 0;

        RGBApixel white;
        white.Red = 255;
        white.Green = 255;
        white.Blue = 255;

        for (int i = 0; i < imgDim.y; ++i) {
            for (int j = 0; j < imgDim.x; ++j) {
                int index = i * imgDim.x + j;
                int value = gathered_result[index];
                RGBApixel color;

                if (value == DEF_MAX_ITERATIONS) {
                    color = black;
                }
                else {
                    int red = (value * 10) % 256;
                    int green = (value * 5) % 256;
                    int blue = (value * 2) % 256;
                    color.Red = red;
                    color.Green = green;
                    color.Blue = blue;
                }

                image.SetPixel(j, i, color);
            }
        }

        image.WriteToFile("mandelbrot.bmp");
    }

    MPI_Finalize();
    return 0;
}
