#include <Arduino.h>
#include <Servo.h>
#include <Sonar.cpp>

#define GRAB_DISTANCE 0.1 // metres

class Wrist
{
    int releaseButtonPin;
    Servo &motor;
    Sonar &sonar;

public:
    Wrist(int releaseButtonPin, Servo &motor, Sonar &sonar) : releaseButtonPin(releaseButtonPin), motor(motor), sonar(sonar)
    {
    }

    void update()
    {
        if (!sonar.ready())
            return;

        if (releaseButtonClicked() || !objectWithinGrabDistance())
        {
            motor.write(0);
        }
        else
        {
            motor.write(180);
        }
    }

private:
    inline bool releaseButtonClicked()
    {
        return digitalRead(releaseButtonPin) == HIGH;
    }

    inline bool objectWithinGrabDistance()
    {
        return sonar.measure() <= GRAB_DISTANCE;
    }
};
