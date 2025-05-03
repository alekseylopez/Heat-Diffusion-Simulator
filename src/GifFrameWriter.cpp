#include "heatdiffusion/GifFrameWriter.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../thirdparty/stb_image_write.h"
#pragma clang diagnostic pop

#include <filesystem>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

namespace heatdiffusion
{

GifFrameWriter::GifFrameWriter(std::string outGif, int delayCS):
    _outGif(outGif), _delayCS(delayCS), _frameCount(0)
{
    std::filesystem::create_directories("frames");
}

// Uses https://github.com/nothings/stb to make GIFS

void GifFrameWriter::writeFrame(const Grid2D& grid, int, double)
{
    int nx = grid.nx(), ny = grid.ny();

    // find range - for normalization

    double minVal = grid(0, 0), maxVal = grid(0, 0);
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            double val = grid(i, j);

            minVal = std::min(minVal, val);
            maxVal = std::max(maxVal, val);
        }
    }
    double range = (maxVal > minVal) ? (maxVal - minVal) : 1.0;

    // write to vector

    std::vector<uint8_t> buffer(nx * ny);
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            double normalized = (grid(i, j) - minVal) / range;

            buffer[i + nx * j] = static_cast<uint8_t>(normalized * 255);
        }
    }

    // create file

    char filename[128];

    std::snprintf(filename, sizeof(filename), "frames/frame_%04d.png", _frameCount++);

    // write to that file

    stbi_write_png(filename, nx, ny, 1, buffer.data(), nx);
}

GifFrameWriter::~GifFrameWriter()
{
    std::string cmd = "magick -delay " + std::to_string(_delayCS) + " -loop 0 frames/frame_*.png " + _outGif;
    std::system(cmd.c_str());

    std::filesystem::remove_all("frames");
}

}