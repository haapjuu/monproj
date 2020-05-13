# monproj
Monialaprojekti PRO4TN004-3005
A simple Arduino and Raspberry Pi based access control system built for a course at Haaga-Helia University of Applied Sciences.
The aim of the project was to create a system where the Arduino controls a solenoid lock with a keypad and then transmits a signal using a nrf24L01+ transmitter to a Raspberry Pi which logs the event and publishes the log on a webserver.

## Project Team
- Juuso Haapaniemi - Project manager
- Konsta Toivonen - Tech lead

# 1. Testing components
The first goal for our project was to test each individual component to see that they work and to get basic knowledge on how to use them.
All of our code used for testing can be found from "tests" -folder in our project.

## 1.1 Servo
Testing that the servo works using nappimoottori.ino -file:

```
#include <Servo.h>
Servo myServo;
int angle;
int switchState = 0;
int switchPin = 2;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  pinMode (switchPin, INPUT);
}

void loop() {
  switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    angle = 0;
  } else {
    angle = 180;


  }
  myServo.write(angle);
  delay(15);

}
````

Our original servo did not work as we expected. It did not move and only made a buzzing noise.
We changed the servo to another one, which worked, but later on we ended up using a solenoid lock. More on that later.

## 1.2 Keypad
Next up: testing out our keypad.
Using the file keypad.ino:
```

#include <Keypad.h>

const byte numRows = 4;
const byte numCols = 4;

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

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
  {
    Serial.println(keypressed);
  }
}

```
In this example we used all 4x4 keys available on the keypad.
Later on we realized that our Arduino Uno did not have enough DigitalPins, so we ended up using only 3x3 keys.
This will be demonstrated later on.

##1.3 Keypad & Servo working together
Moving our servo using our keypad.
Created also our first iteration for a system using pincode to unlock the door.
File used: keypad_servo_test.ino:

```
#include <Keypad.h>
#include <Servo.h>

Servo servo_Motor;
const char* password = "7856";
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  servo_Motor.attach(11);
  setLocked(true);
}
void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }

  if (key == '*') {
      position = 0;
      setLocked(true);
  }

  if (key == password[position]) {
    position ++;
  }

  if (position == 4) {
    setLocked(false);
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
```
When the user enters the code 7856 on the keypad the servo moves 90°.
The servo turns back 90° when * is pressed on the keypad.

## 1.4 Installing and configuring Raspberry Pi
Created a bootable MicroSD memorycard for Raspberry Pi 3B+ using Rufus and Raspbian Buster Lite.
We booted up the Pi and connected it to a monitor so we could enable SSH on it using the following command:  
``
sudo raspi-config
``  
In raspi-config we opened option 5: Interfacing Options > P2: SSH > Yes.  
After enabling SSH on the Pi, we used the following command to create a new user:  
``
sudo adduser konsta
``  
and added the user to the groups "sudo" and "admin":  
``
sudo adduser konsta sudo
sudo adduser konsta admin
``  
Then we locked user Pi using commands:  
``
sudo usermod --lock Pi
``  
We copied our SSH key to the Pi:  
``
ssh-copy-id 192.168.1.180
`` 

Then we disabled password log in by modifying line "PasswordAuthentication yes" to "PasswordAuthentication no"  
``
sudoedit /etc/ssh/sshd_config
``
Enabled firewall:  
``
sudo apt update && sudo apt install ufw -y  
sudo ufw allow 22/tcp  
sudo ufw allow 80/tcp  
sudo ufw allow 443/tcp  
sudo ufw enable
``

## 1.5 Radio Transceiver Module
Testing the communication between Arduino and Raspberry PI using radio transceiver modules.
Testing and actual finished project uses BLavery's Python2/3 lib_nrf24 library for NRF24L01+ Transceivers with an addional fix line below.
`self.spidev.max_speed_hz=4000000`

This extra line is added into lib_nrf24.py line 373 between
```
self.spidev.open(0, csn_pin)
self.ce_pin = ce_pin
```


radio.ino code that was used to test sending data over to Raspberry.
```
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(0x76);
  radio.openWritingPipe(address);
  radio.enableDynamicPayloads();
  radio.powerUp();
  radio.stopListening();
}

void loop(void){
  Serial.println("Attempting to send data");
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  Serial.println("Sending message Hello World");
  delay(1000);
}
```
ReceiveArduino.py code that was used to test receiving data from Arduino.
```
import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev

GPIO.setmode(GPIO.BCM)

pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]

radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)

radio.setPayloadSize(32)
radio.setChannel(0x76)
radio.setDataRate(NRF24.BR_1MBPS)
radio.setPALevel(NRF24.PA_MIN)

radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openReadingPipe(1, pipes[1])
radio.printDetails()
radio.startListening()

while(1):
    # ackPL = [1]
    while not radio.available(0):
        time.sleep(1 / 100)
    receivedMessage = []
    radio.read(receivedMessage, radio.getDynamicPayloadSize())
    print("Received: {}".format(receivedMessage))

    print("Translating the receivedMessage into unicode characters")
    string = ""
    for n in receivedMessage:
        # Decode into standard unicode set
        if (n >= 32 and n <= 126):
            string += chr(n)
    print("Out received message decodes to: {}".format(string))
```
