// Analog-Weather-Station.cpp
// Patrick Dobbie, Feb. 24, 2016
//
// This program controls a weather station using
// a Particle Photon embedded system and stepper
// motors to control dials and display weather.
/////////////////////////////////////////////////
#include "application.h"
#include "OpenWeatherMap.h"
#include "ParticleFunctions.h"
#include "Stepper.h"
#include "ToSteps.h"
#include <string>
#include <vector>
using namespace std;

const uint8_t updateInterval = 15; // minutes between updates
const uint8_t stepMode = 2;  // Use half-step
const uint8_t delayMS = 50; // Min delay is ____ ms
const vector<uint8_t> pinCoils = {D7,D6,D5,D4}; // Share pins with all dials
const vector<uint8_t> pinPower = {A5,A4,A3,A2}; // Set to -1 if always powered
const uint8_t pinReset = A0;
const uint8_t pinAlert = D7; //A1;

const float battCritLevel = 15; // % to show low battery alert
const uint8_t maxSteps  = 64;  // 180* rotation with half-step
const int minTemp   = -40; // *C
const int maxTemp   = 40;
const int minHumid  = 0;   // %
const int maxHumid  = 100;
const int minWSpeed = 0;   // km/h
const int maxWSpeed = 50;
const vector<string> rangeWDir = {"N","NNE","NE","ENE","E","ESE", "SE", "SSE","S","SSW","SW","WSW","W","WNW","NW","NNW"};

string strWeather = "";
unsigned long millisNow = 0UL;
unsigned long millisLastCheck = 0UL;
unsigned long millisLastGet = 0UL;

int8_t stepsTemperature = 0;
int8_t stepsHumidity = 0;
int8_t stepsWindSpeed = 0;
int8_t stepsWindDirection = 0;

OpenWeatherMapClass weather;
Stepper dialTemperature(  stepMode,delayMS,pinCoils,pinPower[0],readEEPROM(0));
Stepper dialHumidity(     stepMode,delayMS,pinCoils,pinPower[1],readEEPROM(1));
Stepper dialWindSpeed(    stepMode,delayMS,pinCoils,pinPower[2],readEEPROM(2));
Stepper dialWindDirection(stepMode,delayMS,pinCoils,pinPower[3],readEEPROM(3));

void resetDevice() {
    particleWiFiOff();
    for (int i=0; i<50; ++i) {
        digitalWrite(pinAlert, HIGH);
        delay(100);
        digitalWrite(pinAlert, LOW);
        delay(100);
    }

    resetEEPROM(0,3);
    dialTemperature.resetStepper(maxSteps);
    dialHumidity.resetStepper(maxSteps);
    dialWindSpeed.resetStepper(maxSteps);
    dialWindDirection.resetStepper(maxSteps);
    particleDeepSleep(1);
}

void setup() {
    pinMode(pinCoils[0], OUTPUT);
    pinMode(pinCoils[1], OUTPUT);
    pinMode(pinCoils[2], OUTPUT);
    pinMode(pinCoils[3], OUTPUT);
    pinMode(pinPower[0], OUTPUT);
    pinMode(pinPower[1], OUTPUT);
    pinMode(pinPower[2], OUTPUT);
    pinMode(pinPower[3], OUTPUT);
    pinMode(pinReset, INPUT_PULLDOWN);
    pinMode(pinAlert, OUTPUT);

    if (!particleBatteryOk(battCritLevel)){
        particleAlert(pinAlert);
        particleDeepSleep(updateInterval,true);
    }

    if (digitalRead(pinReset))  {resetDevice();}
    if (readEEPROM(0)>maxSteps) {resetDevice();}

    particleSubscribeWeather();
    particleGetWeather();
}

void loop() {
    millisNow = millis();
    if ((millisNow - millisLastCheck)>10000UL) {
        millisLastCheck = millisNow;
        strWeather = particleCheckData("<current>","</current>");

        // Publish "Get weather" again after 20 seconds
        if ((strWeather.empty())&&((millisNow - millisLastGet)>20000UL)) {
            millisLastGet = millisNow;
            particleGetWeather();
        }
        // If 2 minutes pass without an update, go to sleep and try again
        if (millisNow>120000UL) {
            particleAlert(pinAlert);
            particleDeepSleep(updateInterval,true);
        }

        else {
            particleWiFiOff();
            weather.update(strWeather);

            stepsTemperature  = valueToSteps(weather.temperature.value,   minTemp,  maxTemp,  maxSteps);
            stepsHumidity     = valueToSteps(weather.humidity.value,      minHumid, maxHumid, maxSteps);
            stepsWindSpeed    = valueToSteps(weather.wind.speed.value,    minWSpeed,maxWSpeed,maxSteps);
            stepsWindDirection = codeToSteps(weather.wind.direction.code, rangeWDir,maxSteps);

            dialTemperature.rotateStepper(stepsTemperature);
            dialHumidity.rotateStepper(stepsHumidity);
            dialWindSpeed.rotateStepper(stepsWindSpeed);
            dialWindDirection.rotateStepper(stepsWindDirection);

            writeEEPROM(0,stepsTemperature);
            writeEEPROM(1,stepsHumidity);
            writeEEPROM(2,stepsWindSpeed);
            writeEEPROM(3,stepsWindDirection);

            particleDeepSleep(updateInterval,true);
        }
    }
}
/////////////////////////////////////////////////
//EOF
