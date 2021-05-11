//
// Created by Qian Chen on 4/12/21.
//

#include "pidController.h"

float pidController::calc(float Ref, float Feedback) {
    error[1] = error[0];
    error[0] = Ref-Feedback;
    float p_out = kp*error[0];
    i_out += ki*error[0];
    i_out = constrain(i_out, -i_limit, i_limit);
    float d_out = kd*(error[0]-error[1]);

    return constrain(p_out+i_out+d_out, -out_limit, out_limit);
}

void pidController::clear_i_out() {
    i_out = 0.0f;
}