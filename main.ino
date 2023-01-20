/**
 * Slotmachine, NwT 2-1 Arduino Halbjahrs Schluss Projekt
 * 
 * Geräte genutzt werden:
 * ┌────────────────────────────────────────────────┐
 * │ TM1637           Zahl Display                  │
 * │ WCMCU-2812B-24   LED_Ring (gleich wie WS2812B) │
 * └────────────────────────────────────────────────┘
 */

#include<TM1637.h>
#include<LiquidCrystal_I2C.h>
#include<Adafruit_NeoPixel.h>

#include"src/animation.h"

#define CS                   3 // coin sensor button input pin
#define SH              PIN_A5 // start handle button input pin
#define CLK                 10 // TM1637 clock pin
#define DIO                  9 // TM1637 data IO pin
#define Speaker              7 // speaker control pin
#define LED_Ring_DI          8 // led ring data input pin
#define Randomseed_PIN  PIN_A0 // pin used for get random seed

#define _lcd_addr_ 0x27
#define _lcd_cols_ 20
#define _lcd_rows_ 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel( NUMPIXELS , LED_Ring_DI , NEO_GRB + NEO_KHZ800 );
LiquidCrystal_I2C lcd( _lcd_addr_ , _lcd_cols_ , _lcd_rows_ );
TM1637 tm1637( CLK , DIO );

uint32_t coin_thrown_num = 0;
bool is_start_handle_pulled = false;

uint16_t LED_Ring_Start_pos = 0;
const uint16_t LED_Ring_Brightness = 5;

#define MAX_TURNS_NUM_TO_LOSE 10 // after how many turns will the player 100% win for one turn

uint16_t turns_num_already_lost = 0;

#define WAIT_LENGTH_AFTER_RESULT_SHOWED 3000

void setup(){
    pinMode( CS , INPUT );
    pinMode( SH , INPUT );

    lcd.init();
    lcd.backlight();

    tm1637.set();
    tm1637.init();
    tm1637.point( POINT_OFF );

    pixels.begin();

    randomSeed( analogRead( Randomseed_PIN ) );
    // get random seed
}

void loop(){
    Slotmachine_Tool::LED_Ring_Show( pixels , LED_Ring_Start_pos , LED_Ring_Brightness );
    // change led_ring show status in this loop

    lcd.setCursor( 0 , 0 );
    String lcd_display_temp( coin_thrown_num );
    if ( coin_thrown_num <= 1 )
    {
        lcd.clear();
        lcd_display_temp += " Chance uebrig";
    }
    else
    {
        lcd.clear();
        lcd_display_temp += " Chancen uebrig";
    }
    lcd.print( lcd_display_temp.c_str() );
    // show how many chances left (same as how many coins have been thrown into the machine)

    // bool CS_status = digitalRead( CS ); // coin sensor status
    // bool SH_status = digitalRead( SH ); // start handle status

    // if ( digitalRead( CS ) )
    // {
    //     coin_thrown_num++;
    //     delay( 200 );
    //     // delay 200 ms in order to ignore accidentally sensor triggered
    // } // coin throwed

    // if ( SH_status && !is_start_handle_pulled && ( coin_thrown_num > 0 ) )
    if ( !digitalRead( SH ) )
    {
        is_start_handle_pulled = true;
        // coin_thrown_num--;

        for ( int i = 0 ; i < 24 ; i++ )
        {
            pixels.setPixelColor( i , 0 , 0 , 0 );
            pixels.show();
            delay( Slotmachine_Tool::LED_Ring_Pause );
        } // turn off all pixels in order

#pragma region main_game_logic

        /**
         * game result should not contain 0 as design
         * therefore, by the game result creation will only get a random num. between 1 and 9
         * 0 is not included
         */

        int8_t game_result[4];
        game_result[0] = random( 1 , 9 );
        game_result[1] = random( 1 , 9 );
        game_result[2] = random( 1 , 9 );
        game_result[3] = random( 1 , 9 );
        // get each bit of the game result

        bool is_won; // did the player win in this turn

        if ( ( game_result[0] == game_result[1] ) && ( game_result[1] == game_result[2] ) && ( game_result[2] == game_result[3] ) )
        {
            is_won = true;
            turns_num_already_lost = 0;
        } // won in this turn
        else
        {
            is_won = false;
            turns_num_already_lost++;
            if ( turns_num_already_lost == MAX_TURNS_NUM_TO_LOSE )
            {
                is_won = true;
                game_result[1] = game_result[0];
                game_result[2] = game_result[0];
                game_result[3] = game_result[0];
                // change all bits of the game result to same as the first bit of itself to make the player win
                turns_num_already_lost = 0;
            } // already lost for turns same as defined MAX_TURNS_NUM_TO_LOSE, trigger break_even mechanism
        } // lost in this turn

#pragma endregion main_game_logic

        lcd.clear();
        lcd.setCursor( 0 , 0 );
        lcd.print( "Bitte warten..." );

        Slotmachine_Tool::Game_Process_Animation_Show( pixels , tm1637 );

        tm1637.display( game_result );
        // display game result on TM1637 display

        pixels.setBrightness( 255 );
        // set led ring's brightness back to 255

        lcd.clear();
        lcd.setCursor( 0 , 0 );
        if ( is_won )
        {
            lcd.print( "Congratulations!" );
        }
        else
        {
            lcd.print( "Schade!" );
        }
        delay( WAIT_LENGTH_AFTER_RESULT_SHOWED );

        tm1637.clearDisplay();
        is_start_handle_pulled = false;
    }

    LED_Ring_Start_pos == NUMPIXELS - 1 ? LED_Ring_Start_pos = 0 
                                        : LED_Ring_Start_pos++;
}