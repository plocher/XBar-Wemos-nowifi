/*
 *  Test harness code for I2C extender
 *
 *  Copyright (c) 2014 John Plocher, released under the terms of the MIT License (MIT)
 */

#include <Wire.h>
#include <I2Cexpander.h>
#include <Crossbar.h>

#define NUMPORTS 7
I2Cexpander m[NUMPORTS];

Crossbar *crossbar;

void testRelays() {
    for (int booster = 0; booster < 8; booster++) {
        for (int board = 0; board < 3; board++) {
            for (int node = 0; node < 7; node++) {
                crossbar->select(node * 3 + board, booster);
            }
        }
    }
}



void setup() {
 
    Serial.begin(19200); 
    while (!Serial); // wait for serial port to connect. Needed for Leonardo only
    Serial.println("Testing I2C");
    delay(250);
  
    crossbar = new Crossbar(m, 1);
    
    for (int x = 0; x < NUMPORTS; x++) {
        m[x]       = I2Cexpander();
    }
    //Wire.begin();
    Wire.begin(D2, D1);

    m[ 6].init(6, I2Cexpander::PCA9555,  B0);
    m[ 5].init(5, I2Cexpander::PCA9555,  B0);
    m[ 4].init(4, I2Cexpander::PCA9555,  B0);
    m[ 3].init(3, I2Cexpander::PCA9555,  B0);
    m[ 2].init(2, I2Cexpander::PCA9555,  B0);
    m[ 1].init(1, I2Cexpander::PCA9555,  B0);
    m[ 0].init(0, I2Cexpander::PCA9555,  B0);

    
    testRelays();
    
    //delay(250);

    for (int node = 0; node < 7; node++) {
        for (int board = 0; board < 3; board++) {
          crossbar->select(node * 3 + board, 1);
        }
    }
}

void loop() {
  delay(5000);
}

