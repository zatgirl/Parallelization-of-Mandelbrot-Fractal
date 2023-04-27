#include <iostream>
#include <mpi.h>
#include "EasyBMP.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 800;
const int MAX_ITERATIONS = 100;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    BMP mandelbrotImage;

    if (rank == 0) {
        mandelbrotImage.SetSize(WIDTH, HEIGHT);
        mandelbrotImage.SetBitDepth(24);
    }

    /// 
    double xMin = -2.0;
    double xMax = 1.0;
    double yMin = -1.5;
    double yMax = 1.5;
        
    /// Divide a imagem na quantidade de processos que tão disponíveis
    int rowsPerProcess = HEIGHT / size;
    int startRow = rank * rowsPerProcess;
    int endRow = startRow + rowsPerProcess;

    printf("startRow: %d | rank: %d\n", startRow, rank);
    printf("endRow: %d | rank %d\n", endRow, rank);

    RGBApixel* buffer = new RGBApixel[WIDTH * rowsPerProcess];

    for (int line = startRow; line < endRow; line++) {
        for (int coll = 0; coll < WIDTH; coll++) {
            double x0 = xMin + (double)coll / (double)WIDTH * (xMax - xMin);
            double y0 = yMin + (double)line / (double)HEIGHT * (yMax - yMin);

            double x = 0.0;
            double y = 0.0;
            int iteration = 0;

            while (x * x + y * y < 4 && iteration < MAX_ITERATIONS) {
                double xTemp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xTemp;
                iteration++;
            }

            RGBApixel pixel;
            if (iteration == MAX_ITERATIONS) {
                pixel.Red = 0;
                pixel.Green = 0;
                pixel.Blue = 0;
            }
            else {
                pixel.Red = iteration * 5;
                pixel.Green = iteration * 5;
                pixel.Blue = iteration * 5;
            }

            /// Armazena o pixel no buffer
            buffer[(line - startRow) * WIDTH + coll] = pixel;
        }
    }

    /// Junta as partes calculadas
    MPI_Gather(buffer, WIDTH * rowsPerProcess, MPI_UNSIGNED_CHAR, mandelbrotImage(0,startRow),
               WIDTH * rowsPerProcess, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        mandelbrotImage.WriteToFile("mandelbrot.bmp");
    }

    MPI_Finalize();
    return 0;
}
