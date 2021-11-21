#include "MoistureSensor.h"
#include "WateringSystem.h"


WateringSystem waterEngine (LED_BUILTIN);


void setup() {
  Serial.begin(9600);

  // setup of sensors
  waterEngine.setup(LED_BUILTIN);

  // initialize data
  waterEngine.stop();
  waterEngine.setWateringDuration(3850);
  waterEngine.setWateringBreakTime(30000);
  waterEngine.setWateringRate(255);

  Serial.print("Initialized! Millis now at: ");
  Serial.println(millis());

}

void loop() {
  updateOnCycle();

  if(waterEngine.pump()){
    Serial.print("now pumping! Time: ");
    Serial.println(millis());
  } 

}

/*
 * In order to get the current time and status, many of the included classes
 * expect a call of the function updateOnCycle() in each loop
 */
void updateOnCycle() {
  //Serial.println(millis());
  waterEngine.updateOnLoop(millis());
}
