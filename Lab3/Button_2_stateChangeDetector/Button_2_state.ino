const int pushButton = 2;
const int ledPin = 3;

bool buttonState = LOW;
bool ledState = LOW;
bool lastButtonState = LOW;

int counter = 0;

void setup() {
  pinMode(pushButton,INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(pushButton);
  if(buttonState != lastButtonState && buttonState == LOW){
    counter++;
    ledState = !ledState;
    digitalWrite(ledPin,ledState);
  }
  lastButtonState = buttonState;
  Serial.println(counter);

}
