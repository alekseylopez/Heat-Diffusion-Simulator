#ifndef HEATDIFFUSION_TIMESTEPPER_HPP
#define HEATDIFFUSION_TIMESTEPPER_HPP

#include "heatdiffusion/Grid2D.hpp"

namespace heatdiffusion
{

/*
 * Abstract time stepper class - for moving a grid forward in time
 * 
 * Derived classes: ExplicitStepper and ImplicitStepper
 */

class TimeStepper
{
public:
    virtual void step(Grid2D& grid, double currentTime, double dt) = 0;
    
    virtual ~TimeStepper();
};

}

#endif