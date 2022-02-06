#ifndef COLORDOOUBLE_H
#define COLORDOOUBLE_H

#include "Color1.h"

class ColorDouble
{
    private:
        /* data */
    public:
        Color1 UpperColor;
        Color1 LowerColor;
        ColorDouble(Color1 upperColor, Color1 lowerColor);
        ColorDouble();
        ~ColorDouble();
};

#endif
