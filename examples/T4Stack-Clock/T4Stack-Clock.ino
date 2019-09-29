/*
 
 T4Stack Clock

Copyright (c) 2019 Salvatore Cavallero

 Based on clock sketch by Gilchrist 6/2/2014 1.0
 
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
 
#include <T4Stack.h>

uint32_t targetTime = 0;

uint8_t hh = 0;
uint8_t mm = 0; 
uint8_t ss = 0;
int brightness = 150;
uint8_t omm = 99;
uint8_t oss = 99;
uint8_t xcolon = 0;
uint8_t xsecs = 0;
unsigned int colour = 0;

void setup(void) {
  //Serial.begin(115200);
  T4.begin();
  // M5.Lcd.setRotation(1);
  T4.Lcd.fillScreen(TFT_BLACK);

  T4.Lcd.setTextSize(1);
  T4.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);

  T4.Lcd.setBrightness(brightness);
  targetTime = millis() + 1000;
}

void loop() 
{
  if (targetTime < millis()) 
  {  
    targetTime = millis() + 1000;

    // Time adjust, add 1 second
    ss++;              
    if (ss == 60) 
    {    
      ss = 0;          
      omm = mm;        
      mm++;            
      if (mm > 59) 
      {   
        mm = 0;
        hh++;          
        if (hh > 23) 
        { 
          hh = 0;
        }
      }
    }

    // Update digital time
    int xpos = 0;
    int ypos = 85; // Top left corner ot clock text, about half way down
    int ysecs = ypos + 24;

    if (omm != mm) { // Redraw hours and minutes time every minute
      omm = mm;
      // Draw hours and minutes
      if (hh < 10) xpos += T4.Lcd.drawChar('0', xpos, ypos, 8); // Add hours leading zero for 24 hr clock
      xpos += T4.Lcd.drawNumber(hh, xpos, ypos, 8);             // Draw hours
      xcolon = xpos; // Save colon coord for later to flash on/off later
      xpos += T4.Lcd.drawChar(':', xpos, ypos - 8, 8);
      if (mm < 10) xpos += T4.Lcd.drawChar('0', xpos, ypos, 8); // Add minutes leading zero
      xpos += T4.Lcd.drawNumber(mm, xpos, ypos, 8);             // Draw minutes
      xsecs = xpos; // Sae seconds 'x' position for later display updates
    }
    if (oss != ss) { // Redraw seconds time every second
      oss = ss;
      xpos = xsecs;

      if (ss % 2) { // Flash the colons on/off
        T4.Lcd.setTextColor(0x39C4, TFT_BLACK);        // Set colour to grey to dim colon
        T4.Lcd.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += T4.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        T4.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);    // Set colour back to yellow
      }
      else {
        T4.Lcd.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += T4.Lcd.drawChar(':', xsecs, ysecs, 6); // Seconds colon
      }

      //Draw seconds
      if (ss < 10) xpos += T4.Lcd.drawChar('0', xpos, ysecs, 6); // Add leading zero
      T4.Lcd.drawNumber(ss, xpos, ysecs, 6);                     // Draw seconds
    }
  }

  T4.update();
  if (T4.BtnC.wasPressed())
  {
    brightness+=30;
    if (brightness > 255)
      brightness = 250;
      T4.Lcd.setBrightness(brightness);
  }
  if (T4.BtnA.wasPressed())
  {
    brightness-=30;
    if (brightness < 0)
      brightness = 0;
      T4.Lcd.setBrightness(brightness);
  }
  delay(100);    
}
