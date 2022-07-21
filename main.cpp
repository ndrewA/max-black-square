#include <iostream>
#include <vector>
#include <unordered_map>

#include <algorithm>

struct Cell
{
    bool isBlack;
    size_t cols;
    size_t rows;
    Cell(bool b) : isBlack(b), cols(0), rows(0) { }
    Cell() { }
};

bool checkSquare(const std::vector<std::vector<Cell>>& matrix, size_t len, std::pair<size_t, size_t> index)
{
    if(matrix[index.first][index.second+len].cols >= matrix[index.first][index.second].cols &&
       matrix[index.first][index.second+len].cols - matrix[index.first][index.second].cols == len &&

       matrix[index.first+len][index.second+len].cols >= matrix[index.first+len][index.second].cols &&
       matrix[index.first+len][index.second+len].cols - matrix[index.first+len][index.second].cols == len &&

       matrix[index.first+len][index.second].rows >= matrix[index.first][index.second].rows &&
       matrix[index.first+len][index.second].rows - matrix[index.first][index.second].rows == len &&

       matrix[index.first+len][index.second+len].rows >= matrix[index.first][index.second+len].rows &&
       matrix[index.first+len][index.second+len].rows - matrix[index.first][index.second+len].rows == len) return true;
    return false;
}

std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> findMaxSquare(std::vector<std::vector<Cell>> matrix)
{

    size_t matrixLen = matrix.size();
    for(size_t rowIter = 0; rowIter < matrixLen; rowIter++)
    {
        size_t curLen = 0;

        for(size_t colIter = 0; colIter < matrixLen; colIter++)
        {
            if(matrix[rowIter][colIter].isBlack)
                matrix[rowIter][colIter].cols = ++curLen;

            else
                curLen = 0;
        }

    }

    for(size_t colIter = 0; colIter < matrixLen; colIter++)
    {
        size_t curLen = 0;

        for(size_t rowIter = 0; rowIter < matrixLen; rowIter++)
        {
            if(matrix[rowIter][colIter].isBlack)
                matrix[rowIter][colIter].rows = ++curLen;

            else
                curLen = 0;
        }
    }

    for(size_t rowIter = 1; rowIter <= matrix.size(); rowIter++)
    {
        for(size_t i = 0; i < rowIter; i++)
        {
            for(size_t j = 0; j < rowIter; j++)
            {
                size_t len = matrix.size()-rowIter;
                if(matrix[i][j].isBlack && checkSquare(matrix, len, {i, j})) return {{i, j}, {i+len, j+len}};
            }
        }
    }
    return {{0, 0}, {0, 0}};
}

int main()
{
    const size_t limit = 5;
    std::vector<std::vector<Cell>> matrix;

    for(size_t i = 0; i < limit; i++)
    {
        std::vector<Cell> row;
        for(size_t j = 0; j < limit; j++)
            row.push_back(Cell(true));
        matrix.push_back(row);
    }

    matrix[0][4].isBlack = false;
    auto res = findMaxSquare(matrix);
    std::cout << "============\n" << res.first.first << ' ' << res.first.second << '\n'
              << res.second.first << ' ' << res.second.second << '\n';
    return 0;
}
