#ifndef HEATDIFFUSION_IMPLICITSTEPPER_HPP
#define HEATDIFFUSION_IMPLICITSTEPPER_HPP

#include "heatdiffusion/TimeStepper.hpp"
#include "heatdiffusion/Grid2D.hpp"

namespace heatdiffusion
{

class ImplicitStepper : public TimeStepper
{
public:
    ImplicitStepper() = default;

    void step(Grid2D& grid, double currentTime, double dt) override
    {
        
    }

    ~ImplicitStepper() override = default;
};

}


#endif