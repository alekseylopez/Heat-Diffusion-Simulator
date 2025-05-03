#ifndef HEATDIFFUSION_FRAMEWRITER_HPP
#define HEATDIFFUSION_FRAMEWRITER_HPP

#include "heatdiffusion/Grid2D.hpp"

namespace heatdiffusion
{

/*
 * Abstract frame writer class
 */

class FrameWriter
{
public:
    virtual void writeFrame(const Grid2D& grid, int step, double time) = 0;

    virtual ~FrameWriter();
};

}

#endif