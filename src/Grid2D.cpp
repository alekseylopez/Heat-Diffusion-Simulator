#include "heatdiffusion/Grid2D.hpp"

#include <stdexcept>
#include <utility>

namespace heatdiffusion
{

Grid2D::Grid2D(int Nx, int Ny, double dx, double dy, double alpha):
    _Nx(Nx), _Ny(Ny), _dx(dx), _dy(dy), _alpha(alpha), _data(Nx * Ny) {}

// setters

void Grid2D::setBoundaryCondition(std::function<double(int, int, double)> bc)
{
    _bc = std::move(bc);
}

// getters

int Grid2D::nx() const
{
    return _Nx;
}

int Grid2D::ny() const
{
    return _Ny;
}

double Grid2D::dx() const
{
    return _dx;
}

double Grid2D::dy() const
{
    return _dy;
}

double Grid2D::alpha() const
{
    return _alpha;
}

std::function<double(int, int, double)> Grid2D::boundaryCondition() const
{
    return _bc;
}

// operators

double& Grid2D::operator()(int i, int j)
{
    if(i < 0 || i >= _Nx || j < 0 || j >= _Ny)
        throw std::out_of_range("Grid2D::operator()");

    return _data[index(i, j)];
}

double Grid2D::operator()(int i, int j) const
{
    if(i < 0 || i >= _Nx || j < 0 || j >= _Ny)
        throw std::out_of_range("Grid2D::operator() const");
        
    return _data[index(i, j)];
}

}