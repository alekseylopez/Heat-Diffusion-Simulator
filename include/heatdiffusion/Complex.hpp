#ifndef HEATDIFFUSION_COMPLEX_HPP
#define HEATDIFFUSION_COMPLEX_HPP

#include <cmath>

namespace heatdiffusion
{

struct Complex
{
    double r, i;

    Complex(double real = 0.0, double imag = 0.0):
        r(real), i(imag) {}

    Complex conj() const;
        
    Complex operator+(const Complex& z) const;
    Complex operator-(const Complex& z) const;
    Complex operator*(const Complex& z) const;
};

inline Complex cis(double theta)
{
    return {std::cos(theta), std::sin(theta)};
}

}

#endif