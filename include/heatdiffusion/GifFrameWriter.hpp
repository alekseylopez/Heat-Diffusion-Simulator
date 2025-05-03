#ifndef HEATDIFFUSION_GIFWRITER_HPP
#define HEATDIFFUSION_GIFWRITER_HPP

#include "heatdiffusion/FrameWriter.hpp"

#include <string>

namespace heatdiffusion
{

/*
 * Derived class of FrameWriter
 * 
 * Makes GIFs
 * 
 * Uses https://github.com/nothings/stb
 */

class GifFrameWriter : public FrameWriter
{
public:
    GifFrameWriter(std::string outGif, int delayCS = 10);

    void writeFrame(const Grid2D& grid, int step, double time) override;

    ~GifFrameWriter() override;

private:
    std::string _outGif;
    int _delayCS, _frameCount;
};

}

#endif