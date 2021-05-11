//
// Created by Qian Chen on 4/15/21.
//

#ifndef ECE_206_LAB_6_MOTORINTERFACE_H
#define ECE_206_LAB_6_MOTORINTERFACE_H

#include "Arduino.h"

/**
 * @author Qian Chen
 * @brief A motor interface for DC-Motor with Encoder
 * */
class motorInterface {
public:
    /**
     * @brief initialize the interface
     * @param PIN_A_ port for A
     * @param PIN_B_ port for B
     * @param OUT_POS_ port for Output Positive Rotation
     * @param OUT_NEG_ port for Output Negative Rotation
     * */
    motorInterface(int PIN_A_, int PIN_B_, int OUT_POS_, int OUT_NEG_, int update_interval_) :
            PIN_A(PIN_A_), PIN_B(PIN_B_), OUT_POS(OUT_POS_), OUT_NEG(OUT_NEG_), update_interval(update_interval_) {
        pinMode(PIN_A, INPUT);
        pinMode(PIN_B, INPUT);
        pinMode(OUT_POS, OUTPUT);
        pinMode(OUT_NEG, OUTPUT);
    }

    /**
     * @brief set PWM for motor
     * @param PWM range from (-254 to 254), the sign decide the direction
     * */
    void setPWM (int PWM);

    /**
     * @brief execute in every loop, it would update the velocity of motor;
     * */
    void updateMotorFeedback ();

    float velcoity = 0.0f;
private:
    int PIN_A;
    int PIN_B;
    int OUT_POS;
    int OUT_NEG;
public:
    float current_angle_raw = 0.0f;
    float last_angle_raw = 0.0f;
    bool A[2] = {0,0};
    bool B[2] = {0,0};
    long int last_update_time;
    int update_interval;
};


#endif //ECE_206_LAB_6_MOTORINTERFACE_H
