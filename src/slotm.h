#ifndef _SLOTM_H_
#define _SLOTM_H_

#include<Arduino.h>

#define MAX_CONTINUOUS_LOST_TIME 20U

typedef uint8_t PIN;

class SOLTMACHINE{
    public:
        SOLTMACHINE( PIN , PIN , uint16_t );

        bool is_Start_Handle_pulled();
    
    private:
        uint16_t randomNUM;
        uint16_t continuous_lost_time;

        uint16_t MAX_CLT; // MAX_Continuous_Lost_Time setting (in class)

        PIN Motion_Sensor;
        PIN Start_Handle;


};

#endif