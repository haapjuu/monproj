# monproj
Monialaprojekti PRO4TN004-3005
A simple Arduino and Raspberry Pi based access control system built for a course at Haaga-Helia University of Applied Sciences.
The aim of the project was to create a system where the Arduino controls a solenoid lock with a keypad and then transmits a signal using a nrf24L01+ transmitter to a Raspberry Pi which logs the event and publishes the log on a webserver.

## Project Team
- Juuso Haapaniemi - Project manager
- Konsta Toivonen - Tech lead

# 1. Testing components
The first goal for our project was to test each individual component to see that they work and to get basic knowledge on how to use them.
All of our code used for testing can be found from "tests" -folder in our project.

## 1.1 Servo
Testing that the servo works using nappimoottori.ino -file:
```
#include <Servo.h>
Servo myServo;
int angle;
int switchState = 0;
int switchPin = 2;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  pinMode (switchPin, INPUT);
}

void loop() {
  switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    angle = 0;
  } else {
    angle = 180;


  }
  myServo.write(angle);
  delay(15);

}
````

Our original servo did not work as we expected. It did not move and only made a buzzing noise.
We changed the servo to another one, which worked, but later on we ended up using a solenoid lock. More on that later.
