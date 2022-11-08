#include"slotm.h"

SOLTMACHINE::SOLTMACHINE( PIN _Motion_Sensor , PIN _Start_Handle ,
                          uint16_t _MAX_CLT = MAX_CONTINUOUS_LOST_TIME ){
    Motion_Sensor = _Motion_Sensor;
    Start_Handle  = _Start_Handle;

    MAX_CLT = _MAX_CLT;

    pinMode( Start_Handle , INPUT_PULLUP );

    randomNUM = 0;
    continuous_lost_time = 0;

    return;
}

/**
 * \brief judge if start handle is pulled down (by judging the button on the top's status)
 * \return start handle (or the button) status, pulled (or pressed) as true
 */
bool SOLTMACHINE::is_Start_Handle_pulled(){
    if ( digitalRead( Start_Handle ) == LOW )
    {
        return true;
    }
    return false;
}