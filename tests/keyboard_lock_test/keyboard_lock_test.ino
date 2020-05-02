#include <Keypad.h>

const byte ROWS = 3;
const byte COLS = 3;
const int lockPin = 2;
const char* password = "2222";
int position = 0;



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
  pinMode(lockPin, OUTPUT);
  setLocked(true);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY){
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
    digitalWrite(lockPin, LOW);
    Serial.println("Locking");
  }
  else {
    digitalWrite(lockPin, HIGH);
    Serial.println("Unlocking");
  }
}
