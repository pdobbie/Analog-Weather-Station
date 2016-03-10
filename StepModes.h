// StepModes.h
// Patrick Dobbie, Feb. 25, 2016
//
// Initiaize the different step modes possible
// for the motor.
/////////////////////////////////////////////////
#ifndef StepModes_H
#define StepModes_H

#include "application.h"

// Activate or deactivate the motor
void powerOn(uint8_t pinPower) {
    digitalWrite(pinPower, HIGH);
}
void powerOff(uint8_t pinPower) {
    digitalWrite(pinPower, LOW);
}
// Perform preferred stepping mode
void waveStepOne(uint8_t pCoil, uint8_t nCoil, uint8_t delayMS) {
    digitalWrite(pCoil, LOW);
    digitalWrite(nCoil, HIGH);
    delay(delayMS);
    digitalWrite(nCoil, LOW);
}
void fullStepOne(uint8_t pCoil, uint8_t nCoil, uint8_t delayMS) {
    digitalWrite(pCoil, HIGH);
    digitalWrite(nCoil, HIGH);
    delay(delayMS);
    digitalWrite(pCoil, LOW);
    digitalWrite(nCoil, LOW);
}
void halfStepOne(uint8_t pCoil, uint8_t nCoil, uint8_t delayMS, bool isPrevHalfStep) {
    // Perform a wave-step
    if (isPrevHalfStep) {
        digitalWrite(pCoil, LOW);
        digitalWrite(nCoil, HIGH);
        delay(delayMS);
        digitalWrite(nCoil, LOW);
    }
    // Perform a full-step
    else {
        digitalWrite(pCoil, HIGH);
        digitalWrite(nCoil, HIGH);
        delay(delayMS);
        digitalWrite(pCoil, LOW);
        digitalWrite(nCoil, LOW);
    }
}
#endif
/////////////////////////////////////////////////
//EOF
