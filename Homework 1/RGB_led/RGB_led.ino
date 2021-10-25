const int ledPinGreen = 10;
const int ledPinRed = 11;
const int ledPinBlue = 9;

const int potPin0 = A0;
const int potPin1 = A1;
const int potPin2 = A2;

int potValue0 = 0;
int potValue1 = 0;
int potValue2 = 0;

int brightnessRed, brightnessGreen, brightnessBlue;

const int maxAnalogValue = 255, maxVoltageValue = 1023;

void setup() {
  pinMode(ledPinGreen,OUTPUT);
  pinMode(ledPinRed,OUTPUT);
  pinMode(ledPinBlue,OUTPUT);
  
  pinMode(potPin0,INPUT);
  pinMode(potPin1,INPUT);
  pinMode(potPin2,INPUT);
}

void loop() {
  potValue0 = analogRead(potPin0);
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);

  brightnessRed = map(potValue0,0,maxVoltageValue,0,maxAnalogValue);
  brightnessBlue = map(potValue1,0,maxVoltageValue,0,maxAnalogValue);
  brightnessGreen = map(potValue2,0,maxVoltageValue,0,maxAnalogValue);
  
  analogWrite(ledPinRed,brightnessRed);
  analogWrite(ledPinBlue,brightnessBlue);
  analogWrite(ledPinGreen,brightnessGreen);
}
