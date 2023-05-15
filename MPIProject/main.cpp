#include <iostream>
#include <mpi.h>
#include <complex>
#include <vector>
#include "EasyBMP.h"
#include "MathHelpers.h"
#include "Mandelbrot.h"
#define DEF_MAX_ITERATIONS 1000
#define DEF_IMAGE_WIDTH    800
#define DEF_IMAGE_HEIGHT   600

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    double startTime = MPI_Wtime();
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /// Define os parâmetros do conjunto de Mandelbrot, plano complexo
    dvec2 start = dvec2(-2.0, -1.5);
    dvec2 end   = dvec2( 1.0,  1.5);

    /// Define o tamanho da imagem = matriz
    ivec2 imgDim = ivec2(DEF_IMAGE_WIDTH, DEF_IMAGE_HEIGHT);

    /// Divide a imagem (trabalho) em fatias iguais (linhas) para cada processo
    int chunckSize = imgDim.y / size;
    /// Calcula a linha inicial e a linha final com base no rank atual
    int startRow = rank * chunckSize;
    int endRow   = startRow + chunckSize;
 
    /// Calcula a fatia recebida, todos os processos vao trabalhar
    double startTimeProcess = MPI_Wtime();
    std::vector<int> local_result = CalculateMandelbrot(start, end, imgDim, DEF_MAX_ITERATIONS, startRow, endRow);
    double endTimeProcess = MPI_Wtime();
    double timeProcess = endTimeProcess - startTimeProcess;
    std::cout << "O processo " << rank << " levou " << timeProcess << " segundos." << std::endl;

    /// Coleta os resultados de todos os processos no processo raiz
    std::vector<int> gathered_result(imgDim.x * imgDim.y);
    MPI_Gather(&local_result[0], local_result.size(), MPI_INT, &gathered_result[0], local_result.size(), MPI_INT, 0, MPI_COMM_WORLD);

    double endTime = MPI_Wtime();
    double time = endTime - startTime;    

    if (rank == 0) {
        /// Cria uma imagem com base na matriz de pixels iterados
        BMP image;
        image.SetSize(imgDim.x, imgDim.y);

        for (int row = 0; row < imgDim.y; ++row) {
            for (int coll = 0; coll < imgDim.x; ++coll) {
                int index = row * imgDim.x + coll;
                RGBApixel color;

                if ((int)gathered_result[index] == DEF_MAX_ITERATIONS) {
                    color.Red   = 0;
                    color.Green = 0;
                    color.Blue  = 0;
                }
                else {                    
                    color.Red   = ((int)gathered_result[index] * 9)  % 256;
                    color.Green = ((int)gathered_result[index] * 2)  % 256;;
                    color.Blue  = ((int)gathered_result[index] * 11) % 256;;
                }
                image.SetPixel(coll, row, color);
            }
        }
        image.WriteToFile("mandelbrot.bmp");
        std::cout << "O programa levou " << time << " segundos." << std::endl;
    }

    MPI_Finalize();
    return 0;
}
