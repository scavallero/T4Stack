/*
 
 T4Stack

Copyright (c) 2019 Salvatore Cavallero

 Derived from the original M5Stack Arduino library, Copyright (c) M5Stack
 
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef _T4STACK_H_
  #define _T4STACK_H_
  
  #if defined(ESP32)

    #include "gitTagVersion.h"
    #include <Arduino.h>
    #include <Wire.h>
    #include <SPI.h>
    #include "FS.h"
    #include "SD.h"

    #include "T4Display.h"
    #include "utility/Config.h"
    #include "utility/Button.h"
    #include "utility/Speaker.h"
    #include "utility/Power.h"
    #include "utility/CommUtil.h"

    class T4Stack
    {
      public:
        T4Stack();
        void begin(bool LCDEnable = true, bool SDEnable = true, bool SerialEnable = true, bool I2CEnable = false);
        void update();

        // Button API
        #define DEBOUNCE_MS 10
        Button BtnA = Button(BUTTON_A_PIN, true, DEBOUNCE_MS);
        Button BtnB = Button(BUTTON_B_PIN, true, DEBOUNCE_MS);
        Button BtnC = Button(BUTTON_C_PIN, true, DEBOUNCE_MS);

        // SPEAKER
        SPEAKER Speaker;

        // LCD
        T4Display Lcd = T4Display();

        // Power
        POWER Power;
          
        // I2C
        CommUtil I2C = CommUtil();
          
        /**
        * Function has been move to Power class.(for compatibility)
        * This name will be removed in a future release.
        */
        void setPowerBoostKeepOn(bool en) __attribute__((deprecated));
        void setWakeupButton(uint8_t button) __attribute__((deprecated));
        void powerOFF() __attribute__((deprecated));
        
      private:
          bool isInited;
    };
    
    extern T4Stack T4;
    #define t4 T4
    #define lcd Lcd
  #else
    #error “This library only supports boards with ESP32 processor.”
  #endif
#endif
