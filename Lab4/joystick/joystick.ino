const int pinSW = 10; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output
int switchValue;
int xValue = 0;
int yValue = 0;
void setup() {
  pinMode(pinSW, INPUT_PULLUP); //activate pull-up resistor on the
  pinMode(pinX,INPUT);
  pinMode(pinY,INPUT);
  // push-button pin
  // Start the serial communication.
  Serial.begin(9600);
}

void loop() {
  switchValue = digitalRead(pinSW);
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
 
  Serial.print("Switch:  ");
  Serial.print(switchValue);
  Serial.print("  |  ");
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print("  |  ");
  Serial.print("Y-axis: ");
  Serial.print(yValue);
  Serial.println("  |  ");
  delay(200);
}
