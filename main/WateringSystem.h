#ifndef WateringSystem_h
#define WateringSystem_h

#include "Arduino.h"
// required for "const char" and "PROGMEM"
#include <avr/pgmspace.h>

/*
 * The wateringSystem controlles the watering pump for the plants.
 * It handles the watering rate and duration and has built-in safety
 * for stopping the watering in various cases. 
 */
class WateringSystem{
    public:
        WateringSystem(int pwmPin);
        void setup(int pwmPin);
        void updateOnLoop(unsigned long currentTime);
        bool pump();
        void pumpAtRate(int pwmRate);
        void stop();
        void breakReset();
        
        unsigned long getTime(unsigned long time);
        const char* timeEnding = "";

        void forceBreakOver();
        bool pumpDurationReached(unsigned long current_time);
        bool breakTimeExpired(unsigned long current_time);
        bool isCurrentlyWatering();
        void setWateringRate(int pwmRate);
        void setWateringDuration(unsigned long durationInMillis);
        void setWateringBreakTime(unsigned long breakTimeInMillis);

        unsigned long remainingTime(unsigned long current_time);
        

    private:
        int MOTOR_PIN; // pin has to support PWM
        int wateringRate = 255; // PWM rate has to be between 0 and 255
        unsigned long wateringDuration = 6000; // duration of one watering in millis (6sec)
        unsigned long wateringBreakTime = 25200000; // break between waterings (7h * 3.600.000)
        unsigned long wateringStartTime = 0;
        bool isWatering = false;
        bool breakIsOver = false;
        bool onUpdateLoopIsCalled = false; // if not called, pump will not stop watering!


};

#endif