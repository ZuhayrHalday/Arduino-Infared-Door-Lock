or  #include <Servo.h>

#include <IRremote.hpp>

#include <LiquidCrystal.h>

const int RECV_PIN = 6;

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long lastCode;


Servo myservo;
int servoPos = 0;
int servoPin = 8;
boolean isClosed = false;
boolean msgTyped = false;

int buzzer = 9;
int i;
int redLED = 11;
int greenLED = 10;

const int rs = 13, en = 12, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();

  myservo.attach(servoPin);
  myservo.write(servoPos);
  isClosed = false;
 
  if (isClosed == false){
  lcd.begin(16, 2);   
  lcd.print("   DOOR OPEN");
  lcd.setCursor(0, 1);
  lcd.print(" Welcome Zuhayr");
  msgTyped = true;
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
      
      if (results.value == 0xFFFFFFFF){
         results.value = lastCode;
      }

      if (results.value == 0xFF22DD) {
        if (isClosed == false) {
        lastCode = results.value;
        servoPos = 90;
        for (int i=0; i<1000; i++) {
          digitalWrite(buzzer,HIGH);
          delayMicroseconds(100);
          digitalWrite(buzzer,LOW);
          delayMicroseconds(100);
        }
        delay(50);
        for (int i=0; i<1000; i++) {
          digitalWrite(buzzer,HIGH);
          delayMicroseconds(100);
          digitalWrite(buzzer,LOW);
          delayMicroseconds(100);
        }
        delay(250);       
        myservo.write(servoPos);
        isClosed = true;
        msgTyped = false;

        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
        }
      }

      if (results.value == 0xFFC23D) {
       if (isClosed == true) {
       lastCode = results.value;
       servoPos = 0;
       for (int i=0; i<1000; i++) {
          digitalWrite(buzzer,HIGH);
          delayMicroseconds(150);
          digitalWrite(buzzer,LOW);
          delayMicroseconds(150);
        }
        delay(10);
        for (int i=0; i<1000; i++) {
          digitalWrite(buzzer,HIGH);
          delayMicroseconds(150);
          digitalWrite(buzzer,LOW);
          delayMicroseconds(150);
        }
        delay(10);
        for (int i=0; i<1000; i++) {
          digitalWrite(buzzer,HIGH);
          delayMicroseconds(100);
          digitalWrite(buzzer,LOW);
          delayMicroseconds(100);
        }
        delay(250);
       myservo.write(servoPos);
       isClosed = false;
       msgTyped = false;
       digitalWrite(greenLED, HIGH);
       digitalWrite(redLED, LOW); 
       }
      }

      //if (results.value == 0xFFA25D) {
       //if (isClosed == true) {
       //lastCode = results.value;
       //servoPos = 90;
       //myservo.write(servoPos);
       //isClosed = false;
       //msgTyped = false; 
       //}
       //else if (isClosed == false) {
       //lastCode = results.value;
       //servoPos = 180;
       //myservo.write(servoPos);
       //isClosed = true;
       //msgTyped = false; 
       //} 
      //}

      if (isClosed == false){
        if (msgTyped == false) {
        lcd.begin(16, 2);   
        lcd.print("   DOOR OPEN");
        lcd.setCursor(0, 1);
        lcd.print(" Welcome Zuhayr");
        msgTyped = true;
        }
       }

       if (isClosed == true){
        if (msgTyped == false) {
        lcd.begin(16, 2);   
        lcd.print("  DOOR LOCKED");
        msgTyped = true;
        }
       }

    delay(500);
    irrecv.resume(); 
  }
}
