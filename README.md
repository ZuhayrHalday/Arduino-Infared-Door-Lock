# Arduino IR Remote Door Lock

This project is an Arduino-based door lock system that uses an IR remote to control a servo motor, which locks and unlocks a door. The system also includes an LCD screen to display 'Welcome' and 'Goodbye' messages, along with the lock status ('Locked'/'Unlocked').

## Features

- **IR Remote Control**: Lock and unlock the door using an IR remote.
- **Visual Feedback**: LCD screen displays lock status and messages.
- **Audible Feedback**: Buzzer sounds on lock/unlock actions.
- **LED Indicators**: Red and green LEDs indicate the lock status.

## Requirements

- Arduino board
- IR remote and receiver
- Servo motor
- LCD screen (16x2)
- Buzzer
- Red and green LEDs
- Miscellaneous electronic components (resistors, wires, etc.)

## Getting Started

### Hardware Setup

1. **Connect the Servo Motor**:
   - Connect the servo signal wire to pin 8.
   - Connect the power and ground wires to the Arduino's 5V and GND pins.

2. **Connect the IR Receiver**:
   - Connect the IR receiver signal pin to pin 6.
   - Connect the power and ground pins to the Arduino's 5V and GND pins.

3. **Connect the LCD Screen**:
   - Connect the LCD pins to the Arduino as follows:
     - `rs` to pin 13
     - `en` to pin 12
     - `d4` to pin 5
     - `d5` to pin 4
     - `d6` to pin 3
     - `d7` to pin 2

4. **Connect the Buzzer and LEDs**:
   - Connect the buzzer to pin 9.
   - Connect the red LED to pin 11.
   - Connect the green LED to pin 10.

### Software Setup

1. **Install Arduino IDE**: Make sure you have the Arduino IDE installed on your computer.
2. **Install Required Libraries**: Install the following libraries from the Arduino Library Manager:
   - `Servo`
   - `IRremote`
   - `LiquidCrystal`

### Code

```cpp
#include <Servo.h>
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
  irrecv.enableIRIn();
  myservo.attach(servoPin);
  myservo.write(servoPos);
  isClosed = false;
 
  if (isClosed == false) {
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
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFFFFFFF) {
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

    if (isClosed == false) {
      if (msgTyped == false) {
        lcd.begin(16, 2);   
        lcd.print("   DOOR OPEN");
        lcd.setCursor(0, 1);
        lcd.print(" Welcome Zuhayr");
        msgTyped = true;
      }
    }

    if (isClosed == true) {
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
```

## Usage

1. **Upload Code**: Upload the provided code to your Arduino board.
2. **Power Up**: Connect the Arduino to a power source.
3. **Use the Remote**: Use the IR remote to lock and unlock the door:
   - Press the "lock" button (code `0xFF22DD`) to lock the door.
   - Press the "unlock" button (code `0xFFC23D`) to unlock the door.

## License

This project is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for details.
