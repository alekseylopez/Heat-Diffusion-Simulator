#include "heatdiffusion/ExplicitStepper.hpp"

namespace heatdiffusion
{

ExplicitStepper::ExplicitStepper() = default;

// forward-Euler method

void ExplicitStepper::step(Grid2D& grid, double currentTime, double dt)
{
    // get info

    int nx = grid.nx(), ny = grid.ny();
    double dx = grid.dx(), dy = grid.dy(), alpha = grid.alpha();

    std::vector<double> oldData(nx * ny);
    for(int i = 0; i < nx; i++)
        for(int j = 0; j < ny; j++)
            oldData[i + j * nx] = grid(i, j);
    
    const auto& bc = grid.boundaryCondition();

    // diffusion numbers

    double nu_x = alpha * dt / (dx * dx);
    double nu_y = alpha * dt / (dy * dy);

    // loop over each cell

    for(int i = 0; i < ny; i++)
    {
        for(int j = 0; j < nx; j++)
        {
            if(i == 0 || j == 0 || i == nx - 1 || j == ny - 1)
            {
                // boundary => use bc functor

                grid(i, j) = bc(i, j, currentTime + dt);
            } else
            {
                // discrete Laplacian approximation

                double uij = oldData[i + j * nx];

                double lapX = oldData[(i + 1) + j * nx] - 2 * uij + oldData[(i - 1) + j * nx];
                double lapY = oldData[i + (j + 1) * nx] - 2 * uij + oldData[i + (j - 1) * nx];

                grid(i, j) = uij + nu_x * lapX + nu_y * lapY;
            }
        }
    }
}

ExplicitStepper::~ExplicitStepper() = default;

}