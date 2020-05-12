#include <Keypad.h>
#include<SPI.h>
#include<RF24.h>

const byte ROWS = 3;
const byte COLS = 3;

int RelayControlPin = 2;

const char* password = "2222";
int position = 0;

RF24 radio(9, 10);


char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
};

byte rowPins[ROWS] = {8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  Serial.begin(9600);
  pinMode(RelayControlPin, OUTPUT);
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

  if (key != NO_KEY) {
    Serial.println(key);
  }

  if (key == password[position]) {
    position ++;

  }



  if (position == 4) {
    setLocked(false);
    delay(5000);
    setLocked(true);
    position = 0;
  }


  delay(100);
}

void setLocked(int locked) {
  if (locked) {
    digitalWrite(RelayControlPin, LOW);
    Serial.println("Locking");
  }
  else {
    digitalWrite(RelayControlPin, HIGH);
    Serial.println("Unlocking");
    const char unlockedmessage[] = "Unlocked";
    radio.write(&unlockedmessage, sizeof(unlockedmessage));
  }
}
