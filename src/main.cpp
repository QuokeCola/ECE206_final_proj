/*ECE 206 Lab 6: Motor Proportional Speed Control*/
#include <Arduino.h>
#include "pidController.h"
#include "motorInterface.h"
#include "RotEncoder.h"
#include "Disp.h"

const int pwmPinPos = 11;
const int pwmPinNeg = 12;

float refRPM = 120.0f; // reference speed (Revolution Per Minute)
float currRPM = 0; // current speed
int currPWM = 0; // current PWM output

const int loopTime = 100; // every 100 ms, the code enters update_speed()
int timePassed = 0;
unsigned long prevMillis = 0; // last time (ms) the code entered update_speed()
volatile long cnt = 0; // number of times Hall sensor passed the magnets

float Kp = 2.5f;
float Ki = 0.5f;
float Kd = 1.0f;
float i_limit = 255.0f;
int out_limit = 255.0f;

int disp_switch_interval;
long int disp_last_update_time;
bool digit = false;
pidController PIDController;
motorInterface MotorInterface(A0, A1, pwmPinPos, pwmPinNeg, 100);
RotEncoder rotEncoder(A2, A3);
Disp disp;

void print_motor_info() {
    //print reference RPM and current RPM
    Serial.println("refRPM currRPM");
    Serial.println(String(refRPM)+" "+String(currRPM));
}

void update_speed() {
    // TODO update currRPM, error, and currPWM variables.
    // There are three magnets inside a wheel encoder. Since the gearbox ratio is 1:48, there will be total 48*3 magnets detected per revolution.
    // Also, the number of magnets passed every loopTime is cnt. Use this information to find the current motor RPM.
    currRPM = MotorInterface.velcoity;
    currPWM = PIDController.calc(refRPM, currRPM);
    MotorInterface.setPWM(currPWM);

    //reference speed can be typed in by a user in Serial Monitor or Serial Plotter
    refRPM = rotEncoder.rotCount*2.0f;
}

void setup() {
    PIDController.kp = Kp;
    PIDController.ki = Ki;
    PIDController.kd = Kd;
    PIDController.i_limit = i_limit;
    PIDController.out_limit = out_limit;
    disp_last_update_time = millis();
}

void loop() {
    timePassed = millis() - prevMillis;
    MotorInterface.updateMotorFeedback();
    rotEncoder.update();
    if(timePassed >= loopTime){
        print_motor_info();
        update_speed();
        //reset cnt and time
        cnt = 0;
        prevMillis = millis();
    }
    if(disp_switch_interval< millis() - disp_last_update_time) {
        int num2show = 0;
        if(digit) {
            num2show = (int)MotorInterface.velcoity % 10;
        } else {
            num2show = (int)MotorInterface.velcoity / 10;
        }
        disp.showNum(num2show, (int) digit);
        disp_last_update_time = millis();
        digit = !digit;
    }
}

