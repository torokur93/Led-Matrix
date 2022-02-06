#include "src/Buffer.h"

#define ROWS 8
#define COLS 32

uint64_t row1[128];
uint64_t temp;

// Pin definitions

int LP = 10;            // Latch Pin
int ClkP = 8;         // Clock Pin
int R1P = 2;          // R1 Pin
int B1P = 4;          // B1 Pin
int G1P = 3;           // G1 Pin
int R2P = 5;           // R2 Pin
int B2P = 7;           // B2 Pin
int G2P = 6;           // G2 Pin
int AP = A0;            // A Pin
int BP = A1;            // B Pin
int CP = A2;            // C Pin
int DP = A3;            // D Pin
int OEP = 9;          // OE Pin

// Variable definitions

int row = 0;
uint8_t i;
int pixel=0;
int color = 1;

//char rows = 8;
//const char c_cols = 32;

//char cols = 32;

//int DisplayBuffer [rows/2][cols*2];

Buffer DisplayBuffer(ROWS/2,COLS*2);

//Array2D LookUpTable(2,cols);

/*char LookUpTable [2][32] = 
  {
    {48,49,50,51,52,53,54,55,32,33,34,35,36,37,38,39,16,17,18,19,20,21,22,23,0,1,2,3,4,5,6,7},
    {63,62,61,60,59,58,57,56,47,46,45,44,43,42,41,40,31,30,29,28,27,26,25,24,15,14,13,12,11,10,9,8}
  };
*/

void setup() {
  //set pins to output so you can control the shift register
  InitalizePins();
  row=0;
  temp =  1;  
  
  DisplayBuffer.ClearData();

  
  Serial.begin(9600);
  
}

void loop() {

  color=1;
  for(int i = 0; i<ROWS*2; i++){
    for(int j = 0; j<COLS; j++){

      SetPixel(i,j,color | (color<<3));
      UpdateDisplay();
      
    }
    
    if(color == 7)
    {
      color=1;
    }else{
      color++;
    }
  }
  //UpdateDisplay();
  //UpdateSerial();
  
  DisplayBuffer.ClearData();

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


void SetPixel(char x, char y,char value){

  char BufferX = (x & B011);
  //char BufferY = LookUpTable[(x & B100)>>2][y];
  char BufferY = TransformY((x & B100)>>2,y);

  char ValueFilter;

  if(x & B1000){
    ValueFilter = B111000;
  }else{
    ValueFilter = B000111;
  }
  DisplayBuffer.ClearBits(BufferX,BufferY,ValueFilter);
  DisplayBuffer.SetBits(BufferX,BufferY,value & ValueFilter);

}

char TransformY(char x, char y){
  char SegmentID = y / 8;
  char BitID = y % 8;

  if(x){
    return COLS - 1 - y - SegmentID * 8;
  }else{
    return COLS - 16 -SegmentID * 16 + BitID;
  }

}


void UpdateDisplay(){
  
  for(char i=0;i<ROWS/2;i++){
    for(char j=0;j<COLS*2;j++){

      char CurrentPixel = DisplayBuffer.GetData(i,j);
    
      // Lower Half
      digitalWrite(B1P, CurrentPixel & B00000001);
      digitalWrite(G1P, (CurrentPixel>>1) & B00000001);
      digitalWrite(R1P, (CurrentPixel>>2) & B00000001);
      // Higher Half
      digitalWrite(B2P, (CurrentPixel>>3) & B00000001);
      digitalWrite(G2P, (CurrentPixel>>4) & B00000001);
      digitalWrite(R2P, (CurrentPixel>>5) & B00000001);

      // Shift to register
      digitalWrite(ClkP, HIGH);
      digitalWrite(ClkP, LOW);
    }
  
    // Disable display
    digitalWrite(OEP, HIGH);
    digitalWrite(LP, HIGH);  
    
    if(i==0){digitalWrite(AP, LOW);}else{digitalWrite(AP, HIGH);}
    
    if(i==1){digitalWrite(BP, LOW);}else{digitalWrite(BP, HIGH);}
    
    if(i==2){digitalWrite(CP, LOW);}else{digitalWrite(CP, HIGH);}
    
    if(i==3){digitalWrite(DP, LOW);}else{digitalWrite(DP, HIGH);}
  
    // Enable Display
    digitalWrite(OEP, LOW);
    digitalWrite(LP, LOW);  
  }
  
}


void UpdateSerial(){

  Serial.println("Start");
  
  for(int i=0;i<ROWS/2;i++){
    
    for(int j=0;j<COLS*2;j++){

      Serial.print(DisplayBuffer.GetData(i,j));
      Serial.print(';');
    }

    Serial.println();
  }
  
}
