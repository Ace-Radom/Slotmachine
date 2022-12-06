#ifndef _SLOTM_H_
#define _SLOTM_H_

#include<Arduino.h>
#include"display.h"

#define MAX_CONTINUOUS_LOST_TIME 20U

#define PULL_SIGNAL( x ) ( x == INPUT_PULLUP ) ? LOW : HIGH

typedef uint8_t PIN;

class SOLTMACHINE{

    // public interface
    public:
        SOLTMACHINE( PIN , int , PIN , int , uint16_t );

        /**
         * \brief judge if a coin is operated
         * \return coin sensor status, operated as true
         */
        bool is_Coin_Sensor_triggered() {
            if ( digitalRead( Coin_Sensor ) == Coin_Sensor_Trigger_Signal )
            {
                delay( 1000 ); // avoid retriggered sensor
                return true;
            }
            return false;
        }

        /**
         * \brief judge if start handle is pulled down (by judging the button on the top's status)
         * \return start handle (or the button) status, pulled (or pressed) as true
         */
        bool is_Start_Handle_pulled() { return ( ( digitalRead( Start_Handle ) == Start_Handle_Trigger_Signal ) ? true : false ); }
    
    private:

    // data members
    protected:
        uint16_t randomNUM;
        uint16_t continuous_lost_time;

        uint16_t MAX_CLT; // MAX_Continuous_Lost_Time setting (in class)

        PIN Coin_Sensor;
        PIN Start_Handle;
        int Coin_Sensor_Trigger_Signal;
        int Start_Handle_Trigger_Signal;


};

#endif