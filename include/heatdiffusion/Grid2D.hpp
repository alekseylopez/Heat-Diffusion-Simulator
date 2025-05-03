#ifndef HEATDIFFUSION_GRID2D_HPP
#define HEATDIFFUSION_GRID2D_HPP

#include <vector>
#include <functional>

namespace heatdiffusion
{

class Grid2D
{
public:
    Grid2D(int Nx, int Ny, double dx, double dy, double alpha);

    void setBoundaryCondition(std::function<double(int, int, double)> bc);

    int nx() const;
    int ny() const;
    double dx() const;
    double dy() const;
    double alpha() const;

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

private:
    int _Nx, _Ny;
    double _dx, _dy, _alpha;
    std::vector<double> _data;
    std::function<double(int, int, double)> _bc;

    inline int index(int i, int j) const
    {
        return i + j * _Nx;
    }
};

}

#endif