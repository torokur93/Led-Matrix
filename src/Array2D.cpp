#include "Array2D.h"

Array2D::Array2D(char rows, char cols)
{
    Rows = rows;
    Cols = cols;
    data = new char* [rows];
    
    for (char i = 0; i < rows; i++)
    {
        data[i] = new char* [cols];
    }
}



Array2D::~Array2D()
{
}