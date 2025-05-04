# Heat Diffusion Simulator

Currently simulating heat diffusion using the forward Euler method to solve the heat equation
$\frac{\partial u}{\partial t} = \alpha \nabla^2 u$ in two dimensions, then writing the short term behavior to a GIF file.

## Future

Will implement an implicit PDE solver using the backward Euler method.

## Credits

Code in "src/" and "include/heatdiffusion/" written by Aleksey Lopez.
* Github: https://github.com/alekseylopez
* LinkedIn: https://www.linkedin.com/in/aleksey-lopez-627922288/

Uses the file "stb_image_write.h" from https://github.com/nothings/stb.

## Dependencies

Uses the "magick" command from ImageMagick to convert series of .png files to .gif file.
