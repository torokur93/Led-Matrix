#ifndef BUFFER_H
#define BUFFER_H

#include "ColorDouble.h"
#include "Color1.h"
#include "Color3.h"

template <typename T>
class Buffer
{
    private:
        //byte data[][];

    public:
        char Rows;
        char Cols;
        //Array2D data;
        ColorDouble<T> *data;

        Buffer(char rows, char cols);

        void ClearData();

        void SetData(ColorDouble<T> value);

        void SetData(char x, char y, ColorDouble<T> value);

        ColorDouble<T> GetData(char x, char y);

        void SetLowerData(char x, char y, T value);

        void SetUpperData(char x, char y, T value);

        T GetLowerData(char x, char y);

        T GetUpperData(char x, char y);

        void SetBits(char x, char y, char bits);

        void ClearBits(char x, char y, char bits);

        void ToggleBits(char x, char y, char bits);

        ~Buffer();
};

#endif