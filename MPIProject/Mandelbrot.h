#ifndef __MANDELBROT__H__
#define __MANDELBROT__H__

#include "MathHelpers.h"
#include <complex>
#include <vector>

int mandelbrot(const std::complex<double>& point, int maxIterations);
std::vector<int> CalculateMandelbrot(dvec2 start, dvec2 end, ivec2 imgDim, int maxIterations, int start_row, int end_row);

#endif  // __MANDELBROT__H__
