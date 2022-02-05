

uint64_t row1[128];
uint64_t temp;

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
int row = 0;
uint8_t i;
int pixel=0;
int color = 1;

const int rows = 8;
const int cols = 32;

int DisplayBuffer [rows/2][cols*2];

//Buffer DisplayBuffer(rows/2,cols*2);

const int LookUpTable [2][cols] = 
  {
    {48,49,50,51,52,53,54,55,32,33,34,35,36,37,38,39,16,17,18,19,20,21,22,23,0,1,2,3,4,5,6,7},
    {63,62,61,60,59,58,57,56,47,46,45,44,43,42,41,40,31,30,29,28,27,26,25,24,15,14,13,12,11,10,9,8}
  };


void setup() {
  //set pins to output so you can control the shift register
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
  row=0;
  temp =  1;  
  
  //------------------------Paste here:
  row1[0]=0x0000000000000000FFC0FF00FF00FF3B;
  row1[1]=0X0000000000000000FFDFFFFFFFFFFFFB;
  row1[2]=0x00000000000000000CDF00FF00FFC0FB;
  row1[3]=0x00000000000000000CCF00000000B13B;
  row1[4]=0x00000000000000007CC000000000B31B;
  row1[5]=0x00000000000000003CC000000000B303;
  row1[6]=0x00000000000000001CFF00FF00FFB3FF;
  row1[7]=0x00000000000000000CFF00FF00FFB3FF;
  //----------------------------up to here


  ClearBuffer();

  
  Serial.begin(9600);

  
}

void loop() {

  color=1;
  for(int i = 0; i<rows*2; i++){
    for(int j = 0; j<cols; j++){

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
  
  ClearBuffer();

}


void ClearBuffer(){
  for(int i=0;i<rows/2;i++){
    for(int j=0;j<cols*2;j++){
      DisplayBuffer[i][j]=0;
    }
  }
}

void SetPixel(int x, int y,int value){

  int BufferX = (x & B011);
  int BufferY = LookUpTable[(x & B100)>>2][y];

  int ValueFilter;

  if(x & B1000){
    ValueFilter = B111000;
  }else{
    ValueFilter = B000111;
  }

  DisplayBuffer[BufferX][BufferY] &= ~(ValueFilter);
  DisplayBuffer[BufferX][BufferY] |= (value & ValueFilter);

}

void UpdateDisplay(){
  
  for(int i=0;i<rows/2;i++){
    for(int j=0;j<cols*2;j++){

      int CurrentPixel = DisplayBuffer[i][j];
    
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
  
  for(int i=0;i<rows/2;i++){
    
    for(int j=0;j<cols*2;j++){

      Serial.print(DisplayBuffer[i][j]);
      Serial.print(';');
    }

    Serial.println();
  }
  
}