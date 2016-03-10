// Stepper.h
// Patrck Dobbie, Feb. 25, 2016
//
// The stepper motors being used are:
// 28BYJ-48 5V 4-Phase 5-Wire Stepper (64 Step)
// + ULN2003 Driver Board
// There are four pins required for the motor
// coils, as well as an optional power pin, for
// use with a simple transistor array.
/////////////////////////////////////////////////
#ifndef Stepper_H
#define Stepper_H

#include <vector>

class Stepper {
public:
    Stepper(uint8_t stepMode, uint8_t delayMS, std::vector<uint8_t> pinCoils, uint8_t pinPower, uint8_t curStep);
    void rotateStepper(int8_t steps);
    void resetStepper(uint8_t maxSteps);
private:
    const uint8_t stepMode; // 0-wave, 1-full, 2-half
    const uint8_t delayMS;  // Min delay is ____ ms
    const std::vector<uint8_t> pinCoils; // Vector of 4 coil pins
    const uint8_t pinPower; // Pin for power if needed
    uint8_t curStep; // Current step is stored in EEPROM, which can become corrupted
};

#endif
/////////////////////////////////////////////////
//EOF
