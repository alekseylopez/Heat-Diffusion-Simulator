#include "heatdiffusion/ImplicitStepper.hpp"

namespace heatdiffusion
{

ImplicitStepper::ImplicitStepper(double theta):
    _theta(theta) {}

void ImplicitStepper::step(Grid2D& grid, double currentTime, double dt)
{
    (void) _theta;
    (void) grid;
    (void) currentTime;
    (void) dt;
}

ImplicitStepper::~ImplicitStepper() = default;

}