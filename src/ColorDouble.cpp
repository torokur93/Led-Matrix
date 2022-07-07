#include "ColorDouble.h"

template <typename T>
ColorDouble<T>::ColorDouble(T upperColor, T lowerColor)
{
    UpperColor = upperColor;
    LowerColor = lowerColor;
}

template <typename T>
ColorDouble<T>::ColorDouble()
{
}


template <typename T>
ColorDouble<T>::~ColorDouble()
{
}

template class ColorDouble<Color1>;
template class ColorDouble<Color3>;
