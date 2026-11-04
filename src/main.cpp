#include <Arduino.h>
#include <Sonar.cpp>
#include <Mobility.cpp>

#define IN1 2
#define IN2 3

#define IN3 4
#define IN4 5

#define TRIG_PIN 6
#define ECHO_PIN 7

Wheels wheels(IN1, IN2, IN3, IN4);
Sonar sonar(TRIG_PIN, ECHO_PIN);

void setup()
{
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void avoidBarrier()
{
  wheels.brake();

  wheels.forward();
}

void loop()
{
  if (!sonar.ready())
    return;
  if (sonar.measure() <= 0.15)
    avoidBarrier();
}
