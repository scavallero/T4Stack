#ifndef _CONFIG_H_
  #define _CONFIG_H_

  // Screen
  #define TFT_LED_PIN 4
  #define TFT_DC_PIN 32
  #define TFT_CS_PIN 27
  #define TFT_MOSI_PIN 23
  #define TFT_CLK_PIN 18
  #define TFT_RST_PIN 5
  #define TFT_MISO_PIN 12

  // SD card
  #define TFCARD_CS_PIN 13
  #define TFCARD_MOSI_PIN 15
  #define TFCARD_CLK_PIN 14
  #define TFCARD_MISO_PIN 2
  

  // Buttons
  #define BTN_A 0
  #define BTN_B 1
  #define BTN_C 2
  #define BUTTON_A 0
  #define BUTTON_B 1
  #define BUTTON_C 2
  #define BUTTON_A_PIN 38
  #define BUTTON_B_PIN 37
  #define BUTTON_C_PIN 39

  // BEEP PIN
  #define SPEAKER_PIN 25
  #define TONE_PIN_CHANNEL 0


  // UART
  #define USE_SERIAL Serial

#endif /* SETTINGS_C */
