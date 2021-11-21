#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int water, int air, float set, int pin){
    waterReading = water;
    airReading = air;
    setPoint = set;
    SENSOR_PIN = pin;
}

MoistureSensor::MoistureSensor(int pin){
    MoistureSensor(300, 900, 50.0, pin);
}

float MoistureSensor::getMoistureValue(){
    return analogRead(SENSOR_PIN);
}

float MoistureSensor::getMoisturePercentage(){
    int reading = analogRead(SENSOR_PIN);
    if (reading < waterReading) return 100.0;
    else if (reading > airReading) return 0.0;
    else return (-100.0/(airReading - waterReading))*(reading - airReading);
}
bool MoistureSensor::needsWater(){
    return getMoisturePercentage() < setPoint;
}
void MoistureSensor::setWaterReading(int newReading){
    waterReading = newReading;
}
int MoistureSensor::getWaterReading(){
    return waterReading;
}

void MoistureSensor::setAirReading(int newReading){
    airReading = newReading;
}
int MoistureSensor::getAirReading(){
    return airReading;
}
void MoistureSensor::setSetPoint(float newPoint){
    setPoint = newPoint;
}
float MoistureSensor::getSetPoint(){
    return setPoint;
}
