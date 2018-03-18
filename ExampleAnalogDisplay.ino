// ========================================================================================
//      Meine Welt in meinem Kopf
// ========================================================================================
// Projekt:       TFT, Sensor and Graphics
// Author:        Johannes P. Langner
// Controller:    Arduino Duemilanove
// Sensors:       
// Actor:         TFT 1.8" 128x160 SPI (on TFT Shield)
// Description:   Sensor Daten ergebnisse auf dem TFT schreiben
// ========================================================================================

#include <SPI.h>
#include <TFT.h>
#include <Wire.h>

// ========================================================================================
// TFT 128x160

#define CS   10
#define DC   9
#define RST  8

TFT mScreen = TFT(CS, DC, RST);

// ========================================================================================
// defines and variables

int mLocationAnalogDisplayX = 10;                       // X Postion of the anlaog display
int mLocationAnalogDisplayY = 20;                       // Y Postion of the anlaog display

float mValuePointer = 0.0;                              // actual value to show on display
float mValuePointerLast = 0.0;                          // last value to clear on display

float mValuePointer2 = 0.0;                              // actual value to show on display
float mValuePointerLast2 = 0.0;                          // last value to clear on display

// ========================================================================================
void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  Serial.println("Initialisiere TFT");
  mScreen.begin();
  mScreen.background(0, 0, 0);
  mScreen.stroke(255, 255, 255);
  mScreen.setTextSize(1);
  mScreen.text("Analog Display ", 5, 5);

                                                        // first analaog display for max 1023
  renderAnalogDisplay(mLocationAnalogDisplayX,          // set location x
                      mLocationAnalogDisplayY,          // set location y
                      0.0,                              // value to draw on display
                      1023,
                      false,                            // not clear
                      true);                            // draw all

                                                        // secound analaog display for max 500
  renderAnalogDisplay(mLocationAnalogDisplayX + 70,     // set location x
                      mLocationAnalogDisplayY,          // set location y
                      0.0,                              // value to draw on display
                      500,
                      false,                            // not clear
                      true);                            // draw all
  
  pinMode(A0, INPUT);                                   // only for test and demo
}

// ========================================================================================
void loop() {

  int readValue = analogRead(A0);
  mValuePointer = (float)readValue;                     // set new value

                                                        // first analaog display for max 1023
                                                        // clear last rendered value
  renderAnalogDisplay(mLocationAnalogDisplayX,          // set location x
                      mLocationAnalogDisplayY,          // set location y
                      mValuePointerLast,                // last value for clear
                      1023,
                      true,                             // clear with last value
                      false);                           // draw only pointer for clear

                                                        // render actual value
  renderAnalogDisplay(mLocationAnalogDisplayX,          // set location x
                      mLocationAnalogDisplayY,          // set location y
                      mValuePointer,                    // value to draw on display
                      1023,
                      false,                            // not clear
                      false);                           //  draw only pointer 


                                                        // secound analaog display for max 500
                                                        // clear last rendered value
  renderAnalogDisplay(mLocationAnalogDisplayX + 70,     // set location x
                      mLocationAnalogDisplayY,          // set location y
                      mValuePointerLast,                // value to draw on display
                      500,
                      true,                             // not clear
                      false);                           // draw only pointer 
                                                        
                                                        // render actual value
  renderAnalogDisplay(mLocationAnalogDisplayX + 70,     // set location x
                      mLocationAnalogDisplayY,          // set location y
                      mValuePointer,                    // value to draw on display
                      500,
                      false,                            // not clear
                      false);                           //  draw only pointer 
                      
  mValuePointerLast = mValuePointer;                    // set remember last value

  delay(10);
}
