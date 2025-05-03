#ifndef HEATDIFFUSION_TIMESTEPPER_HPP
#define HEATDIFFUSION_TIMESTEPPER_HPP

#include "heatdiffusion/Grid2D.hpp"

namespace heatdiffusion
{

class TimeStepper
{
public:
    virtual ~TimeStepper();

    virtual void step(Grid2D& grid, double currentTime, double dt) = 0;
};

}

#endif