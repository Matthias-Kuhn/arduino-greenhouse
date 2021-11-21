#ifndef MoistureSensor_h
#define MoistureSensor_h

#include "Arduino.h"


/*
 * The class MoistureSensor simplifies the usage of a capacitve soil moisture sensor.
 * It provides functions for calculating the moisture percentage and detection if the
 * moisture is under a distinct threshold.
 */
class MoistureSensor{
    public:
        // typical measurements with our sensor were 420 for water, 830 for air
        MoistureSensor(int water, int air, float set, int pin);
        MoistureSensor(int pin);
        float getMoisturePercentage();
        float getMoistureValue();
        bool needsWater();
        void setWaterReading(int newReading);
        int getWaterReading();
        void setAirReading(int newReading);
        int getAirReading();
        void setSetPoint(float newPoint);
        float getSetPoint();

    private:
        int SENSOR_PIN;
        int waterReading; // maximum moisture
        int airReading; // minimum moisture
        float setPoint; // moisture, where you want to water the plants
};

#endif