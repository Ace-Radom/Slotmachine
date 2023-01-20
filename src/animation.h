#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include<Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<TM1637.h>
#ifdef __AVR__
#include<avr/power.h>
#endif

#define NUMPIXELS 24

namespace Slotmachine_Tool {

    const uint16_t LED_Ring_Pause = 30;
    
    void LED_Ring_Show( Adafruit_NeoPixel& pixels , uint8_t start_pos , uint16_t brightness );
    void Game_Process_Animation_Show( Adafruit_NeoPixel& pixels , TM1637& tm1637 );

} // namespace Slotmachine_Tool

#endif