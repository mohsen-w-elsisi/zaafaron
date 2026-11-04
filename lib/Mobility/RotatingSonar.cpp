#include <Arduino.h>
#include <Servo.h>
#include <Sonar.cpp>

#define PATH_ANGLE 60
#define ROTATION_STAGGER_INTERVAL 10

class RotatingSonar
{
    Sonar sonar;
    Servo motor;

public:
    RotatingSonar(Sonar sonar, Servo motor)
        : sonar(sonar), motor(motor)
    {
    }

    int findEmptyPathAngle()
    {
        int path1NextObject, path2NextObject;
        rotate(-PATH_ANGLE);
        delay(500);
        return 0; // ay 7ga
    }

private:
    int getObjectDistanceAtAngle(int angle)
    {
        rotate(PATH_ANGLE);
        delay(500);
    }

    void rotate(int degrees)
    {
        if (degrees > 200)
        {
            return;
        }
        motor.write(degrees);
    }
};