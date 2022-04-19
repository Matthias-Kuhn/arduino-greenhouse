#include "MoistureSensor.h"
#include "WateringSystem.h"
#include "DHT.h"
#include "StatusDisplay.h"

#include <SoftwareSerial.h>

SoftwareSerial btSerial(10, 11); // RX, TX PIN

String bt_rx;


// PINS
#define waterEnginePin LED_BUILTIN // pin has to support pwm
#define moisturePin A0
#define dhtPin 22


WateringSystem waterEngine(waterEnginePin);
// values for mositure sensor vary. Test your sensor for the values.
 //MoistureSensor moistureSensor(420, 830, 40.0, moisturePin);
 //DHT dhtSensor(dhtPin, DHT22);
 //StatusDisplay statusDisplay;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  // setup of sensors
  waterEngine.setup(waterEnginePin);

  // initialize data
  waterEngine.stop();
  //waterEngine.setWateringDuration(3850);
  //waterEngine.setWateringBreakTime(30000);

  waterEngine.setWateringDuration(3000);
  waterEngine.setWateringBreakTime(86400000);

  waterEngine.setWateringRate(255);

  //dhtSensor.begin();
  //statusDisplay.setup();

  Serial.print("Initialized! Millis now at: ");
  Serial.println(millis());

}

void loop() {
  updateOnCycle();

  if(waterEngine.pump()){
    Serial.print("Watering started! Time: ");
    Serial.println(millis());
  }

  if (btSerial.available()) {
    bt_rx = btSerial.readString();
    Serial.print("Received:");
    Serial.println(bt_rx);
    if (bt_rx == "how_long") {
      btSerial.print("Start watering in ");
      btSerial.print(waterEngine.getTime(waterEngine.remainingTime(millis())));
      btSerial.println(waterEngine.timeEnding);
    }
    if (bt_rx == "water_now") {
      btSerial.println("Ok. Watering started!");
      waterEngine.forceBreakOver();
      waterEngine.pump();
    }
  }

}

/*
 * In order to get the current time and status, many of the included classes
 * expect a call of the function updateOnCycle() in each loop
 */
void updateOnCycle() {
  //Serial.println(millis());
  waterEngine.updateOnLoop(millis());
  //statusDisplay.updateOnLoop(millis(), waterEngine.remainingTime(millis()),dhtSensor.readTemperature(), dhtSensor.readHumidity(), moistureSensor.getMoisturePercentage(), waterEngine.isCurrentlyWatering());
}


void printEvery10Seconds(){
  // TODO: Dont work with exact milli values
  if (millis() % 100000 == 0) {
    //Serial.print("Soil moisture: ");
    //Serial.print(moistureSensor.getMoistureValue());
    //Serial.print(" (");
    //Serial.print(moistureSensor.getMoisturePercentage());
    //Serial.println("%)");
    //Serial.print("Temperature: ");
    //Serial.println(dhtSensor.readTemperature());
    //Serial.print("Humidity: ");
    //Serial.println(dhtSensor.readHumidity());
    //Serial.println("");
    Serial.print("Time until next watering: ");
    Serial.println(waterEngine.remainingTime(millis()));

  }
}
