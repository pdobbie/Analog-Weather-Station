// Stepper.cpp
// Patrick Dobbie, Feb. 25, 2016
//
// Initiaize the movement functions of the motor.
/////////////////////////////////////////////////
#include "application.h"
#include "Stepper.h"
#include "StepModes.h"
#include <vector>
using namespace std;

Stepper::Stepper(uint8_t stepMode, uint8_t delayMS, vector<uint8_t> pinCoils, uint8_t pinPower, uint8_t curStep)
: stepMode(stepMode),
delayMS(delayMS),
pinCoils(pinCoils),
pinPower(pinPower),
curStep(curStep) {
}

void Stepper::rotateStepper(int8_t steps) {
    steps -= curStep;

    if (steps==0) {return;}
    if (pinPower>-1) {powerOn(pinPower);}

    bool isPrevHalfStep = false;
    int pCoil=0;
    int nCoil=0;

    // Step forwards
    if (steps>0) {
        switch (stepMode) {
        // Wave-step
        case 0:
            pCoil = curStep%4;
            nCoil = pCoil+1;
            for (int i=0; i<steps; ++i) {
                if (pCoil>3) {pCoil=0;}
                if (nCoil>3) {nCoil=0;}
                waveStepOne(pinCoils[pCoil],pinCoils[nCoil],delayMS);
                ++pCoil; ++nCoil;
            }
            break;
        // Full-step
        case 1:
            pCoil = (curStep%4)+1;
            if (pCoil>3) {pCoil=0;}
            nCoil = pCoil+1;
            for (int i=0; i<steps; ++i) {
                if (pCoil>3) {pCoil=0;}
                if (nCoil>3) {nCoil=0;}
                fullStepOne(pinCoils[pCoil],pinCoils[nCoil],delayMS);
                ++pCoil; ++nCoil;
            }
            break;
        // Half-step
        case 2:
            if ((curStep%2) != 0) {isPrevHalfStep=true;}
            pCoil = (curStep/2)%4;
            nCoil = pCoil+1;
            for (int i=0; i<steps; ++i) {
                if (pCoil>3) {pCoil=0;}
                if (nCoil>3) {nCoil=0;}
                halfStepOne(pinCoils[pCoil],pinCoils[nCoil],delayMS,isPrevHalfStep);
                if (isPrevHalfStep) {++pCoil; ++nCoil;}
                isPrevHalfStep = !isPrevHalfStep;
            }
            break;
        }
    }
    // Step backwards
    else {
        switch (stepMode) {
        // Wave-step
        case 0:
            pCoil = curStep%4;
            nCoil = pCoil-1;
            for (int i=0; i<-steps; ++i) {
                if (pCoil<0) {pCoil=3;}
                if (nCoil<0) {nCoil=3;}
                waveStepOne(pinCoils[pCoil],pinCoils[nCoil],delayMS);
                --pCoil; --nCoil;
            }
            break;
        // Full-step
        case 1:
            pCoil = curStep%4;
            nCoil = pCoil-1;
            for (int i=0; i<-steps; ++i) {
                if (pCoil<0) {pCoil=3;}
                if (nCoil<0) {nCoil=3;}
                fullStepOne(pinCoils[pCoil],pinCoils[nCoil],delayMS);
                --pCoil; --nCoil;
            }
            break;
        // Half-step
        case 2:
            if ((curStep%2) != 0) {isPrevHalfStep=true;}
            pCoil = (curStep/2)%4;
            nCoil = pCoil-1;
            for (int i=0; i<-steps; ++i) {
                if (pCoil<0) {pCoil=3;}
                if (nCoil<0) {nCoil=3;}
                halfStepOne(pinCoils[pCoil],pinCoils[nCoil],delayMS,isPrevHalfStep);
                if (isPrevHalfStep) {--pCoil; --nCoil;}
                isPrevHalfStep = !isPrevHalfStep;
            }
            break;
        }
    }
    if (pinPower>-1) {powerOff(pinPower);}
}

void Stepper::resetStepper(uint8_t maxSteps) {
    curStep=maxSteps;
    rotateStepper(0);
}
/////////////////////////////////////////////////
//EOF
