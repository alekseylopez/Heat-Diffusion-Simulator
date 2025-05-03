#ifndef HEATDIFFUSION_EXPLICITSTEPPER_HPP
#define HEATDIFFUSION_EXPLICITSTEPPER_HPP

#include "heatdiffusion/TimeStepper.hpp"
#include "heatdiffusion/Grid2D.hpp"

namespace heatdiffusion
{

/*
 * Derived class of TimeStepper
 * 
 * Perform forward-Euler update on every interior cell:
 *     u_new = u_old + νx·Δxx + νy·Δyy
 */

class ExplicitStepper : public TimeStepper
{
public:
    ExplicitStepper();

    void step(Grid2D& grid, double currentTime, double dt) override;

    ~ExplicitStepper() override;
};

}


#endif