#include "heatdiffusion/Grid2D.hpp"
#include "heatdiffusion/ExplicitStepper.hpp"
#include "heatdiffusion/GifFrameWriter.hpp"
#include "heatdiffusion/Simulator.hpp"

#include <iostream>
#include <string>
#include <filesystem>

int main()
{
    // sample settings

    int nx = 100, ny = 100;
    double dx = 1.0, dy = 1.0;
    double alpha = 0.5;
    double dt = 0.2;
    int maxSteps = 1000;
    int outputInterval = 5;
    int delayCS = 5;
    std::string outGif = "diffusion.gif";

    heatdiffusion::Grid2D grid(nx, ny, dx, dy, alpha);
    grid.setBoundaryCondition([](int, int, double)
    {
        return 0.0;
    });

    grid(nx / 2, ny / 3) = 100.0;
    grid(nx / 2, 2 * ny / 3) = 100.0;

    // choose TimeStepper: Explicit or Implicit

    heatdiffusion::ExplicitStepper stepper;

    // create GIF writer on the stack - will make GIF file when destroyed

    heatdiffusion::GifFrameWriter writer(outGif, delayCS);

    // simulate

    heatdiffusion::Simulator sim(&stepper, &grid, dt, maxSteps, outputInterval, &writer);

    std::cout << "Writing PNG frames to " << std::filesystem::current_path() / "frames" << "\n";
    std::cout << "Final GIF will be: " << outGif << "\n";
    std::cout << "Running simulation...\n";

    sim.run();

    std::cout << "Simulation complete.\n";

    return 0;
}