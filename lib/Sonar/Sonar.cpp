#pragma once
#include <Arduino.h>

#define SPEED_SOUND_M_PER_US 0.000343
#define TRIG_PULSE_DURATION 10UL
#define ECHO_PULSE_TIMEOUT 30000UL
#define SONAR_MEASURMENT_REST 100

class Sonar
{
    int trigPin;
    int echoPin;

    unsigned long long lastMeasurement = 0;

public:
    Sonar(int trigPin, int echoPin)
        : trigPin(trigPin), echoPin(echoPin)
    {
    }

    double measure()
    {
        if (!ready())
            return 0;

        sendTrig();

        unsigned long roundTripTime =
            pulseIn(echoPin, HIGH, ECHO_PULSE_TIMEOUT);
        if (roundTripTime == 0)
            return 0;

        lastMeasurement = millis();

        return calcDistance(roundTripTime);
    }

    bool ready()
    {
        return (millis() - lastMeasurement) > SONAR_MEASURMENT_REST;
    }

private:
    void sendTrig()
    {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(TRIG_PULSE_DURATION);
        digitalWrite(trigPin, LOW);
    }

    double calcDistance(unsigned long roundTripTime)
    {
        return (roundTripTime * SPEED_SOUND_M_PER_US) / 2;
    }
};