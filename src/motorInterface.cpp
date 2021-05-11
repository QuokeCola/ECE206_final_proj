//
// Created by Qian Chen on 4/15/21.
//

#include "motorInterface.h"

void motorInterface::setPWM(int PWM) {
    if (PWM > 0) {
        analogWrite(OUT_NEG, LOW);
        analogWrite(OUT_POS, PWM);
    } else {
        analogWrite(OUT_POS, LOW);
        analogWrite(OUT_NEG, -PWM);
    }
}

void motorInterface::updateMotorFeedback() {

    /*** Rotation Detection ***/
    A[0] = A[1];
    B[0] = B[1];
    A[1] = digitalRead(PIN_A);
    B[1] = digitalRead(PIN_B);
    if((!A[0]&&!A[1]&&!B[0]&& B[1])||
       (!A[0]&& A[1]&& B[0]&& B[1])||
       ( A[0]&& A[1]&& B[0]&&!B[1])||
       A[0]&&!A[1]&&!B[0]&&!B[1]) { // Turn CW
        current_angle_raw ++;
    } else if (!(A[0]==A[1]&&B[0]==B[1])) { // Turn CCW (Except same position,
        // the rest condition was turning CCW)
        current_angle_raw --;
    }
    if(millis() - last_update_time > (unsigned) update_interval) {
        velcoity = float(current_angle_raw - last_angle_raw)/float(millis()-last_update_time)/576.0f*60000.0f;
        last_angle_raw = current_angle_raw;
        last_update_time = millis();
    }
}