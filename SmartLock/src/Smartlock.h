#include <stdio.h>
// To use time library of C
#include <time.h>




typedef enum{
    Locked,
    Unlocked,
    ValidAccess,
    InvalidAccess
}LOCK_STATE_T;

typedef enum{
    Closed,
    Opened
}DOOR_STATE_T;

typedef enum{
    Off,
    On
}ALARM_STATE_T;

typedef struct{
DOOR_STATE_T Door_State;
LOCK_STATE_T Lock_State;
ALARM_STATE_T Alarm_State;
__uint16_t Open_Time;
}Door_t;


void AlarmTurnOn(Door_t *Door);
void LockOpen(Door_t *Door);
void LockClose(Door_t *Door);
void delay(int number_of_seconds);
void Smartlock_FSM(Door_t *Door);