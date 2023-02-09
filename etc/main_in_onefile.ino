#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<TM1637.h>
#include<Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel( 24 , 8 , NEO_GRB + NEO_KHZ800 );
LiquidCrystal_I2C Lcd( 0x27 , 20 , 2 );
TM1637 tm1637( 11 , 10 );

int w,x,y,z;

int times = 0;

int Gen(){
    w = random( 1 , 4 );
    x = random( 1 , 4 );
    y = random( 1 , 4 );
    z = random( 1 , 4 );
}

void ls(){
    tone( 7 , 523 );
    delay( 500 );
    tone( 7 , 659 );
    delay( 500 );
    tone( 7 , 784 );
    delay( 500 );
    tone( 7 , 659 );
    delay( 500 );
    tone( 7 , 523 );
    delay( 500 );
    noTone( 7 );
}

void lsf(){
    tone( 7 , 784 );
    delay( 500 );
    tone( 7 , 659 );
    delay( 500 );
    tone( 7 , 523 );
    delay( 500 );
    noTone( 7 );
}


void LED_Ring_Show( uint8_t start_pos , uint16_t brightness ){
    pixels.begin();
    int n[25];
    pixels.clear();
        
    n[1] = start_pos;
    for ( int k = 2 ; k <= 24 ; k++ )
    {
        n[k] = n[k-1] - 1;
        if ( n[k] < 0 )
        {
            n[k] += 24;
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

    delay( 30 );
}

void setup(){
    Lcd.init();
    Lcd.backlight();
    randomSeed( analogRead( A1 ) );


    tm1637.set();
    tm1637.init();
    tm1637.point( POINT_OFF );

    pixels.begin();

    pinMode(PIN_A0,INPUT_PULLUP);
}

int sp = 0;

void loop() {
    LED_Ring_Show( sp , 5 );
    pixels.show();

    if(!digitalRead(PIN_A0)) { //MÜNZ EINWURF

    delay( 100 );
    Lcd.clear();
    Lcd.print( "Hebel eindrueck" );

    while ( digitalRead( PIN_A5 ) );
     //HEBEL 
        Gen();
        pixels.clear();
        pixels.show();
        delay( 200 );

        int8_t n[] = { w , x , y , z };
   
        if ( w == x && x == y && y == z )
        { //was passiert wenn man gewinnt
            delay( 200 );
            tm1637.clearDisplay();
            tm1637.display( n );
            Lcd.clear();
            Lcd.print( " " );
            Lcd.print( " " );
            Lcd.print( " " );
            Lcd.print( " " );
            Lcd.print( "Gewonnen!" );
            pixels.fill( pixels.Color( 0 , 255 , 0 ) , 0 , 24 );
            pixels.show();
        // TON 
            ls();

            times = 0;
        //ENDE VOM TON
        }
        else
        {
            times++;
            if ( times == 5 )
            {
                delay( 200 );
                Lcd.clear();
                Lcd.print(" ");
                Lcd.print(" ");
                Lcd.print(" ");
                Lcd.print(" ");
                Lcd.print("Gewonnen!");
                n[1] = w;
                n[2] = w;
                n[3] = w;
                tm1637.clearDisplay();
                tm1637.display( n );
                pixels.fill( pixels.Color( 0 , 255 , 0 ) , 0 , 24 );
                pixels.show();

                ls();

                times = 0;
            }
            else
            {
                delay( 200 );
                Lcd.clear();
                Lcd.print( "     " );
                Lcd.print( "Schade!" );
                tm1637.clearDisplay();
                tm1637.display( n );
                pixels.fill( pixels.Color( 255 , 0 , 0 ) , 0 , 24 );
                pixels.show();
                lsf();
            }
        } 
    pixels.clear();
    tm1637.clearDisplay();

    Lcd.clear();
    pixels.show();
    Lcd.print( "Muenze einwerfen" ); 
    
}

    sp == 23 ? sp = 0 : sp++;
}