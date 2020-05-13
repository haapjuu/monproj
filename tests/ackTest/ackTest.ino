#include <Keypad.h>
#include<SPI.h>
#include<RF24.h>

const byte ROWS = 3;
const byte COLS = 3;

int RelayControlPin = 2;

String Password = "1234";
String tempPassword = "";
int i = 0;

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
  radio.setPayloadSize(32);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x74);
  radio.openWritingPipe(0xF0f0f0f0E1LL);
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.powerUp();
  
//added radio.setPayloadSize(32);
//added radio.setAutoAck(True);
//added radio.enableAckPayload();
}
//end of void setup

void loop() {
  A:
  i = 0;
  tempPassword = "";
  char key = keypad.getKey();

    if (key != NO_KEY) {
    Serial.println(key);
  }
  
  while (i < 4) {
  char key = keypad.getKey();
  if (key != NO_KEY){
    
    Serial.println(key);
    tempPassword += key;
    i++;

    if(tempPassword.startsWith("1",0)){ 
      } else if (tempPassword.startsWith("2",1)){
       } else if (tempPassword.startsWith("3",2)){
         } else if (tempPassword.startsWith("4",3)){
            } else {
                goto A;
                   }
}}
//end of while loop

  if (Password == tempPassword){
    setLocked(false);
    delay(5000);
    setLocked(true);
    goto A;
  } else {
    goto A;
  }
  delay(100);
}
//end of void loop

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
  
  if (radio.isAckPayloadAvailable()){
    returnedPL = []
    radio.read(returnedPL, radio.getDynamicPayloadSize())
    print("Our returned payload was {}".format(returnedPL))
    } else {
    print("No payload was received")
    time.sleep(1)
    }
  }
}