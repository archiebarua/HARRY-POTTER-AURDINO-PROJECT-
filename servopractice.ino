#include <RGBColor.h>
#include <RGBLED.h>
#include <RGBMath.h>
#include <RGBReact.h>
#include <Transition.h>

#include <Servo.h>
#include <RGBLed.h>

Servo myservo;
Servo myservo2;
const int buttonPin = 2;
const int vibrationPin = 8;
const int redLED = 6;
const int greenLED = 3;
const int blueLED = 5;
bool isSaved = false;
int i = 0;


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
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redLED, redValue);
  analogWrite(greenLED, greenValue);
  analogWrite(blueLED, blueValue);
}

void gavel() {
  if (digitalRead(buttonPin) == HIGH) {
    myservo.write(0);
    
  } else {
    myservo.write(90);
  }
}

void wand() {
  if (digitalRead(buttonPin) == HIGH) {
    myservo.write(180);
    myservo2.write(0);

    
  } else {
    myservo.write(90);
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
    if (digitalRead(vibrationPin) == HIGH) {
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

void loop() {
  // put your main code here, to run repeatedly:
  gavel();
  /*
  if (digitalRead(buttonPin) == HIGH) {
    myservo.write(180);
  } else {
    myservo.write(0);
  }
  */
}
