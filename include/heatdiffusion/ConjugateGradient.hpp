#ifndef HEATDIFFUSION_CONJUGATEGRADIENT_HPP
#define HEATDIFFUSION_CONJUGATEGRADIENT_HPP

#include "SparseMatrix.hpp"

#include <vector>

namespace heatdiffusion
{

bool solveCG(const SparseMatrix& A, const std::vector<double>& b, std::vector<double>& x, double tol = 1e-4, int maxIt = 5000);

}

#endif