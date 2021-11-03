const int ledGreenPin = 6;
const int ledYellowPin = 5;
const int ledRedPin = 3;

const int ledGreenPasserPin = 10;
const int ledRedPasserPin = 9;

const int pushButton = 2;

const int buzzerPin = 11;

bool greenCarState;
bool yellowCarState;
bool redCarState;
bool redPasserState;
bool greenPasserState;
bool buttonState = LOW;

bool reading = LOW;
bool lastReading = LOW;

int lastDebounceTimer = 0;
const int debounceInterval = 50;

int buzzerTone = 1000;
int buzzerDuration = 30;

unsigned long startTime = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

const long intervalBlink = 500;
const long intervalBuzzer = 1000;

const int state1Interval = 10000;
const int state2Interval = 13000;
const int state3Interval = 23000;
const int state4Interval = 28000;

void setup() {
  pinMode(pushButton,INPUT_PULLUP);
  pinMode(ledGreenPin,OUTPUT);
  pinMode(ledYellowPin,OUTPUT);
  pinMode(ledRedPin,OUTPUT);
  pinMode(ledGreenPasserPin,OUTPUT);
  pinMode(ledRedPasserPin,OUTPUT);
  
  Serial.begin(9600);

  digitalWrite(ledGreenPin,HIGH);
  digitalWrite(ledRedPasserPin,HIGH);
}

void loop()
{
  
  reading = digitalRead(pushButton);
  Serial.println(reading);

  if(reading != lastReading){
    lastDebounceTimer = millis();
  }

  if(millis()-lastDebounceTimer > debounceInterval){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState == LOW){
        startTime = millis();
        lightsFlow();
      }
    }
  }
  
  lastReading = reading;
}

void lightsFlow(){

  bool Run = true;
  while(Run == true){
    
   unsigned long checkTime = millis();
   unsigned long elapsedTime = checkTime - startTime;
   
  if (elapsedTime < state1Interval){
     redCarState = LOW;             
     yellowCarState = LOW;            
     greenCarState = HIGH; 
     greenPasserState = LOW; 
     redPasserState = HIGH; 
  }
  
  if (elapsedTime > state1Interval && elapsedTime < state2Interval){
      redCarState = LOW;             
      yellowCarState = HIGH;            
      greenCarState = LOW ;   
      greenPasserState = LOW; 
      redPasserState = HIGH; 
    }
  
   if (elapsedTime > state2Interval && elapsedTime < state3Interval){
    redCarState = HIGH;             
    yellowCarState = LOW;            
    greenCarState = LOW ;   
    greenPasserState = HIGH; 
    redPasserState = LOW; 
    
    currentMillis = millis();
    
    if (currentMillis - previousMillis >= intervalBuzzer){
      previousMillis = currentMillis;
        tone(buzzerPin, buzzerTone, buzzerDuration);
      }
    }
  
    if (elapsedTime > state3Interval && elapsedTime < state4Interval){
      
      currentMillis = millis();
    
      if (currentMillis - previousMillis >= intervalBlink){
        previousMillis = currentMillis;
        tone(buzzerPin, buzzerTone, buzzerDuration);
          if(greenPasserState ==LOW) {
            greenPasserState =HIGH;
          }
          else{
            greenPasserState =LOW;
          }
       }
    }
    
    if (elapsedTime > state4Interval){
      redCarState = LOW;             
      yellowCarState = LOW;            
      greenCarState = HIGH ;   
      greenPasserState = LOW; 
      redPasserState = HIGH; 
      
      buttonState = digitalRead(pushButton);
      Run = false;
  }
  digitalWrite(ledRedPin,redCarState);
  digitalWrite(ledGreenPin,greenCarState);
  digitalWrite(ledYellowPin,yellowCarState);
  digitalWrite(ledRedPasserPin,redPasserState);
  digitalWrite(ledGreenPasserPin,greenPasserState);
  }
}
