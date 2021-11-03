# IntroductionToRobotics
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

## Homework #1

### Components
RBG led (1 minimum), potentiometers (3 minimum), resistors and wires (per logic).

### Technical Task
Use a separat potentiometer in controlling each of the color of the RGB led (Red,Green and Blue). The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led).

**The code can be found** [here](https://github.com/BuduroesBianca/IntroductionToRobotics/blob/main/Homework%201/RGB_led/RGB_led.ino).
</br>

### Picture of the setup

<img src="Homework 1/IMG_2784.JPG" width="500" height = "310">

### Video showcasing the functionality

Video can be found [here](https://www.youtube.com/watch?v=NjVsNNJ_Mvk).

## Homework #2

### Components
5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)

### Technical Task
Building the traffic lights for a crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).
**The system has the following states:**
1. **State 1** (default, reinstated after state 4 ends): green light for cars,
red light for people, no sounds. Duration: indefinite, changed by
pressing the button.
2. **State 2** (initiated by counting down 10 seconds after a button press):
the light should be yellow for cars, red for people and no sounds.
Duration: 3 seconds.
3. **State 3** (initiated after state 2 ends): red for cars, green for people and
a beeping sound from the buzzer at a constant interval. Duration:
10 seconds.
4. **State 4** (initiated after state 3 ends): red for cars, blinking green
for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. This state should last 5
seconds

**The code can be found** [here](https://github.com/BuduroesBianca/IntroductionToRobotics/blob/main/Homework%203/Homework_3.ino).
</br>

### Picture of the setup

<img src="Homework 3/IMG_2845.jpg" width="600" height = "461">

### Video showcasing the functionality

Video can be found [here](https://www.youtube.com/watch?v=MHa8Tr0oopY).

