#ifndef HEATDIFFUSION_SIMULATOR_HPP
#define HEATDIFFUSION_SIMULATOR_HPP

#include "heatdiffusion/TimeStepper.hpp"
#include "heatdiffusion/FrameWriter.hpp"

namespace heatdiffusion
{

/*
 * Simulates heat diffusion with an arbitrary TimeStepper
 * 
 * Works on a pointer to a grid
 */

class Simulator
{
public:
    Simulator(TimeStepper* stepper, Grid2D* grid, double dt, int maxSteps, int outputInterval, FrameWriter* writer);

    void run();
private:
    TimeStepper* _stepper;
    Grid2D* _grid;
    double _dt;
    int _maxSteps, _outputInterval;
    double _currentTime;
    FrameWriter* _writer;
};

}

#endif