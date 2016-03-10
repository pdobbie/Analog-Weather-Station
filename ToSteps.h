// ToSteps.h
// Patrick Dobbie, Feb. 28, 2016
//
// Convert various inputs into stepper motor step
// equivalents.
/////////////////////////////////////////////////
#ifndef ToSteps_H
#define ToSteps_H

#include "application.h"
#include <string>
#include <vector>

int valueToSteps(std::string value, int min, int max, uint8_t maxSteps) {
    double val = atof(value.c_str());
    if (val<min) {val=min;}
    if (val>max) {val=max;}

    return int((val-min)/(max-min)*maxSteps);
}
int codeToSteps(std::string code, std::vector<std::string> rangeCode, uint8_t maxSteps) {
    int i=0;
    while (i<rangeCode.size()) {
        if (code == rangeCode[i]) {break;}
        ++i;
    }
    return int(i/(double)rangeCode.size()*maxSteps);
}

#endif
/////////////////////////////////////////////////
//EOF
