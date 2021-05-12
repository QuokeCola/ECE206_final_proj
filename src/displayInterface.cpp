//
// Created by Qian Chen on 5/12/21.
//

#include "displayInterface.h"

void displayInterface::init() {
    DDRD=B11111110;
    DDRB=B000111;
}
void displayInterface::showNum(int i, int digit) {
    // Profiles for each number
    //                  0               1               2               3               4           5               6               7           8                   9
    int sete[10][10] = {{1,2,3,7,8,10}, {3,8},          {1,2,4,7,8},    {2,3,4,7,8},    {3,4,8,10}, {7,10,4,2,3},   {7,10,4,3,1,2}, {3,7,8},    {1,2,3,4,7,8,10},   {2,3,7,8,4,10}};
    int setd[10][10] = {{4},            {1,2,4,7,10},   {3,10},         {1,10},         {1,2,7},    {1,8},          {8},            {1,2,4,10}, {0},                {1}};
    // Digit
    if (digit == 1) {
        digitalWrite(9, LOW);
        digitalWrite(6, HIGH);
    } else {
        digitalWrite(6, LOW);
        digitalWrite(9, HIGH);
    }
    // Write HIGH digit
    for (int j = 0; j< 10; j++) {
        if(setd[i][j]!=0) {
            digitalWrite(setd[i][j],HIGH);
        }
    }
    // Write LOW digit
    for (int j = 0; j< 10; j++) {
        if(sete[i][j]!=0) {
            digitalWrite(sete[i][j],LOW);
        }
    }
}