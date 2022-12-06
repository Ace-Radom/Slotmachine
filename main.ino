/**
 * 
 */

#include"src/display.h"
#include"src/slotm.h"

#define cs 1 // coin sensor
#define sh 2 // start handle

SOLTMACHINE solt( cs , PULL_SIGNAL( INPUT_PULLUP ) , // coin sensor
                  sh , PULL_SIGNAL( INPUT_PULLUP ) , // start handle
                  MAX_CONTINUOUS_LOST_TIME );

void setup(){
    pinMode( cs , INPUT_PULLUP );
    pinMode( sh , INPUT_PULLUP );
}

void loop(){
    if ( solt.is_Coin_Sensor_triggered() )
    {

    }

    if ( solt.is_Start_Handle_pulled() )
    {
        
    }
}