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

#include "T4Stack.h"

SPIClass sdSPI(VSPI);

T4Stack::T4Stack() : isInited(0) {
}

void T4Stack::begin(bool LCDEnable, bool SDEnable, bool SerialEnable, bool I2CEnable) {
  // Correct init once
  if (isInited == true) {
    return;
  } else {
    isInited = true;
  }

  // UART
  if (SerialEnable == true) {
    Serial.begin(115200);
    Serial.flush();
    delay(50);
    Serial.println("T4Stack initializing...");
  }

  // LCD INIT
  if (LCDEnable == true) {
    Lcd.begin();
  }

  // TF Card
  if (SDEnable == true) {
	sdSPI.begin(TFCARD_CLK_PIN, TFCARD_MISO_PIN, TFCARD_MOSI_PIN, TFCARD_CS_PIN);
	if (!SD.begin(TFCARD_CS_PIN, sdSPI)) 
	{
		Serial.println("SDCard mount fail.");
	}
	else
	{
		Serial.println("SDCard mounted.");
	}
    
  }

  // Set wakeup button
  Power.setWakeupButton(BUTTON_A_PIN);

  // I2C init
  if (I2CEnable == true) {
    Wire.begin(21, 22);
  }

  if (SerialEnable == true) {
    Serial.println("T4Stack initializing done.");
  }
}

void T4Stack::update() {
  //Button update
  BtnA.read();
  BtnB.read();
  BtnC.read();

  //Speaker update
  Speaker.update();
}

// Deprecated method declared for compatibility
void T4Stack::setPowerBoostKeepOn(bool en) {
  T4.Power.setPowerBoostKeepOn(en);
}
void T4Stack::setWakeupButton(uint8_t button) {
  T4.Power.setWakeupButton(button);
}
void T4Stack::powerOFF() {
  T4.Power.deepSleep();
}

T4Stack T4;
