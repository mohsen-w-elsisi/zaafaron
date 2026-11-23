#include <Arduino.h>

class Wheels
{
    int in1, in2, in3, in4;

public:
    Wheels(int in1, int in2, int in3, int in4) : in1(in1), in2(in2), in3(in3), in4(in4)
    {
    }

    void forward()
    {
        updateMotor1(HIGH, LOW);
        updateMotor2(HIGH, LOW);
    }

    void reverse()
    {
        updateMotor1(LOW, HIGH);
        updateMotor2(LOW, HIGH);
    }

    void right()
    {
        updateMotor1(HIGH, LOW);
        updateMotor2(LOW, HIGH);
    }

    void left()
    {
        updateMotor1(LOW, HIGH);
        updateMotor2(HIGH, LOW);
    }

    void stop()
    {
        updateMotor1(LOW, LOW);
        updateMotor2(LOW, LOW);
    }

private:
    void updateMotor1(int in1out, int in2out)
    {
        digitalWrite(in1, in1out);
        digitalWrite(in2, in2out);
    }

    void updateMotor2(int in3out, int in4out)
    {
        digitalWrite(in3, in3out);
        digitalWrite(in4, in4out);
    }
};
