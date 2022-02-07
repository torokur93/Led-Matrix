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

// Constants

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

// Variable definitions

char currentRow = 0;

int counter=0;
char increment = -16;

Buffer DisplayBuffer(ROWS/4,COLS*2);

void setup() {
  
  InitalizePins();
  SetupInterrupt();
  
  DisplayBuffer.ClearData();

  Serial.begin(9600);

}

void loop() {

    Color1 pb_bck(0,1,0);

    if(counter>5000){
      if (counter>6500)
      {
        pb_bck = Color1(1,0,0);
      }else{
        pb_bck = Color1(1,1,0);
      }
    }

    DrawRectBorder(0, 0, 16, 26,Color1(1,1,1));
    DrawProgressBar(1,1,14,24,pb_bck,Color1(0,0,0),(float)counter/7200,1);
    
    DrawNumber(14,26,counter,Color1(0,0,1),1);

    if(counter == 7200 || counter == 0){
      increment = -increment;
    }
  //UpdateSerial();
  
  counter += increment;
  delay(100);
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

  if(x & B1000){
    DisplayBuffer.SetUpperData(BufferX, BufferY, value);
  }else{
    DisplayBuffer.SetLowerData(BufferX, BufferY, value);
  }

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
  
  for(char col=0;col<DisplayBuffer.Cols;col++){

    ColorDouble CurrentPixel = DisplayBuffer.GetData(currentRow,col);

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
    
    if(currentRow==0){digitalWrite(AP, LOW);}else{digitalWrite(AP, HIGH);}
    
    if(currentRow==1){digitalWrite(BP, LOW);}else{digitalWrite(BP, HIGH);}
    
    if(currentRow==2){digitalWrite(CP, LOW);}else{digitalWrite(CP, HIGH);}
    
    if(currentRow==3){digitalWrite(DP, LOW);}else{digitalWrite(DP, HIGH);}
  
    // Enable Display
    digitalWrite(OEP, LOW);
    digitalWrite(LP, LOW);  

    if(currentRow<DisplayBuffer.Rows){
      currentRow++;
    }else{
      currentRow=0;
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
  DrawRect(x, y, size, size, color);
}

void DrawRect(char x, char y, char height, char width, Color1 color){
  for (char row = 0; row < height; row++)
  {
    for (char col = 0; col < width; col++)
    {
      SetPixel(x+row,y+col,color);
    }
    
  }
}

void DrawRectBorder(char x, char y, char height, char width, Color1 color){
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


void DrawCircle(char x, char y, char size, Color1 color){
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

void DrawDigit(char x, char y, char digit, Color1 color, bool orientation){

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
        SetPixel(x_Trans,y_Trans,Color1(0,0,0));
      }
    }
    
  }
}

void DrawNumber(char x, char y, int number, Color1 color, bool orientation){
  
  char x_Trans = x;
  char y_Trans = y;

  bool lastLeadingZero = true;

  number %= 10000;

  for (char digit = 0; digit < 4; digit++)
  {
    if (orientation)
    {
      x_Trans = x + (digit * -4);
    }else{
      y_Trans = y + (digit * 4);
    }

    unsigned int currentDigitValue = ((unsigned int)(number/pow(10,3-digit))) % 10;

    if(!(lastLeadingZero && (currentDigitValue == 0))){
      DrawDigit(x_Trans,y_Trans,currentDigitValue,Color1(0,0,1),orientation);
      lastLeadingZero = false;
    }
  }
}

void DrawProgressBar(char x, char y,char height, char width, Color1 barColor, Color1 bgColor, float progress, bool orientation){
  
  if(orientation){
    DrawRect(x,y,height,(char)(width*progress),barColor);
    DrawRect(x,y+(char)(width*progress),height,width-(char)(width*progress),bgColor);
  }else{
    DrawRect(x,y,(char)(height*progress),width,barColor);
    DrawRect(x+(char)(height*progress),y,height-(char)(width*progress),width,bgColor);
  }
}


// intterrupts
void SetupInterrupt(){
  cli();
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 40;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts

}

ISR(TIMER1_COMPA_vect){
  UpdateDisplay();
}