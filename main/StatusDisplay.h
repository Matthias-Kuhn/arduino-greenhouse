#ifndef StatusDisplay_h
#define StatusDisplay_h

#include "Arduino.h"
// required for "const char" and "PROGMEM"
#include <avr/pgmspace.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class StatusDisplay {
public:
  StatusDisplay();
  void setup();
  void updateOnLoop(
    unsigned long currentTime, unsigned long remainingBreak,
    float temperature, float humidity, float moisture,
    bool isWatering);

private:
  void showDHTScreen(float t, float h);
  void showMoistureScreen(unsigned long time, float moisture);
  void updateSeconds(unsigned long time);
  void showWateringScreen();
  unsigned long getTime(unsigned long time);

  const char* timeEnding = "";
  bool onUpdateLoopIsCalled = false;
  int lastTime = 0;
  bool updateTime = true;

  Adafruit_SSD1306* display;
  int activeDisplay;
};

#endif