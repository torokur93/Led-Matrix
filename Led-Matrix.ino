#include "src/Buffer.h"

#define ROWS  16
#define COLS  32
#define FPS   1

// Pin definitions

#define LP    10           // Latch Pin
#define ClkP  8        // Clock Pin
#define R1P   2         // R1 Pin
#define B1P   4         // B1 Pin
#define G1P   3          // G1 Pin
#define R2P   5          // R2 Pin
#define B2P   7          // B2 Pin
#define G2P   6          // G2 Pin
#define AP    A0           // A Pin
#define BP    A1           // B Pin
#define CP    A2           // C Pin
#define DP    A3           // D Pin
#define OEP   9         // OE Pin

// Variable definitions

uint64_t temp;
int row = 0;
uint8_t i;
int pixel=0;
int color = 1;

char currentFrame = 0;

Buffer DisplayBuffer(ROWS/4,COLS*2);

void setup() {
  
  InitalizePins();

  row=0;
  temp = 1;  
  
  DisplayBuffer.ClearData();

  Serial.begin(9600);

}

void loop() {
/*
  color=1;
  for(char row = 0; row<ROWS; row++){
    for(char col = 0; col<COLS; col++){
      Color1 tmp(color & B001, (color & B010)>>1, (color & B100)>>2);
      //Color1 tmp(1, 1, 1);

      SetPixel(row,col,tmp);
      UpdateDisplay();
      
    }
    
    if(color == 7)
    {
      color=1;
    }else{
      color++;
    }
  }
*/

  /*SetPixel(0,0,Color1(1,0,0));
  SetPixel(1,0,Color1(1,1,0));
  SetPixel(0,4,Color1(1,1,0));
  SetPixel(4,0,Color1(0,1,0));
  SetPixel(4,4,Color1(0,1,1));*/

  for (char currentFrame = 1; currentFrame < 150; currentFrame++)
  {

    DrawCircle(7,8,currentFrame/10,Color1(0,1,1));
    DrawCircle(7,24,currentFrame/10,Color1(0,1,0),Color1(1,0,0));
    DrawSquare(5,22,currentFrame/30,Color1(1,1,0));
    UpdateDisplay();
    DisplayBuffer.ClearData();
  }
  

  //UpdateSerial();
  

}

void InitalizePins(){
  
  pinMode(LP, OUTPUT);
  pinMode(ClkP, OUTPUT);
  pinMode(R1P, OUTPUT);
  pinMode(B1P, OUTPUT);
  pinMode(G1P, OUTPUT);
  pinMode(R2P, OUTPUT);
  pinMode(B2P, OUTPUT);
  pinMode(G2P, OUTPUT);
  pinMode(AP,OUTPUT);
  pinMode(BP,OUTPUT);
  pinMode(CP,OUTPUT);
  pinMode(DP,OUTPUT);
  pinMode(OEP,OUTPUT);
  
  digitalWrite(AP, LOW);
  digitalWrite(BP, LOW);
  digitalWrite(CP, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(LP, LOW);
  digitalWrite(OEP, LOW);
}


void SetPixel(char x, char y,Color1 value){

  char BufferX = (x & B011);
  
  char BufferY = TransformY((x & B100)>>2,y);

  //char ValueFilter;

  if(x & B1000){
    /*ValueFilter = B111000;
    value <<= 3;*/
    DisplayBuffer.SetUpperData(BufferX, BufferY, value);
  }else{
    //ValueFilter = B000111;
    DisplayBuffer.SetLowerData(BufferX, BufferY, value);
  }
/*
  DisplayBuffer.ClearBits(BufferX,BufferY,ValueFilter);
  DisplayBuffer.SetBits(BufferX,BufferY,value & ValueFilter);
*/
}

char TransformY(char x, char y){
  char SegmentID = y / 8;
  char BitID = y % 8;

  if(x){
    return (COLS*2) - 1 - y - SegmentID * 8;
  }else{
    return (COLS*2) - 16 -SegmentID * 16 + BitID;
  }

}


void UpdateDisplay(){
  
  

  for(char row=0;row<DisplayBuffer.Rows;row++){
    for(char col=0;col<DisplayBuffer.Cols;col++){

      ColorDouble CurrentPixel = DisplayBuffer.GetData(row,col);
      /*
      // Lower Half
      digitalWrite(B1P, CurrentPixel & B00000001);
      digitalWrite(G1P, (CurrentPixel>>1) & B00000001);
      digitalWrite(R1P, (CurrentPixel>>2) & B00000001);
      // Higher Half
      digitalWrite(B2P, (CurrentPixel>>3) & B00000001);
      digitalWrite(G2P, (CurrentPixel>>4) & B00000001);
      digitalWrite(R2P, (CurrentPixel>>5) & B00000001);
      */

      // Lower Half
      digitalWrite(B1P, CurrentPixel.LowerColor.GetB());
      digitalWrite(G1P, CurrentPixel.LowerColor.GetG());
      digitalWrite(R1P, CurrentPixel.LowerColor.GetR());
      // Higher Half
      digitalWrite(B2P, CurrentPixel.UpperColor.GetB());
      digitalWrite(G2P, CurrentPixel.UpperColor.GetG());
      digitalWrite(R2P, CurrentPixel.UpperColor.GetR());


      // Shift to register
      digitalWrite(ClkP, HIGH);
      digitalWrite(ClkP, LOW);
    }
  
    // Disable display
    digitalWrite(OEP, HIGH);
    digitalWrite(LP, HIGH);  
    
    if(row==0){digitalWrite(AP, LOW);}else{digitalWrite(AP, HIGH);}
    
    if(row==1){digitalWrite(BP, LOW);}else{digitalWrite(BP, HIGH);}
    
    if(row==2){digitalWrite(CP, LOW);}else{digitalWrite(CP, HIGH);}
    
    if(row==3){digitalWrite(DP, LOW);}else{digitalWrite(DP, HIGH);}
  
    // Enable Display
    digitalWrite(OEP, LOW);
    digitalWrite(LP, LOW);  
  }
  
}

/*void UpdateSerial(){

  Serial.println("Start");
  
  for(char row=0;row<DisplayBuffer.Rows;row++){
    
    for(char col=0;col<DisplayBuffer.Cols;col++){

      Serial.print(DisplayBuffer.GetData(row,col));
      Serial.print(';');
    }

    Serial.println();
  }
}
*/

void DrawSquare(char x, char y, char size, Color1 color){
  for (char row = 0; row < size; row++)
  {
    for (char col = 0; col < size; col++)
    {
      SetPixel(x+row,y+col,color);
    }
    
  }
  
}

void DrawCircle(char x, char y, char size, Color1 color){
  /*for (char row = 0; row < size; row++)
  {
    for (char col = 0; col < size; col++)
    {
      double distance = sqrt(pow(row-(size/2),2) + pow(col-(size/2),2));

      if(distance<=size/2){
        SetPixel(x-(size/2)+row,y-(size/2)+col,color);
      }else{
        SetPixel(x-(size/2)+row,y-(size/2)+col,Color1(1,0,0));
      }
    }
    
  }*/

  DrawCircle(x,y,size,color,Color1(0,0,0));
}

void DrawCircle(char x, char y, char size, Color1 frontColor, Color1 backColor){
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