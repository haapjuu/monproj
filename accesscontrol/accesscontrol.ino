#include <Servo.h>
#include <Keypad.h>
#include<SPI.h>
#include<RF24.h>

Servo servo_Motor;
const char* password = "2222";
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
RF24 radio(9, 10);

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  servo_Motor.attach(8);
  Serial.begin(9600);
  setLocked(true);

  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x74);
  radio.openWritingPipe(0xF0f0f0f0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();



}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }

  if (key == '*') {
      position = 0;
      setLocked(true);
      const char lockedmessage[] = "Locked";
      radio.write(&lockedmessage, sizeof(lockedmessage));
  }

  if (key == password[position]) {
    position ++;
  }

  if (position == 4) {
    setLocked(false);
    const char unlockedmessage[] = "Unlocked";
    radio.write(&unlockedmessage, sizeof(unlockedmessage));
  }
  delay(100);
}

void setLocked(int locked) {
  if (locked) {
    servo_Motor.write(0);
    Serial.println("Locking");
  }
  else {
    servo_Motor.write(90);
    Serial.println("Unlocking");
  }
}
