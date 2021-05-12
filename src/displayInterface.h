//
// Created by Qian Chen on 5/12/21.
//

#ifndef ECE_206_LAB_6_DISPLAYINTERFACE_H
#define ECE_206_LAB_6_DISPLAYINTERFACE_H

#include "Arduino.h"

class displayInterface {
public:
    void init();
    void showNum(int num, int digit);
};


#endif //ECE_206_LAB_6_DISPLAYINTERFACE_H
