
#include <Servo.h>
#include <Ultrasonic.h>
Servo myservo;
const int ledPin = 3;
Ultrasonic ultrasonic(12, 13,400000);
int distance;
int affordanceLED;

void setup() {
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
myservo.attach(11);

}

void loop() {
distance = ultrasonic.read();
//when someones hand is close enough i want it to start caring
if (distance == 0) {
  affordanceLED = 0;
  myservo.write (90); // 90 is important for MECHANISM (harry!)
  // dont turn on if hand is far!
 }else if (distance <= 15)  {
    affordanceLED = (255 +  (distance * -17) );
    myservo.write(180);
    // if hand is near turn on (numbers were my attempt at dimming but u cant rlly tell with regular LED)
    }
   digitalWrite(ledPin, affordanceLED);
    Serial.println(affordanceLED);

}
