#include <Servo.h>
#include <Keypad.h>

//Define the keypad
const byte numRows = 4;
const byte numCols = 4;
Servo myServo;
int angle;
int switchState = 0;
int switchPin = 2;

//Door is locked by default
boolean locked = 1;

//Set code to open lock
const char* code = "1234";

//Define where input of code begins
int currentPosition = 0;

char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {9, 8, 7, 6};
byte colPins[numCols] = {5, 4, 3, 2};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  myServo.attach(10);
  Serial.begin(9600);
}

void loop() {

  char keypressed = myKeypad.getKey();
//  Serial.println(keypressed);
  if (keypressed == code[currentPosition] && currentPosition < 4)
    {
      ++currentPosition;
      if (currentPosition == 4)
      {
        //Todo: Unlock method
        Serial.println("Door unlocked");
        currentPosition = 0;
      }
    } //else {
      //Serial.println("Invalid code");   
      //delay(1000);
      //Serial.println("Resetting");
      //delay(1000);
      //currentPosition = 0;
  //  }

  }
