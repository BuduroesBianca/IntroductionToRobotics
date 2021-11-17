#define NUMREADINGS 30

const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int pinBuzzer = 11;
int buzzerTone = 31;

int readings[NUMREADINGS];  
int index = 0;                           
int total = 0;
int average = 0;       

int senseLimit = 850; 
int probePin = 5; 
int val = 0;

const int segSize = 8;
const int noOfDigits = 10;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber(byte digit) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  buzzerTone = digit * 1000;
  tone(pinBuzzer, buzzerTone, 20);
}

void setup() {
  pinMode(probePin,INPUT);
  pinMode(pinBuzzer,OUTPUT);
  
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  
  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;   
  
  Serial.begin(9600);
}

void loop() {
  val = analogRead(probePin);  
  if(val >= 1){
    val = constrain(val, 1, senseLimit);  
    val = map(val, 1, senseLimit, 1, 1023);  
    total -= readings[index];              
    readings[index] = val; 
    total += readings[index];               
    index = (index + 1);                    

    if (index >= NUMREADINGS) {            
      index = 0;        
    }                   

    average = total / NUMREADINGS; 
    
    if (average > 0 and average < 90){                
      displayNumber(0);  
    }

    if (average > 90 and average < 150){               
      displayNumber(1);    
    }

    if (average > 150 and average < 250 ){
      displayNumber(2);    
    }

    if (average > 250 and average < 350){
      displayNumber(3);  
    }

    if (average > 350 and average < 450){
      displayNumber(4);   
    }

    if (average > 450 and average < 550){
      displayNumber(5);    
    }

    if (average > 550 and average < 650){
      displayNumber(6);    
    }

    if (average > 650 and average < 750){
      displayNumber(7);   
    }

    if (average > 750 and average < 850){
      displayNumber(8);   
    }

    if (average > 850){
      displayNumber(9);  
    }
    Serial.println(average); 
    delay(40);
  }        
}
