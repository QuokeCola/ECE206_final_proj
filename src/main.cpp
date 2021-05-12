/*ECE 206 Lab 6: Motor Proportional Speed Control*/
#include <Arduino.h>
#include "pidController.h"
#include "motorInterface.h"
#include "encoderInterface.h"
#include "displayInterface.h"
#include "../.pio/libdeps/uno/IRremote/src/IRremote.h"

const int pwmPinPos = 11;
const int pwmPinNeg = 5;
const int RECV_PIN = 12;

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

int disp_switch_interval = 10;
long int disp_last_update_time;
bool digit = false;
pidController PIDController;
motorInterface MotorInterface(A0, A1, pwmPinPos, pwmPinNeg, 100);
encoderInterface EncoderInterface(A2, A3);
displayInterface DisplayInterface;

IRrecv irrecv(RECV_PIN);
decode_results results;

#define POWER 0xFF629D

#define UP 0xFF9867
#define DOWN 0xFF38C7
#define LEFT 0xFF30CF
#define RIGHT 0xFF7A85
#define SELECT 0xFF18E7

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
}

void setup() {
    PIDController.kp = Kp;
    PIDController.ki = Ki;
    PIDController.kd = Kd;
    PIDController.i_limit = i_limit;
    PIDController.out_limit = out_limit;
    disp_last_update_time = millis();
    irrecv.enableIRIn();
    DisplayInterface.init();
    Serial.begin(115200);
}

void loop() {
    timePassed = millis() - prevMillis;
    MotorInterface.updateMotorFeedback();
    EncoderInterface.update();
    if(timePassed >= loopTime){
        print_motor_info();
        update_speed();
        //reset cnt and time
        cnt = 0;
        refRPM += ((float)EncoderInterface.getRotCount()*5.0f);
        prevMillis = millis();
        //Serial.println(currPWM);
    }
    if(disp_switch_interval< millis() - disp_last_update_time) {
        int num2show;
        if(!digit) {
            num2show = (int)abs(MotorInterface.velcoity) % 10;
        } else {
            num2show = (int)abs(MotorInterface.velcoity) / 10;
        }
        DisplayInterface.showNum(num2show, (int) digit);
        disp_last_update_time = millis();
        digit = !digit;
    }
    if (irrecv.decode(&results))
    {
        Serial.println("Recv");
        Serial.println(results.value);
        if (results.value == POWER||results.value == 5316027)
        {
            Serial.println("Stop");
            if(refRPM != 0) {
                refRPM = 0.0f;
            }
        }
        else if (results.value == UP||results.value == 2538093563)
        {
            Serial.println("UP");
            refRPM = refRPM + 5.0f;
        }
        else if (results.value == DOWN||results.value == 1217346747)
        {
            Serial.println("DOWN");
            refRPM = refRPM - 5.0f;
        }
        irrecv.resume();
    }
}

