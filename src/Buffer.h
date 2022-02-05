#ifndef BUFFER_H
#define BUFFER_H

#include "Array2D.h"

class Buffer
{
    private:
        //byte data[][];

    public:
        char Rows;
        char Cols;
        Array2D data;

        Buffer(char rows, char cols);

        void ClearData();

        void SetData(char value);

        void SetData(char x, char y, char value);

        char GetData(char x, char y);

        void SetBits(char x, char y, char bits);

        void ClearBits(char x, char y, char bits);

        void ToggleBits(char x, char y, char bits);

        ~Buffer();
};

#endif