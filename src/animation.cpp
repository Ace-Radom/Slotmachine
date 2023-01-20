#include"animation.h"

/**
 * @brief show a 24-bit gradient color on led ring
 * 
 * @param pixels Adafruit_NeoPixel base class (led ring's deployment class)
 * @param start_pos start position of the gradient color (always in range 0~23)
 * @param brightness how bright is this gradient color (in range 1~5)
 */
void Slotmachine_Tool::LED_Ring_Show( Adafruit_NeoPixel& pixels , uint8_t start_pos , uint16_t brightness ){
    pixels.begin();
    int n[NUMPIXELS+1];
    pixels.clear();
        
    n[1] = start_pos;
    for ( int k = 2 ; k <= NUMPIXELS ; k++ )
    {
        n[k] = n[k-1] - 1;
        if ( n[k] < 0 )
        {
            n[k] += NUMPIXELS;
        }
    }

#pragma region set_pixel

    pixels.setPixelColor( n[ 1] ,  0              , 51 * brightness ,  0              );
    pixels.setPixelColor( n[ 2] ,  3 * brightness , 43 * brightness ,  0              );
    pixels.setPixelColor( n[ 3] , 11 * brightness , 35 * brightness ,  0              );
    pixels.setPixelColor( n[ 4] , 19 * brightness , 27 * brightness ,  0              );
    pixels.setPixelColor( n[ 5] , 27 * brightness , 19 * brightness ,  0              );
    pixels.setPixelColor( n[ 6] , 35 * brightness , 11 * brightness ,  0              );
    pixels.setPixelColor( n[ 7] , 43 * brightness ,  3 * brightness ,  0              );
    pixels.setPixelColor( n[ 8] , 51 * brightness ,  0              ,  0              );
    pixels.setPixelColor( n[ 9] , 51 * brightness ,  0              ,  0              );
    pixels.setPixelColor( n[10] , 43 * brightness ,  0              ,  3 * brightness );
    pixels.setPixelColor( n[11] , 35 * brightness ,  0              , 11 * brightness );
    pixels.setPixelColor( n[12] , 27 * brightness ,  0              , 19 * brightness );
    pixels.setPixelColor( n[13] , 19 * brightness ,  0              , 27 * brightness );
    pixels.setPixelColor( n[14] , 11 * brightness ,  0              , 35 * brightness );
    pixels.setPixelColor( n[15] ,  3 * brightness ,  0              , 43 * brightness );
    pixels.setPixelColor( n[16] ,  0              ,  0              , 51 * brightness );
    pixels.setPixelColor( n[17] ,  0              ,  0              , 51 * brightness );
    pixels.setPixelColor( n[18] ,  0              ,  3 * brightness , 43 * brightness );
    pixels.setPixelColor( n[19] ,  0              , 11 * brightness , 35 * brightness );
    pixels.setPixelColor( n[20] ,  0              , 19 * brightness , 27 * brightness );
    pixels.setPixelColor( n[21] ,  0              , 27 * brightness , 19 * brightness );
    pixels.setPixelColor( n[22] ,  0              , 35 * brightness , 11 * brightness );
    pixels.setPixelColor( n[23] ,  0              , 43 * brightness ,  3 * brightness );
    pixels.setPixelColor( n[24] ,  0              , 51 * brightness ,  0              );
    pixels.show();

#pragma endregion set_pixel

    delay( LED_Ring_Pause );
}

/**
 * @brief show the game process animation on led ring and TM1637 display
 * 
 * @param pixels Adafruit_NeoPixel base class (led ring's deployment class)
 * @param tm1637 TM1637 display base class
 */
void Slotmachine_Tool::Game_Process_Animation_Show( Adafruit_NeoPixel& pixels , TM1637& tm1637 ){
    for ( int i = 0 ; i <= 255 ; i += 3 )
    {
        pixels.fill( pixels.Color( 0 , 204 , 255 ) , 0 , NUMPIXELS );
        pixels.setBrightness( i );
        pixels.show();
        delay( LED_Ring_Pause );
    }

    for ( int i = 255 ; i >= 0 ; i -= 5 )
    {
        pixels.fill( pixels.Color( 0 , 204 , 255 ) , 0 , NUMPIXELS );
        pixels.setBrightness( i );
        pixels.show();
        delay( LED_Ring_Pause );
    }
}