#ifndef BUFFER_H
#define BUFFER_H

#include "ColorDouble.h"

class Buffer
{
    private:
        //byte data[][];

    public:
        char Rows;
        char Cols;
        //Array2D data;
        ColorDouble *data;

        Buffer(char rows, char cols);

        void ClearData();

        void SetData(ColorDouble value);

        void SetData(char x, char y, ColorDouble value);

        ColorDouble GetData(char x, char y);

        void SetLowerData(char x, char y, Color1 value);

        void SetUpperData(char x, char y, Color1 value);

        Color1 GetLowerData(char x, char y);

        Color1 GetUpperData(char x, char y);

        void SetBits(char x, char y, char bits);

        void ClearBits(char x, char y, char bits);

        void ToggleBits(char x, char y, char bits);

        ~Buffer();
};

#endif