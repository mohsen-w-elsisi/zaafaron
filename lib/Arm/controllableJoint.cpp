#include <Arduino.h>
#include <Servo.h>

class ControllableJoint
{
    Servo &motor;
    int potentiometerPin;

public:
    ControllableJoint(int potentiometerPin, Servo &motor) : motor(motor), potentiometerPin(potentiometerPin)
    {
    }

    void update()
    {
        int potReading = analogRead(potentiometerPin);
        int degree = pot_reading_to_deg(potReading);
        motor.write(degree);
    }

private:
    static inline int pot_reading_to_deg(int pot_reading)
    {
        return (pot_reading / 1024.0) * 180;
    }
};