//
// Created by Qian Chen on 4/12/21.
//

#ifndef LAB6_PIDCONTROLLER_H
#define LAB6_PIDCONTROLLER_H

#include "Arduino.h"

class pidController {
public:
    float kp;
    float ki;
    float kd;
    float i_limit;
    float out_limit;
    float calc(float Ref, float Feedback);
    void clear_i_out();
private:
    float i_out = 0.0f;
    float error[2] = {0.0f,0.0f};
};

#endif //LAB6_PIDCONTROLLER_H
