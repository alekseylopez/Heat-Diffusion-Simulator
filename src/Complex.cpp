#include "heatdiffusion/Complex.hpp"

namespace heatdiffusion
{

Complex Complex::conj() const
{
    return {r, -i};
}

Complex Complex::operator+(const Complex& z) const
{
    return {r + z.r, i + z.i};
}

Complex Complex::operator-(const Complex& z) const
{
    return {r - z.r, i - z.i};
}

Complex Complex::operator*(const Complex& z) const
{
    return {r * z.r - i * z.i, r * z.i + i * z.r};
}

}