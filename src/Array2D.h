#ifndef ARRAY2D_H
#define ARRAY2D_H

class Array2D
{
private:
    char Rows;
    char Cols;
    char **data;
public:
    Array2D(char rows, char cols);
    ~Array2D();
    
};

#endif