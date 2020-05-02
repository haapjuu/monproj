#include <Servo.h>
#include <Keypad.h>
#include<SPI.h>
#include<RF24.h>

Servo servo_Motor;
const char* password = "2222";
int position = 0;
const byte ROWS = 4;
const byte COLS = 3;
RF24 radio(9, 10);

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  servo_Motor.attach(8);
  Serial.begin(9600);
  setLocked(true);

  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
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
    servo_Motor.write(10);
    Serial.println("Locking");
  }
  else {
    servo_Motor.write(170);
    Serial.println("Unlocking");
  }
}
