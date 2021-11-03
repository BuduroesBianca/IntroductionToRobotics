const int ledGreen = 6;
const int ledYellow = 5;
const int ledRed = 3;

const int ledGreenPasser = 10;
const int ledRedPasser = 9;

int greenState;
int yellowState;
int redState;
int redPasserState;
int greenPasserState;

const int pushButton = 2;

bool buttonState = LOW;

bool reading = LOW;
bool lastReading = LOW;

int lastDebounceTimer = 0;
const int debounceInterval = 50;

const int buzzerPin = 11;
int buzzerTone = 1000;

const long interval = 27000;


void setup() {
  pinMode(pushButton,INPUT_PULLUP);
  pinMode(ledGreen,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreenPasser,OUTPUT);
  pinMode(ledRedPasser,OUTPUT);
  
  Serial.begin(9600);

  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledRedPasser,HIGH);

}

unsigned long offAt = 0;

void loop()
{
  Serial.println(digitalRead(pushButton));
  reading = digitalRead(pushButton);

  if(reading != lastReading){
    lastDebounceTimer = millis();
  }

  if(millis()-lastDebounceTimer > debounceInterval){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState == LOW){
        State2();
      }
    }
  }
  
  lastReading = reading;
  
}
unsigned long previousMillis =0;
unsigned long previousMillisB =0;
unsigned long startTime =0;
const long intervalBlink =500;
const long intervalBuzzer1  =1000;
const long intervalBuzzer2  =500;
unsigned long currentMillis = 0;
unsigned long currentMillisB = 0;

void State2(){
  
  int ok = 1;
  while(ok){
  unsigned long checkTime = millis();
  unsigned long elapsedTime = checkTime - startTime;
  if(elapsedTime > interval) {

    startTime = checkTime;   

  }
  
  // verdele de la masini mai sta aprins inca 10 sec dupa apasare buton
  if (elapsedTime < 10000){
    redState = LOW;             
    yellowState = LOW;            
    greenState = HIGH; 
    greenPasserState = LOW; 
    redPasserState = HIGH; 
  }
  
  // aprindem galbenul de la masini pt 3 secunde
  if (elapsedTime > 10000 && elapsedTime < 13000){
    redState = LOW;             
    yellowState = HIGH;            
    greenState = LOW ;   
    greenPasserState = LOW; 
    redPasserState = HIGH; 
  }
  //aprindem rosu de la masini si verde de la pietoni pt 10 sec
   if (elapsedTime > 13000 && elapsedTime < 23000){
    redState = HIGH;             
    yellowState = LOW;            
    greenState = LOW ;   
    greenPasserState = HIGH; 
    redPasserState = LOW; 
    
    currentMillisB =millis();
    
    if(currentMillisB - previousMillisB >= intervalBuzzer1){
      previousMillisB = currentMillisB;
        tone(buzzerPin, buzzerTone, 30);
      }
  }

   if (elapsedTime > 23000 && elapsedTime <28000){
    currentMillis =millis();
    
    if(currentMillis - previousMillis >= intervalBlink){
      previousMillis = currentMillis;
        if(greenPasserState ==LOW) {
          greenPasserState =HIGH;
        }
        else{
          greenPasserState =LOW;
        }
      }
      currentMillisB =millis();
    
    if(currentMillisB - previousMillisB >= intervalBuzzer2){
      previousMillisB = currentMillisB;
        tone(buzzerPin, buzzerTone, 30);
      }
    }
    if (elapsedTime > 26000){
    redState = LOW;             
    yellowState = LOW;            
    greenState = HIGH ;   
    greenPasserState = LOW; 
    redPasserState = HIGH; 
    buttonState = HIGH;
    ok=0;
  }
  
  
  digitalWrite(ledRed,redState);
  digitalWrite(ledGreen,greenState);
  digitalWrite(ledYellow,yellowState);
  digitalWrite(ledRedPasser,redPasserState);
  digitalWrite(ledGreenPasser,greenPasserState);
  
  }
}
