#ifndef COLORDOOUBLE_H
#define COLORDOOUBLE_H

#include "Color1.h"
#include "Color3.h"

template <typename T>
class ColorDouble
{
    private:
        /* data */
    public:
        T UpperColor;
        T LowerColor;
        ColorDouble(T upperColor, T lowerColor);
        ColorDouble();
        ~ColorDouble();
};

#endif
