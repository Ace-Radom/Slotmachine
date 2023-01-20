#include"slotm.h"

SOLTMACHINE::SOLTMACHINE( PIN _Coin_Sensor , int _Coin_Sensor_Trigger_Signal ,
                          PIN _Start_Handle , int _Start_Handle_Trigger_Signal ,
                          PIN _Digit_Display_CLK , PIN _Digit_Display_DIO ,
                          PIN _Speaker ,
                          uint16_t _MAX_CLT ){
    Coin_Sensor = _Coin_Sensor;
    Start_Handle  = _Start_Handle;

    Coin_Sensor_Trigger_Signal  = _Coin_Sensor_Trigger_Signal;
    Start_Handle_Trigger_Signal = _Start_Handle_Trigger_Signal;
    Digit_CLK = _Digit_Display_CLK;
    Digit_DIO = _Digit_Display_DIO;
    Speaker = _Speaker;

    MAX_CLT = _MAX_CLT;

    is_start_allowed = false;
    randomNUM = 0;
    continuous_lost_time = 0;

    return;
}

bool is_start_slot_allowed( SOLTMACHINE& __sm ){
    return ( __sm.is_start_allowed ? true : false );
}