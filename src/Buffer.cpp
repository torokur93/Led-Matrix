#include "Buffer.h"

// Constructor
Buffer::Buffer(char rows, char cols)
{
    Rows = rows;
    Cols = cols;
    //data = new Array2D(rows, cols);
    data = new char[rows*cols];

    ClearData();
}
// Destructor
Buffer::~Buffer(){

}

void Buffer::ClearData(){
    SetData(0);
}

void Buffer::SetData(char value){
    
    for (char row = 0; row < Rows; row++)
    {
        for (char col = 0; col < Cols; col++)
        {
            data[(row * Cols) + col] = value;
        }
    }
}

void Buffer::SetData(char x, char y, char value){
    if(x<=Rows && y<=Cols){
        data[(x * Cols) + y]=value;
    }

}

char Buffer::GetData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[(x * Cols) + y];
    }

    return 0;

}

void Buffer::SetBits(char x, char y, char bits){
    data[(x * Cols) + y] |= bits;
}
void Buffer::ClearBits(char x, char y, char bits){
    data[(x * Cols) + y] &= ~bits;
}
void Buffer::ToggleBits(char x, char y, char bits){
    data[(x * Cols) + y] ^= bits;
}