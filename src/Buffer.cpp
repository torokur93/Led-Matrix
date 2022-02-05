#include "Buffer.h"

// Constructor
Buffer::Buffer(char rows, char cols)
{
    Rows = rows;
    Cols = cols;
    data = new Array2D(rows, cols);
    ClearData();
}
// Destructor
Buffer::~Buffer(){

}

Buffer::ClearData(){
    SetData(0);
}

Buffer::SetData(char value){
    
    for (char row = 0; row < Rows; row++)
    {
        for (char col = 0; col < Cols; col++)
        {
            data[row][col] = value;
        }
    }
}

Buffer::SetData(char x, char y, char value){
    if(x<=Rows && y<=Cols){
        data[x][y]=value;
    }

}

Buffer::GetData(char x, char y){
    if(x<=Rows && y<=Cols){
        return data[x][y];
    }

    return 0;

}

Buffer::SetBits(char x, char y, char bits){
    data[x][y] |= bits;
}
Buffer::ClearBits(char x, char y, char bits){
    data[x][y] &= ~bits;
}
Buffer::SetBits(char x, char y, char bits){
    data[x][y] ^= bits;
}