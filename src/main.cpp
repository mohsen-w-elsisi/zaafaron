#include <Arduino.h>
#include <Sonar.cpp>
#include <Mobility.cpp>
#include "pins.cpp"

Wheels wheels(IN1, IN2, IN3, IN4);
Sonar sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
Servo pathScannerMotor;
PathScanner pathScanner(pathScannerMotor, sonar);

void setup()
{
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(SONAR_TRIG_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);

  pathScannerMotor.attach(FRONT_SONAR_MOTOR);
}

void avoidObsticle()
{
  wheels.stop();

  Serial.println("Path is blocked");
  Serial.println("Starting Scan...");
  int bestAngle = pathScanner.findBestUnblockedPath();
  Serial.print("Found path at angle: ");
  Serial.println(bestAngle);

  if (bestAngle == 90)
  {
    Serial.println("path is no longer blockled");
  }
  else if (bestAngle > 90)
  {
    Serial.println("turingi right");
    wheels.right();
    delay(300);
  }
  else
  {
    Serial.println("turingi left");
    wheels.left();
    delay(300);
  }
}

void loop()
{

  if (pathScanner.pathIsBlocked())
  {
    avoidObsticle();
  }
  else
  {
    Serial.println("Path is clear");
    wheels.forward();
  }
}
