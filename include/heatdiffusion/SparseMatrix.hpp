#ifndef HEATDIFFUSION_SPARSEMATRIX_HPP
#define HEATDIFFUSION_SPARSEMATRIX_HPP

#include <vector>

namespace heatdiffusion
{

class SparseMatrix
{
public:
    SparseMatrix(int rows, int cols);

    void add(int r, int c, double value);

    void finalize();

    void multiply(const std::vector<double>& x, std::vector<double>& y) const;

    void clearRow(int r);

    void scale(double factor);

    void addIdentity(double factor);

private:
    int _rows, _cols;
    std::vector<int> _rowPtr; // row -> index
    std::vector<int> _colIdx; // index -> column
    std::vector<double> _vals; // VALUES: index -> value
    std::vector<std::vector<std::pair<int, double>>> _staging;
};

}

#endif