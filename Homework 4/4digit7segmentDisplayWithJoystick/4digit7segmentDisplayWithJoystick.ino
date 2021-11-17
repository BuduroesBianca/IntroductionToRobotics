#include <EEPROM.h>

const int dataPin = 12; //DS
const int latchPin = 11; //STCP
const int clockPin = 10; //SHCP

const int pinSW = 2; 
const int pinX = A0; 
const int pinY = A1;

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

bool dpState = LOW;
bool swState = LOW;
bool lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;

bool joyMoved = false;
bool joyMoved1 = false;
int digit = 0;
int minThreshold= 400;
int maxThreshold= 600;
int minThreshold1= 500;
int maxThreshold1= 700;
int currentDisplay = 0;

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int displayCount = 4;
int currentDisplayAddress = 4;

int digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

int valuesSaved[displayCount] = {
  0, 0, 0, 0
};

void setup() {
  pinMode(dataPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);

  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinX,INPUT);
  pinMode(pinY,INPUT);

  attachInterrupt(digitalPinToInterrupt(pinSW), editDigit, FALLING);

  for(int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  Serial.begin(9600);
}

bool switchDigit = false;
const int debounceInterval = 50;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long intervalBlink = 500;

void loop() {

  readValuesFromMemory();
  
  showAll();
  Serial.println(dpState);

  if(switchDigit == true) {
    xValue = analogRead(pinX);
  
    digit = valuesSaved[currentDisplay];
  
    if(xValue < minThreshold && joyMoved == false){
      joyMoved = true;
      digit--;
      if(digit < 0){
        digit = 9;
     }
    valuesSaved[currentDisplay] = digit;
    }
    
    if(xValue > maxThreshold && joyMoved == false){
      joyMoved = true;
      digit++;
      if(digit > 9){
        digit = 0;
      }
    valuesSaved[currentDisplay] = digit;
    }

    if(xValue > minThreshold && xValue < maxThreshold){
      joyMoved = false;
    }
  }
  else {
    yValue = analogRead(pinY);
  
    if(yValue < minThreshold && joyMoved == false){
      joyMoved = true;
      currentDisplay++;
    
    if(currentDisplay > 3){
      currentDisplay = 0;
    }
   }

    if(yValue > maxThreshold && joyMoved == false){
      joyMoved = true;
      currentDisplay--;
   
      if(currentDisplay < 0){
        currentDisplay = 3;
      }
    }

   if(yValue > minThreshold && yValue < maxThreshold){
    joyMoved = false;
    }
  }

  updateValuesInMemory();
}

void showAll() {
  for(int i = 0; i < 4; i++) {
    showDigits(i);
    
    if(i == currentDisplay){
      showDP();
    }
    else{
      writeReg(digitArray[valuesSaved[i]]);
    }
    delay(5);
  }
}

void editDigit() {
  static unsigned long lastDebounceTime = 0;

  if (millis() - lastDebounceTime > debounceInterval) {
    switchDigit = !switchDigit;
  }

  lastDebounceTime = millis();
}

void showDP() {
  if(switchDigit == true) {
    writeReg(digitArray[valuesSaved[currentDisplay]] + 1);
  }
  else{
  if (millis() - previousMillis >= intervalBlink){
    previousMillis = millis();
    dpState = !dpState;
  }
    if(dpState == LOW) {
       writeReg(digitArray[valuesSaved[currentDisplay]] + 1);
    }
    else{
       writeReg(digitArray[valuesSaved[currentDisplay]]);
    }
  }
}

void showDigits(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void readValuesFromMemory() {
  for (int i = 0 ; i < displayCount; i++) {
    valuesSaved[i] = EEPROM.read(i);
  }
  
  currentDisplay = EEPROM.read(currentDisplayAddress);
}

void updateValuesInMemory() {
  for (int i = 0 ; i < displayCount; i++) {
    EEPROM.update(i, valuesSaved[i]);
  }

  EEPROM.update(currentDisplayAddress, currentDisplay);
}

void writeReg(int digit) {
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}
