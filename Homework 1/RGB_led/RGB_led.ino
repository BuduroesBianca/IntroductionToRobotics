const int ledPinGreen = 10;
const int ledPinRed = 11;
const int ledPinBlue = 9;

const int potPinRed = A0;
const int potPinBlue = A1;
const int potPinGreen = A2;

int potValueRed = 0;
int potValueBlue = 0;
int potValueGreen = 0;

int brightnessRed, brightnessGreen, brightnessBlue;

const int maxAnalogValue = 255, maxVoltageValue = 1023;

void setup() {
  pinMode(ledPinGreen,OUTPUT);
  pinMode(ledPinRed,OUTPUT);
  pinMode(ledPinBlue,OUTPUT);
  
  pinMode(potPinRed,INPUT);
  pinMode(potPinBlue,INPUT);
  pinMode(potPinGreen,INPUT);
}

void loop() {
  potValueRed = analogRead(potPinRed);
  potValueBlue = analogRead(potPinBlue);
  potValueGreen = analogRead(potPinGreen);

  brightnessRed = map(potValueRed,0,maxVoltageValue,0,maxAnalogValue);
  brightnessBlue = map(potValueBlue,0,maxVoltageValue,0,maxAnalogValue);
  brightnessGreen = map(potValueGreen,0,maxVoltageValue,0,maxAnalogValue);
  
  analogWrite(ledPinRed,brightnessRed);
  analogWrite(ledPinBlue,brightnessBlue);
  analogWrite(ledPinGreen,brightnessGreen);
}
