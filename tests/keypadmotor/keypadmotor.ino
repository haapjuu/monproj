#include <Servo.h>
#include <Keypad.h>

const byte numRows = 4;
const byte numCols = 4;
Servo myServo;
int angle;
int switchState = 0;
int switchPin = 2;

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
  if (keypressed != NO_KEY)
  {
    Serial.println(keypressed);
    angle = 0;
    myServo.write(angle);
    delay(15);
    Serial.println("Turning servo forwards");
  } else {
    angle = 180;
    myServo.write(angle);
    delay(15);
    Serial.println("Turning servo backwards");
  }



}
