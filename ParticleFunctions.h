// PatricleFunctions.h
// Patrick Dobbie, Feb. 25, 2016
//
// A collection of functions which communicate
// with the Particle server or the Photon.
/////////////////////////////////////////////////
#ifndef ParticleFunctions_H
#define ParticleFunctions_H

#include "application.h"
#include "PowerShield.h"
#include <string>

std::string dataStr=""; // Bad practice, but Particle.subscribe function causes limitations (must return void)

// Publish event and wait for webhook
void particleGetWeather() {
    Particle.publish("edmonton_weather","",60,PRIVATE);
}
// Get weather from server. Data comes in 512 byte chunks, so this function may be called twice
void particleGotWeather(const char *name, const char *data) {
    std::string str (data);
    dataStr += str; // Store data in a global string so it can be passed around
}
// Subscribe to the "edmonton_weather" event
void particleSubscribeWeather() {
    Particle.subscribe("hook-response/edmonton_weather", particleGotWeather, MY_DEVICES);
}
// Check to see if data has arrived correctly, and pass it along if it has
std::string particleCheckData(std::string startStr="", std::string endStr="") {
    if (dataStr.empty()) {return "";}

    int p0 = dataStr.find(startStr);
    int p1 = dataStr.find(endStr);

    if ((p0 == std::string::npos)||(p0 != 0)) {return "";}
    if (p1 == std::string::npos) {return "";}
    return dataStr;
}

// EEPROM functions
int readEEPROM(uint8_t addr) {
    return EEPROM.read(addr);
}
void writeEEPROM(uint8_t addr, uint8_t value) {
    EEPROM.update(addr, value);
}
void resetEEPROM(uint8_t minAddr, uint8_t maxAddr) {
    for (int i=minAddr; i<=maxAddr; ++i) {
        EEPROM.update(i, 0);
    }
}

// Battery functions
bool particleBatteryOk(float battCritLevel) {
    PowerShield battery;
    battery.begin();
    battery.quickStart();
    delay(500);
    if (battery.getSoC()<battCritLevel) {
        return false;
    }
    return true;
}
void particleAlert(uint8_t pinAlert) {
    for (int i=0; i<3; ++i) {
        digitalWrite(pinAlert, HIGH);
        delay(800);
        digitalWrite(pinAlert, LOW);
        delay(800);
    }
}

// Power saving modes
void particleWiFiOff() {
    WiFi.off();
}
void particleDeepSleep(uint8_t updateInterval, bool syncTime=false) {
    int updateTime = updateInterval*60+1;

    if (syncTime){
        if ((Time.minute()%updateInterval)>0) {
            updateTime -= (Time.minute()%updateInterval)*60;
        }
        updateTime -= Time.second();
    }

    System.sleep(SLEEP_MODE_DEEP, updateTime);
}

#endif
/////////////////////////////////////////////////
//EOF
