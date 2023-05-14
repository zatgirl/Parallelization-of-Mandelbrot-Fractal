#include "Mandelbrot.h"

/// <summary>
/// Calcula o número de iterações necessárias para determinar se um ponto do plano complexo
/// pertence ao conjunto de Mandelbrot, iterando sobre a fórmula z(n+1) = z(n)^2 + point, onde z(0) = point
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

/// <summary>
/// Calcula o conjunto de Mandelbrot de uma fatia da imagem, iterando sobre as linhas e colunas da imagem
/// calculando o número de iterações para cada pixel utilizando a funcao mandelbrot
/// </summary>
/// <param name="start"> Coordenadas da região </param>
/// <param name="end">   do plano complexo     </param>
/// <param name="imgDim"> Dimensoes da imagem completa </param>
/// <param name="maxIterations"> Condição de parada </param>
/// <param name="startRow"> Boudingbox da fatia da imagem  </param>
/// <param name="endRow">   recebida pelo processo         </param>
/// <returns></returns>
std::vector<int> CalculateMandelbrot(dvec2 start, dvec2 end, ivec2 imgDim, int maxIterations, int startRow, int endRow) {
    dvec2 step = dvec2((end - start) / imgDim);
    std::vector<int> result(imgDim.x * (endRow - startRow));

    for (int i = startRow; i < endRow; ++i) {
        double y = start.y + i * step.y;
        for (int j = 0; j < imgDim.x; ++j) {
            double x = start.x + j * step.x;
            std::complex<double> point(x, y);
            result[(i - startRow) * imgDim.x + j] = mandelbrot(point, maxIterations);
        }
    }
    return result;
}
