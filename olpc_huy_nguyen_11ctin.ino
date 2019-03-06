#include <Servo.h>
#define enA 9 // Left
#define enB 10 // Right
#define in1 4
#define in2 5
#define in3 6
#define in4 7
int xAxis, yAxis, x = 0, y = 0, motorSpeedA = 0,  motorSpeedB = 0;
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void loop() {
  xAxis = yAxis = 510; 
  while (Serial.available() == 0) {}
  x = Serial.read(); delay(10);
  y = Serial.read(); delay(10);
  xAxis = x * 4; yAxis = y * 4;
  if (yAxis < 470) { // Move Backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550) { // Move Forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  else { // Stop
    motorSpeedA = 0;
    motorSpeedB = 0;
  }
  if (xAxis < 470) { // Left Control
    int xMapped = map(xAxis, 470, 0, 0, 255);
    motorSpeedA -= xMapped;
    motorSpeedB += xMapped;
    motorSpeedA = max(motorSpeedA, 0);
    motorSpeedB = min(motorSpeedB, 255);
  }
  if (xAxis > 550) { // Right Control
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    motorSpeedA += xMapped;
    motorSpeedB -= xMapped;
    motorSpeedA = min(motorSpeedA, 255);
    motorSpeedB = max(motorSpeedB, 0);
  }
  // Buzz Fix
  //if (motorSpeedA < 70) motorSpeedA = 0;
  //if (motorSpeedB < 70) motorSpeedB = 0;
  // Maneuver
  analogWrite(enA, motorSpeedA); 
  analogWrite(enB, motorSpeedB); 
}
