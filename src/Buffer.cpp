#include "Buffer.h"

// Constructor
template <typename T>
Buffer<T>::Buffer(char rows, char cols)
{
    Rows = rows;
    Cols = cols;
    //data = new Array2D(rows, cols);
    data = new ColorDouble<T>[rows*cols];

    ClearData();
}
// Destructor
template <typename T>
Buffer<T>::~Buffer(){

}

template <typename T>
void Buffer<T>::ClearData(){
    SetData(ColorDouble<T>());
}

template <typename T>
void Buffer<T>::SetData(ColorDouble<T> value){
    
    for (char row = 0; row < Rows; row++)
    {
        for (char col = 0; col < Cols; col++)
        {
            data[(row * Cols) + col] = value;
        }
    }
}

template <typename T>
void Buffer<T>::SetData(char x, char y, ColorDouble<T> value){
    if(x<=Rows && y<=Cols){
        data[(x * Cols) + y]=value;
    }

}

template <typename T>
ColorDouble<T> Buffer<T>::GetData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[(x * Cols) + y];
    }

    return ColorDouble<T>();
}

template <typename T>
void Buffer<T>::SetLowerData(char x, char y, T value){
    if(x<=Rows && y<=Cols){
        data[(x * Cols) + y].LowerColor=value;
    }

}

template <typename T>
void Buffer<T>::SetUpperData(char x, char y, T value){
    if(x<=Rows && y<=Cols){
        data[(x * Cols) + y].UpperColor=value;
    }

}

template <typename T>
T Buffer<T>::GetLowerData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[(x * Cols) + y].LowerColor;
    }

    return T();
}

template <typename T>
T Buffer<T>::GetUpperData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[(x * Cols) + y].UpperColor;
    }

    return T();
}
/*
void Buffer::SetBits(char x, char y, char bits){
    data[(x * Cols) + y] |= bits;
}
void Buffer::ClearBits(char x, char y, char bits){
    data[(x * Cols) + y] &= ~bits;
}
void Buffer::ToggleBits(char x, char y, char bits){
    data[(x * Cols) + y] ^= bits;
}*/

template class Buffer<Color1>;
template class Buffer<Color3>;

