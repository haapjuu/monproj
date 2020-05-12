#include <Keypad.h>
int sensor = 11;
int buzzer = 10;
int red = 12;
int i = 0;
String Pass = "1331";
String tempPass = "";

const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};




byte rowPins[rows] = {8, 7, 6, 9}; //connect to the row pinouts of the keypad
byte colPins[cols] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void setup() {
pinMode(sensor, INPUT);
pinMode (buzzer, OUTPUT);
StartingBuzz();
keypad.waitForKey();
digitalWrite(red,HIGH);
digitalWrite(buzzer,HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(60000);
}

void StartingBuzz()
{
digitalWrite(buzzer, HIGH);
delay(125);
digitalWrite(buzzer, LOW);
delay(125);
digitalWrite(buzzer, HIGH);
delay(125);
digitalWrite(buzzer, LOW);
delay(125);
digitalWrite(buzzer,HIGH);
delay(125);
digitalWrite(buzzer, LOW);
  }

void UnlockBuzz()
{
  delay(200);
       tone(buzzer,3250,200);
       delay(300);
       tone(buzzer,3500,200);
       delay(300);
       tone(buzzer,4000,200);
  }

void loop() {
  i=0;//resets the password-checking loop.
  tempPass = "";//resets the guessed password.
  char state = digitalRead(sensor);
  if (state == HIGH)
  {
    digitalWrite(buzzer, HIGH);
    A:
    {
    while(i < 4)
    {
    char key = keypad.getKey();
    if(key != NO_KEY)
    {
      tempPass += key;
      i++;
      }
    }
    }
    if(Pass == tempPass)
    {
      digitalWrite(buzzer, LOW);
      digitalWrite(red, LOW);
      UnlockBuzz();
      keypad.waitForKey();
      digitalWrite(buzzer,HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      digitalWrite(red, HIGH);
      delay(60000);
    }
    else
    { tempPass = "";
       i=0;
      goto A;
      }




  }
}
