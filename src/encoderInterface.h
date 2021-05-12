//
// Created by Qian Chen on 5/12/21.
//

#ifndef ECE_206_LAB_6_ENCODERINTERFACE_H
#define ECE_206_LAB_6_ENCODERINTERFACE_H

#include "Arduino.h"

class encoderInterface {
public:
    /**
    * @brief initialize the interface
    * @param PIN_A_ port for A
    * @param PIN_B_ port for B
    * */
    encoderInterface(int PINA_, int PINB_): PIN_A(PINA_), PIN_B(PINB_) {
        pinMode(PIN_A, INPUT);
        pinMode(PIN_B, INPUT);
    }

    void update();

    int getRotCount();
    int rotCount = 0;

private:
    int PIN_A;
    int PIN_B;
    int A[2] = {0,0};
    int B[2] = {0,0};
    int current_angle_raw = 0;
};


#endif //ECE_206_LAB_6_ENCODERINTERFACE_H
