#include "MoistureSensor.h"
#include "WateringSystem.h"

// PINS
#define waterEnginePin LED_BUILTIN // pin has to support pwm
#define moisturePin A0


WateringSystem waterEngine(waterEnginePin);
// values for mositure sensor vary. Test your sensor for the values.
MoistureSensor moistureSensor(420, 830, 40.0, moisturePin);


void setup() {
  Serial.begin(9600);

  // setup of sensors
  waterEngine.setup(waterEnginePin);

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
    Serial.print("Watering started! Time: ");
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


void printEvery10Seconds(){
  // TODO: Dont work with exact milli values
  if (millis() % 100000 == 0) {
    Serial.print("Soil moisture: ");
    Serial.println(moistureSensor.getMoistureValue());
  }
}
