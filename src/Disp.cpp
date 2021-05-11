//
// Created by Qian Chen on 5/12/21.
//

#include "Disp.h"

void Disp::showNum(int num, int digit) {
    if(num == 0){
        PORTD=B01110001;
        PORTB=B111010;
    }
    if(num == 1){
        PORTD=B11110111;
        PORTB=B111110;
    }
    if(num == 2){
        PORTD=B01101001;
        PORTB=B111110;
    }
    if(num == 3){
        PORTD=B01100011;
        PORTB=B111110;
    }
    if(num == 4){
        PORTD=B11100111;
        PORTB=B111010;
    }
    if(num == 5){
        PORTD=B01100011;
        PORTB=B111011;
    }
    if(num == 6){
        PORTD=B01100001;
        PORTB=B111011;
    }
    if(num == 7){
        PORTD=B01110111;
        PORTB=B111110;
    }
    if(num == 8){
        PORTD=B01100001;
        PORTB=B111010;
    }
    if(num == 9){
        PORTD=B01100011;
        PORTB=B111010;
    }
    if(digit==0){
        PORTD=PORTD|B01000000;
        PORTB=PORTB&B111101;
    }
    if(digit==1){
        PORTD=PORTD&B10111111;
        PORTB=PORTB|B000010;
    }
}