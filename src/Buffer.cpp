#include "Buffer.h"

// Constructor
Buffer::Buffer(char rows, char cols)
{
    Rows = rows;
    Cols = cols;
    //data = new Array2D(rows, cols);
    data = new ColorDouble[rows*cols];

    ClearData();
}
// Destructor
Buffer::~Buffer(){

}

void Buffer::ClearData(){
    SetData(ColorDouble());
}

void Buffer::SetData(ColorDouble value){
    
    for (char row = 0; row < Rows; row++)
    {
        for (char col = 0; col < Cols; col++)
        {
            data[(row * Cols) + col] = value;
        }
    }
}

void Buffer::SetData(char x, char y, ColorDouble value){
    if(x<=Rows && y<=Cols){
        data[(x * Cols) + y]=value;
    }

}

ColorDouble Buffer::GetData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[(x * Cols) + y];
    }

    return ColorDouble();
}

void Buffer::SetLowerData(char x, char y, Color1 value){
    if(x<=Rows && y<=Cols){
        data[(x * Cols) + y].LowerColor=value;
    }

}

void Buffer::SetUpperData(char x, char y, Color1 value){
    if(x<=Rows && y<=Cols){
        data[(x * Cols) + y].UpperColor=value;
    }

}

Color1 Buffer::GetLowerData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[(x * Cols) + y].LowerColor;
    }

    return Color1();
}

Color1 Buffer::GetUpperData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[(x * Cols) + y].UpperColor;
    }

    return Color1();
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


