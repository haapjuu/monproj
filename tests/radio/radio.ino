#include<SPI.h>
#include<RF24.h>
#include <nRF24L01.h>

// ce, csn pins
RF24 radio(9, 10);
const byte address = 0xE0E0F1F1E0LL;

void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(0x76);
  radio.openWritingPipe(address);
  radio.enableDynamicPayloads();
  radio.powerUp();
  radio.stopListening();

}

void loop(void){
  Serial.println("Attempting to send data");
  const char text[] = "Thist is a test, please ignore";
  radio.write(&text, sizeof(text));
  Serial.println("Sending data");
  delay(1000);

}
