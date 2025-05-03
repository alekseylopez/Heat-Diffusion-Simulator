#include "heatdiffusion/Simulator.hpp"

namespace heatdiffusion
{

Simulator::Simulator(TimeStepper* stepper, Grid2D* grid, double dt, int maxSteps, int outputInterval, FrameWriter* writer):
    _stepper(stepper), _grid(grid), _dt(dt), _maxSteps(maxSteps), _outputInterval(outputInterval), _currentTime(0.0), _writer(writer)
{
    if(!_stepper || !_grid || !_writer)
        throw std::invalid_argument("Simulator::Simulator: null pointer passed");
    if(_dt <= 0 || _maxSteps < 1 || _outputInterval < 1)
        throw std::invalid_argument("Simulator::Simulator: invalid parameters");
}

void Simulator::run()
{
    // write first frame

    _writer->writeFrame(*_grid, 0, _currentTime);

    // do steps

    for(int step = 1; step <= _maxSteps; step++)
    {
        _stepper->step(*_grid, _currentTime, _dt);

        _currentTime += _dt;

        // only write frame on some steps

        if(step % _outputInterval == 0)
            _writer->writeFrame(*_grid, step, _currentTime);
    }
}

}