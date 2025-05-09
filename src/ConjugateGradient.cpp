#include "heatdiffusion/ConjugateGradient.hpp"

namespace heatdiffusion
{

bool solveCG(const SparseMatrix& A, const std::vector<double>& b, std::vector<double>& x, double tol, int maxIt)
{
    int N = static_cast<int>(b.size());

    std::vector<double> r(N), p(N), Ap(N);

    // r = b - Ax

    A.multiply(x, r);
    for(int i = 0; i < N; i++)
        r[i] = b[i] - r[i];

    p = r;

    // rsold = rᵀr

    double rsold = 0;

    for(double v : r)
        rsold += v * v;

    if(rsold < tol * tol)
        return true;

    // loop

    for(int iter = 0; iter < maxIt; iter++)
    {
        // alpha = rᵀr / pᵀAp

        A.multiply(p, Ap);

        double alpha = 0;

        for(int i = 0; i < N; i++)
            alpha += p[i] * Ap[i];

        alpha = rsold / alpha;

        // update solution and residual

        for(int i = 0; i < N; i++)
        {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }

        // rsnew = rᵀr

        double rsnew = 0;

        for(double v : r)
            rsnew += v * v;
        
        if(rsnew < tol * tol)
            return true;
        
        // beta = r_{k + 1}ᵀ r_{k + 1} / r_kᵀr_k

        double beta = rsnew / rsold;

        // p_{k + 1} = r_{k + 1} + β·p_k

        for(int i = 0; i < N; i++)
            p[i] = r[i] + beta * p[i];

        // update rsold
        
        rsold = rsnew;
    }

    return false;
}

}