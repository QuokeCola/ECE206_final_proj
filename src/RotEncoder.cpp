//
// Created by Qian Chen on 5/12/21.
//

#include "RotEncoder.h"

void RotEncoder::update() {
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
    if(current_angle_raw > 4) {
        rotCount++;
        current_angle_raw = 0;
    } else if (current_angle_raw < -4) {
        rotCount--;
        current_angle_raw = 0;
    }
}