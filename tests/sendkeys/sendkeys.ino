#include <Servo.h>
#include <Keypad.h>
#include<SPI.h>
#include<RF24.h>

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
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x74);
  radio.openWritingPipe(0xF0f0f0f0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();



}

void loop() {
  char key = keypad.getKey();

  while (key != NO_KEY){
    Serial.println(key);
    const char* keypressed = key;
    radio.write(&keypressed, sizeof(keypressed));
    delay(100);
    char key2 = keypad.getKey();
      if (key2 != NO_KEY){
       break; 
     }
    }

  
}
