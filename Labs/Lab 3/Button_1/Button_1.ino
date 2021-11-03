
const int pushButton = 2;
const int ledPin = 3;

bool buttonState = LOW;
bool ledState = LOW;

void setup() {
  pinMode(pushButton,INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  buttonState = digitalRead(pushButton);
  ledState = !buttonState;
  digitalWrite(ledPin,ledState);
  Serial.println(buttonState);

}
