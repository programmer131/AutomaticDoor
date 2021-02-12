#include <LiquidCrystal_I2C.h>

#include <Servo.h>

#include <Wire.h>

#include <Adafruit_MLX90614.h>

Adafruit_MLX90614
mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo myservo1;
Servo myservo2;

#define red 13
#define haha 4
#define pin 9
int pos1, pos2;

void setup() {
   Serial.begin(9600);
   pinMode(red, OUTPUT);
   pinMode(haha, INPUT);
   myservo1.attach(7);
   myservo2.attach(8);
   myservo1.write(90);
   myservo2.write(90);
   mlx.begin();

   lcd.init();
   lcd.backlight();
   lcd.setBacklight(255);
   lcd.setCursor(0, 0);
   //lcd.print("ObjectTemp:");
   lcd.setBacklight(255);
   pinMode(pin, INPUT); // set pin to input
   digitalWrite(pin, HIGH); // turn on pullup resistors

}

void loop() {

   int montion = digitalRead(haha);
   if (montion == 1) {
      Serial.print("made");
      Serial.print("\n");
      lcd.setCursor(0, 0);
      lcd.print("ObjectTemp:");
      //lcd.setCursor(13,3);
      //delay(2000);
      kaiguan();
   }

}

void kaiguan() {

   int temp_obj = mlx.readObjectTempC();
   Serial.print(temp_obj);
   Serial.print("\n");

   if (temp_obj <= 25 && !digitalRead(pin)) {
      lcd.setCursor(0, 1);
      lcd.print(temp_obj);
      lcd.setCursor(0, 2);
      lcd.print("Not detected,retest!");
   }
   if (temp_obj > 25 && temp_obj <= 37 && !digitalRead(pin)) {
      lcd.setCursor(0, 1);
      lcd.print(temp_obj);
      lcd.setCursor(0, 2);
      lcd.print("body temperature ok ");
      for (int pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
         // in steps of 1 degree
         myservo1.write(pos); // tell servo to go to position in variable 'pos'
         myservo2.write(180 - pos);
         delay(15); // waits 15ms for the servo to reach the position
      }
      delay(5000);
      for (int pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
         myservo1.write(pos); // tell servo to go to position in variable 'pos'
         myservo2.write(180 - pos);
         delay(15); // waits 15ms for the servo to reach the position
      }

   }

   if (temp_obj <= 30 && digitalRead(pin)) {
      lcd.setCursor(0, 1);
      lcd.print(temp_obj);
      lcd.setCursor(0, 2);
      lcd.print("Not detected,retest!");
   }
   if (temp_obj > 30 && temp_obj <= 37 && digitalRead(pin)) {
      lcd.setCursor(0, 1);
      lcd.print(temp_obj);
      lcd.setCursor(0, 2);
      lcd.print("body temperature ok ");
      for (int pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
         // in steps of 1 degree
         myservo1.write(pos); // tell servo to go to position in variable 'pos'
         myservo2.write(180 - pos);
         delay(15); // waits 15ms for the servo to reach the position
      }
      delay(5000);
      for (int pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
         myservo1.write(pos); // tell servo to go to position in variable 'pos'
         myservo2.write(180 - pos);
         delay(15); // waits 15ms for the servo to reach the position
      }

   }
   if (temp_obj > 37) {
      digitalWrite(red, HIGH);
      lcd.setCursor(0, 1);
      lcd.print(temp_obj);
      lcd.setCursor(0, 2);
      lcd.print(" --Keep out!--      ");
      delay(500);
   }
   digitalWrite(red, LOW);
}
