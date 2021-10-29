const int pushButton = 2;
const int ledPin = 3;

bool buttonState = LOW;
bool ledState = LOW;

bool reading = LOW;
bool lastReading = LOW;

int lastDebounceTimer = 0;
const int debounceInterval = 50;

void setup() {
  pinMode(pushButton,INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  reading = digitalRead(pushButton);

  if(reading != lastReading){
    lastDebounceTimer = millis();
  }

  if(millis()-lastDebounceTimer > debounceInterval){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState == HIGH){
        ledState = !ledState;
      }
      digitalWrite(ledPin,ledState);
    }
  }
  lastReading = reading;
}
