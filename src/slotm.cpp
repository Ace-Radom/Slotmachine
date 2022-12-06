#include"slotm.h"

SOLTMACHINE::SOLTMACHINE( PIN _Coin_Sensor , int _Coin_Sensor_Trigger_Signal ,  PIN _Start_Handle , int _Start_Handle_Trigger_Signal , 
                          uint16_t _MAX_CLT ){
    Coin_Sensor = _Coin_Sensor;
    Start_Handle  = _Start_Handle;

    Coin_Sensor_Trigger_Signal  = _Coin_Sensor_Trigger_Signal;
    Start_Handle_Trigger_Signal = _Start_Handle_Trigger_Signal;

    MAX_CLT = _MAX_CLT;

    pinMode( Start_Handle , INPUT_PULLUP );

    randomNUM = 0;
    continuous_lost_time = 0;

    return;
}

