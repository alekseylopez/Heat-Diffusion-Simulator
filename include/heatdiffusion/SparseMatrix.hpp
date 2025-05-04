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

    void multiply(const std::vector<double>& x, std::vector<double>& y);

    void clearRow(int r);

private:
    int _rows, _cols;
    std::vector<int> _rowPtr;
    std::vector<int> _colIdx;
    std::vector<double> _vals;
    std::vector<std::vector<std::pair<int, double>>> _staging;
};

}

#endif