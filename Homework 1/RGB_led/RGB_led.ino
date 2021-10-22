const int ledPinGreen = 10;
const int ledPinRed = 11;
const int ledPinBlue = 9;

const int potPin0 = A0;
const int potPin1 = A1;
const int potPin2 = A2;

int potValue0 = 0;
int potValue1 = 0;
int potValue2 = 0;

void setup() {
  // put your setup code here, to run once:
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
  
  analogWrite(ledPinRed,potValue0/4);
  analogWrite(ledPinBlue,potValue1/4);
  analogWrite(ledPinGreen,potValue2/4);
}
