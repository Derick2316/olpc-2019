#include <Servo.h>
#include <PS2X_lib.h>
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define enA 8 // Left
#define enB 9 // Right
#define dat 10 // Data
#define cmd 11 // Command
#define atn 12 // Attention
#define clk 13 // Clock

PS2X ps2x;
int xAxis, yAxis, x = 0, y = 0, motorSpeedA = 0,  motorSpeedB = 0;

void setup() {
  ps2x.config_gamepad(clk, cmd, atn, dat, 0, 0);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  xAxis = yAxis = 130; 
  ps2x.read_gamepad();
  xAxis = ps2x.Analog(PSS_RX); delay(10);
  yAxis = ps2x.Analog(PSS_RY); delay(10);
  if (yAxis < 120) { // Move Backward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); // Left Motor Back 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); // Right Motor Back
    motorSpeedA = map(yAxis, 120, 0, 0, 255);
    motorSpeedB = map(yAxis, 120, 0, 0, 255);
  }
  else if (yAxis > 140) { // Move Forward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); // Left Motor Forward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); // Right Motor Forward
    motorSpeedA = map(yAxis, 140, 255, 0, 255);
    motorSpeedB = map(yAxis, 140, 255, 0, 255);
  }
  else { // Stop
    motorSpeedA = 0;
    motorSpeedB = 0;
  }
  if (xAxis < 120) { // Left Control
    int xMapped = map(xAxis, 120, 0, 0, 255);
    motorSpeedA -= xMapped;
    motorSpeedB += xMapped;
    motorSpeedA = max(motorSpeedA, 0);
    motorSpeedB = min(motorSpeedB, 255);
  }
  if (xAxis > 140) { // Right Control
    int xMapped = map(xAxis, 140, 255, 0, 255);
    motorSpeedA += xMapped;
    motorSpeedB -= xMapped;
    motorSpeedA = min(motorSpeedA, 255);
    motorSpeedB = max(motorSpeedB, 0);
  }
  if (motorSpeedA < 70) motorSpeedA = 0;
  if (motorSpeedB < 70) motorSpeedB = 0; // Buzz Fix
  analogWrite(enA, motorSpeedA); 
  analogWrite(enB, motorSpeedB); // Maneuver 
}
