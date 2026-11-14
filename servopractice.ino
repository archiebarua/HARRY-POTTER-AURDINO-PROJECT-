#include <RGBColor.h>
#include <RGBLED.h>
#include <RGBMath.h>
#include <RGBReact.h>
#include <Transition.h>

#include <Servo.h>
#include <RGBLed.h>

#include <Ultrasonic.h>

Servo myservo;
Servo myservo2;
int storyProgress = 0;
const int buttonPin = 2;
const int button2 = 4;
const int vibrationPin = 8;
const int redLED = 6;
const int greenLED = 3;
const int blueLED = 5;
bool isSaved = false;
int i = 0;


const int ledPin = 3;
Ultrasonic ultrasonic(12, 13,400000);
int distance;
int affordanceLED;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  myservo2.attach(11);
  pinMode(buttonPin, INPUT);
  myservo.write(90);
  myservo2.write(90);

  pinMode(vibrationPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);


  pinMode(ledPin, OUTPUT);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redLED, redValue);
  analogWrite(greenLED, greenValue);
  analogWrite(blueLED, blueValue);
}

void approach() {
  distance = ultrasonic.read();
  Serial.println(distance);
  //when someones hand is close enough i want it to start caring
  if (distance == 0) {
    affordanceLED = 0;
    myservo.write (90); // 90 is important for MECHANISM (harry!)
    // dont turn on if hand is far!
  } else if (distance <= 15)  {
      affordanceLED = (255 +  (distance * -17) );
      myservo.write(180);
      storyProgress += 50;
      // if hand is near turn on (numbers were my attempt at dimming but u cant rlly tell with regular LED)
  }
  digitalWrite(ledPin, affordanceLED);
  //Serial.println(affordanceLED);
}


void gavel() {
  if (digitalRead(buttonPin) == HIGH) {
    myservo.write(0);
    storyProgress += 1;
  } else {
    myservo.write(90);
  }
}

void wand() {
  if (digitalRead(button2) == HIGH) {
    myservo2.write(0);
    storyProgress += 1;
    
  } else {
    myservo2.write(90);
  }
}

void timeTurner() {

  while (isSaved == false) {
    i += 1;
    Serial.println(i);
    int redValue = i;
    int greenValue = 255 - i;

    setColor(i, 255 - i, 0);
    delay(10); // Adjust speed of the fade
    if (digitalRead(button2) == HIGH) {
      Serial.println("I'm SAVED!");
      setColor(0, 255, 0);
      i = 0;
      isSaved = true;
    }
    if (i == 255) {
      myservo.write(180);
      Serial.println("BLAM!");
      Serial.println("I'm DOOOMED!!");
      setColor(255, 0, 0);
      isSaved = true;
    }

  }
  
}

void pumpkinPatch() {

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(storyProgress);
  approach();
  if (storyProgress >= 200) {
    wand();
  }
  if (storyProgress >= 400) {
    gavel();
  }


}
