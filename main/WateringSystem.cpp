#include "WateringSystem.h"

/*  
 * The wateringSystem controlles the watering pump for the plants.
 * It handles the watering rate and duration and has built-in safety
 * for stopping the watering in various cases.
 ****************************************************************************
 *   !!! updateOnLoop() has to be called in every loop in the main file  !!!
 ***************************************************************************
 */


WateringSystem::WateringSystem(int pwmPin){
    MOTOR_PIN = pwmPin;
    pinMode(MOTOR_PIN, OUTPUT);
    stop(); 
}

void WateringSystem::setup(int pwmPin){
    MOTOR_PIN = pwmPin;
    pinMode(MOTOR_PIN, OUTPUT);
    stop();
}

// has to be called in every loop in main file
// stops the watering after duration is reached and checks if break time is over
void WateringSystem::updateOnLoop(unsigned long currentTime){
    onUpdateLoopIsCalled = true;
    if (pumpDurationReached(currentTime))
        stop();
    if (!breakIsOver)
        breakIsOver = breakTimeExpired(currentTime);
}

// starts watering and stops automatically after wateringDuration is reached
// returns true if pump starts watering
bool WateringSystem::pump(){
    if (breakIsOver && onUpdateLoopIsCalled && !isWatering){
        pumpAtRate(wateringRate);
        wateringStartTime = millis();
        breakIsOver = false;
        isWatering = true;
        return true;
    }
    return false;
}
void WateringSystem::pumpAtRate(int pwmRate){
    analogWrite(MOTOR_PIN, pwmRate);
//    digitalWrite(MOTOR_PIN, HIGH);
}
// stops the watering
void WateringSystem::stop(){
    digitalWrite(MOTOR_PIN, LOW);
    isWatering = false;
}
// reset the break timer manually
void WateringSystem::breakReset(){
    stop();
    breakIsOver = false;
    wateringStartTime = millis();
}
bool WateringSystem::pumpDurationReached(unsigned long current_time){
    return  (current_time-wateringStartTime) >= wateringDuration;
}
bool WateringSystem::breakTimeExpired(unsigned long current_time){
    return (current_time-wateringStartTime) >= wateringBreakTime;
}

unsigned long WateringSystem::remainingTime(unsigned long current_time){
    if(breakTimeExpired(current_time)|| isWatering){
        return 0;
    } else {
        return wateringBreakTime - (current_time - wateringStartTime);
    }
}


// getter and setter

bool WateringSystem::isCurrentlyWatering(){
    return isWatering;
}
void WateringSystem::setWateringRate(int pwmRate){
    wateringRate = pwmRate;
}
void WateringSystem::setWateringDuration(unsigned long durationInMillis){
    wateringDuration = durationInMillis;
}
void WateringSystem::setWateringBreakTime(unsigned long breakTimeInMillis){
    wateringBreakTime = breakTimeInMillis;
}
    
