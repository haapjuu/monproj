#include<SPI.h>
#include<RF24.h>
#include <nRF24L01.h>

// ce, csn pins
RF24 radio(9, 10);
 
void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
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
