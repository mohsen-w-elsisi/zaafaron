#include <Servo.h>
#include <Sonar.cpp>

#define BLOCKED_PATH_DISTANCE 0.30 // metres
#define MOTOR_REST_ANGLE 90

#define PATH_SCAN_DURATION 1000
#define PATH_SCAN_DEG_COUNT (PATH_SCAN_DURATION / SONAR_MEASURMENT_REST)
#define PATH_SCAN_DEG_INCREMENTS (180 / PATH_SCAN_DEG_COUNT)

class PathScanner
{
    Servo motor;
    Sonar sonar;

public:
    PathScanner(Servo motor, Sonar sonar) : motor(motor), sonar(sonar) {}

    int findBestUnblockedPath()
    {
        int bestDistance = 0;
        int bestDegree = 0;

        motor.write(0);
        for (int i = 0; i < PATH_SCAN_DEG_COUNT; i++)
        {
            int degree = PATH_SCAN_DEG_INCREMENTS * i;
            motor.write(degree);
            while (!sonar.ready())
                ;
            int distance = sonar.measure();
            if (distance > bestDistance)
            {
                bestDistance = distance;
                bestDegree = degree;
            }
            else if (distance == bestDistance)
            {
                if (abs(degree - 90) < abs(bestDegree - 90))
                    bestDegree = degree;
            }
        }

        return bestDegree;
    }

    bool pathIsBlocked()
    {
        awaitReady();
        return sonar.measure() <= BLOCKED_PATH_DISTANCE;
    }

    bool isReady()
    {
        return sonar.ready() && motor.read() == MOTOR_REST_ANGLE;
    }

    void awaitReady()
    {
        motor.write(MOTOR_REST_ANGLE);
        while (!sonar.ready())
            ;
    }
};