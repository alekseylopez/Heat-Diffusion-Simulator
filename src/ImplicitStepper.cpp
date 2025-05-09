#include "heatdiffusion/ImplicitStepper.hpp"

namespace heatdiffusion
{

ImplicitStepper::ImplicitStepper(double theta):
    _theta(theta) {}

void ImplicitStepper::step(Grid2D& grid, double currentTime, double dt)
{
    // grid parameters

    int nx = grid.nx();
    int ny = grid.ny();
    int N = nx * ny;
    double dx = grid.dx();
    double dy = grid.dy();
    double alpha = grid.alpha();

    // build backward-Euler matrix A = I - θ·dt·α·∆

    // start with discrete laplacian L0

    SparseMatrix L0(N, N);
    auto idx = [&](int i, int j){return i + j * nx;};

    double cx0 = alpha / (dx * dx);
    double cy0 = alpha / (dy * dy);

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            int r = idx(i, j);

            if(i > 0) L0.add(r, idx(i - 1, j), cx0);
            if(i < nx - 1) L0.add(r, idx(i + 1, j), cx0);
            
            if(j > 0) L0.add(r, idx(i, j - 1), cy0);
            if(j < ny - 1) L0.add(r, idx(i, j + 1), cy0);

            L0.add(r, r, -2.0 * (cx0 + cy0));
        }
    }

    L0.finalize();

    // now scale by - θ·dt and add identity to get A

    SparseMatrix A = L0;
    A.scale(-_theta * dt);
    A.addIdentity(1.0);

    // now form the RHS of system: b = u^n + (1-θ)·dt·(L0·u^n)

    std::vector<double> u(N), Lu(N), b(N), x(N);

    for(int i = 0; i < nx; i++)
        for(int j = 0; j < ny; j++)
            u[idx(i, j)] = grid(i, j);
    
    L0.multiply(u, Lu);

    double beta = (1.0 - _theta) * dt;

    for(int k = 0; k < N; k++)
    {
        b[k] = u[k] + beta * Lu[k];

        // simultaneously create initial guess for conjugate gradient
        
        x[k] = b[k];
    }

    // boundary conditions
    // zero out row r in A and fix b[r] and x[r]

    const auto& bc = grid.boundaryCondition();

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            if(i == 0 || j == 0 || i == nx - 1 || j == ny - 1)
            {
                int r = idx(i, j);
                A.clearRow(r);

                double g = bc(i, j, currentTime + dt);

                b[r] = g;
                x[r] = g;
            }
        }
    }

    bool solved = solveCG(A, b, x);
    if(!solved) throw std::runtime_error("ImplictStepper::step did not converge");

    // write u^{n + 1} back to grid

    for(int i = 0; i < nx; i++)
        for(int j = 0; j < ny; j++)
            grid(i, j) = x[idx(i, j)];
}

ImplicitStepper::~ImplicitStepper() = default;

}