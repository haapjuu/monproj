#include <Keypad.h>
   #include <Servo.h>

   Servo servo_Motor;
   char* password = "7856";
   int position = 0;
   const byte ROWS = 4;
   const byte COLS = 4;
   char keys[ROWS][COLS] = {
   {'1','2','3','A'},
   {'4','5','6','B'},
   {'7','8','9','C'},
   {'*','0','#','D'}
   };

   byte rowPins[ROWS] = { 8, 7, 6, 9 };
   byte colPins[COLS] = { 5, 4, 3, 2 };
   Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

   void setup(){
     servo_Motor.attach(11);
     setLocked(true);
   }
   void loop(){
     char key = keypad.getKey();
     if (key == '*') {
         position = 0;
         setLocked(true);
   }
   if (key == password[position]){
         position ++;
   }
   if (position == 4){
         setLocked(false);
   }
   delay(100);
   }
   void setLocked(int locked){
   if (locked){
       servo_Motor.write(0);
   }
   else{
       servo_Motor.write(90);
   }
   }
