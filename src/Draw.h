#ifndef DRAW_H
#define DRAW_H

#include "ColorDouble.h"
#include "Color1.h"
#include "Color3.h"
#include "Buffer.h"
#include <math.h>

template <typename T>
class Draw
{
    
    const int numbers[10] = {
    075557,
    011111,
    071747,
    071717,
    055711,
    074717,
    074757,
    071111,
    075757,
    075717
    };

    const int PercentSign = 041241;

    private:
        //byte data[][];

    public:
        Buffer<T> *DisplayBuffer;
        char Rows;
        char Cols;

        Draw(char rows, char cols);
        ~Draw();
        void SetPixel(char x, char y,T value);
        T GetPixel(char x, char y);
        char TransformY(char x, char y);
        void Square(char x, char y, char size, T color);
        void Rect(char x, char y, char height, char width, T color);
        void RectBorder(char x, char y, char height, char width, T color);
        void Circle(char x, char y, char size, T color);
        void Circle(char x, char y, char size, T frontColor, T backColor);
        void Digit(char x, char y, char digit, T color, bool orientation);
        void Char(char x, char y, int character, T color, bool orientation);
        void Number(char x, char y, int number, char digits, T color, bool orientation);
        void ProgressBar(char x, char y,char height, char width, T barColor, T bgColor, float progress, bool orientation);
};

#endif