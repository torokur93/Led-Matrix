#include "Draw.h"

// Constructor
template <typename T>
Draw<T>::Draw(char rows, char cols)
{
    DisplayBuffer = new Buffer<T>(rows, cols);
    Rows = rows;
    Cols = cols;
}
// Destructor
template <typename T>
Draw<T>::~Draw(){

}

template <typename T>
void Draw<T>::SetPixel(char x, char y,T value){

  char BufferX = (x & 0x03);
  
  char BufferY = TransformY((x & 0x04)>>2,y);

  if(x & 0x08){
    DisplayBuffer->SetUpperData(BufferX, BufferY, value);
  }else{
    DisplayBuffer->SetLowerData(BufferX, BufferY, value);
  }

}
template <typename T>
T Draw<T>::GetPixel(char x, char y){

  char BufferX = (x & 0x03);
  
  char BufferY = TransformY((x & 0x04)>>2,y);

  if(x & 0x08){
    return DisplayBuffer->GetUpperData(BufferX, BufferY);
  }else{
    return DisplayBuffer->GetLowerData(BufferX, BufferY);
  }

}

template <typename T>
char Draw<T>::TransformY(char x, char y){
  char SegmentID = y / 8;
  char BitID = y % 8;

  if(x){
    return (Cols*2) - 1 - y - SegmentID * 8;
  }else{
    return (Cols*2) - 16 -SegmentID * 16 + BitID;
  }

}

template <typename T>
void Draw<T>::Square(char x, char y, char size, T color){
  Rect(x, y, size, size, color);
}

template <typename T>
void Draw<T>::Rect(char x, char y, char height, char width, T color){
  for (char row = 0; row < height; row++)
  {
    for (char col = 0; col < width; col++)
    {
      SetPixel(x+row,y+col,color);
    }
    
  }
}

template <typename T>
void Draw<T>::RectBorder(char x, char y, char height, char width, T color){
  for (char row = 0; row < height; row++)
  {
    for (char col = 0; col < width; col++)
    {
      if(row == 0 || row == height-1 || col == 0 || col == width-1 ){
        SetPixel(x+row,y+col,color);
      }
    }
    
  }
}

template <typename T>
void Draw<T>::Circle(char x, char y, char size, T color){
  Circle(x,y,size,color,T(0,0,0));
}

template <typename T>
void Draw<T>::Circle(char x, char y, char size, T frontColor, T backColor){
  for (char row = 0; row < size; row++)
  {
    for (char col = 0; col < size; col++)
    {

      double distance = sqrt(pow(row-(size/2),2) + pow(col-(size/2),2));

      if(distance<=size/2){
        SetPixel(x-(size/2)+row,y-(size/2)+col,frontColor);
      }else{
        SetPixel(x-(size/2)+row,y-(size/2)+col,backColor);
      }
    }
    
  }
}

template <typename T>
void Draw<T>::Digit(char x, char y, char digit, T color, bool orientation){

  int digitData = numbers[digit%10];

  char x_Trans =0;
  char y_Trans =0;

  for (char row = 0; row < 5; row++)
  {
    for (char col = 0; col < 3; col++)
    {

      if(orientation){
        x_Trans = x-col;
        y_Trans = y+row;
      }else{
        x_Trans = x+row;
        y_Trans = y+col;
      }

      if(digitData>>(((row+1)*3)-1-col)&1){
        SetPixel(x_Trans,y_Trans,color);
      }else{
        SetPixel(x_Trans,y_Trans,T(0,0,0));
      }
    }
    
  }
}

template <typename T>
void Draw<T>::Char(char x, char y, int character, T color, bool orientation){

  char x_Trans =0;
  char y_Trans =0;

  for (char row = 0; row < 5; row++)
  {
    for (char col = 0; col < 3; col++)
    {

      if(orientation){
        x_Trans = x-col;
        y_Trans = y+row;
      }else{
        x_Trans = x+row;
        y_Trans = y+col;
      }

      if(character>>(((row+1)*3)-1-col)&1){
        SetPixel(x_Trans,y_Trans,color);
      }else{
        SetPixel(x_Trans,y_Trans,T(0,0,0));
      }
    }
    
  }
}

template <typename T>
void Draw<T>::Number(char x, char y, int number, char digits, T color, bool orientation){
  
  char x_Trans = x;
  char y_Trans = y;

  bool lastLeadingZero = true;

  number %= (int)pow(10,digits);

  for (char digit = 0; digit < digits; digit++)
  {
    if (orientation)
    {
      x_Trans = x + (digit * -4);
    }else{
      y_Trans = y + (digit * 4);
    }

    unsigned int currentDigitValue = ((unsigned int)(number/pow(10,(digits-1)-digit))) % 10;

    if(!(lastLeadingZero && (currentDigitValue == 0)) || (number == 0 && digit == (digits-1)) ){
      Digit(x_Trans,y_Trans,currentDigitValue,T(0,0,1),orientation);
      lastLeadingZero = false;
    }else{
      Rect(x_Trans-2, y_Trans, 3, 5, T(0,0,0));
    }
  }
}

template <typename T>
void Draw<T>::ProgressBar(char x, char y,char height, char width, T barColor, T bgColor, float progress, bool orientation){
  
  if(orientation){
    Rect(x,y,height,(char)(width*progress),barColor);
    Rect(x,y+(char)(width*progress),height,width-(char)(width*progress),bgColor);
  }else{
    Rect(x,y,(char)(height*progress),width,barColor);
    Rect(x+(char)(height*progress),y,height-(char)(width*progress),width,bgColor);
  }
}

template class Draw<Color1>;
template class Draw<Color3>;