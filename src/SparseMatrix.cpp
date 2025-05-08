#include "heatdiffusion/SparseMatrix.hpp"

#include <stdexcept>

namespace heatdiffusion
{

SparseMatrix::SparseMatrix(int rows, int cols):
    _rows(rows), _cols(cols), _staging(rows) {}

void SparseMatrix::add(int r, int c, double value)
{
    if(r < 0 || r >= _rows || c < 0 || c >= _cols)
        throw std::out_of_range("SparseMatrix::add");
    
    _staging[r].push_back({c, value});
}

void SparseMatrix::finalize()
{
    // get array of indices

    _rowPtr.assign(_rows + 1, 0);
    for(int r = 0; r < _rows; r++)
        _rowPtr[r + 1] = _rowPtr[r] + static_cast<int>(_staging[r].size());
    
    // number of nonzerot

    int nnz = _rowPtr.back();
    _colIdx.resize(nnz);
    _vals.resize(nnz);

    for(int r = 0; r < _rows; r++)
    {
        int base = _rowPtr[r];

        for(int k = 0; k < static_cast<int>(_staging[r].size()); k++)
        {
            _colIdx[base + k] = _staging[r][k].first;
            _vals[base + k] = _staging[r][k].second;
        }
    }

    // free _staging

    _staging.clear();
    _staging.shrink_to_fit();
}

// requires x.size() == _cols

void SparseMatrix::multiply(const std::vector<double>&x, std::vector<double>& y)
{
    y.assign(_rows, 0);

    for(int r = 0; r < _rows; r++)
    {
        double sum = 0;

        for(int i = _rowPtr[r]; i < _rowPtr[r + 1]; i++)
            sum += _vals[i] * x[_colIdx[i]];

        y[r] = sum;
    }
}

void SparseMatrix::clearRow(int r)
{
    // zero out the row

    for(int i = _rowPtr[r]; i < _rowPtr[r + 1]; i++)
        _vals[i] = 0;
    
    // make the diagonal entry 1
    
    bool found = false;
    for(int i = _rowPtr[r]; i < _rowPtr[r + 1]; i++)
    {
        if(_colIdx[i] == r)
        {
            _vals[i] = 1;
            found = true;
            break;
        }
    }

    if(!found)
        throw std::invalid_argument("SparseMatrix::clearRow");
}

}