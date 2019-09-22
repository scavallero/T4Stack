#include "T4Stack.h"

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
    Serial.print("T4Stack initializing...");
  }

  // LCD INIT
  if (LCDEnable == true) {
    Lcd.begin();
  }

  // TF Card
  if (SDEnable == true) {
    SD.begin(TFCARD_CS_PIN, SPI, 40000000);
  }

  // Set wakeup button
  Power.setWakeupButton(BUTTON_A_PIN);

  // I2C init
  if (I2CEnable == true) {
    Wire.begin(21, 22);
  }

  if (SerialEnable == true) {
    Serial.println("OK");
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
