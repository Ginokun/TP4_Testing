#include <stdio.h>
// To use time library of C
#include <time.h>

typedef enum
{
    Unlocked,
    Locked,
    ValidAccess,
    InvalidAccess
} LOCK_STATE_T;

typedef enum
{
    Closed,
    Opened
} DOOR_STATE_T;

typedef enum
{
    Alarm_Off,
    Alarm_On
} ALARM_STATE_T;

typedef enum
{
    Led_Off,
    Led_On
} LED_STATE_T;

typedef struct
{
    DOOR_STATE_T Door_State;
    LOCK_STATE_T Lock_State;
    ALARM_STATE_T Alarm_State;
    LED_STATE_T Led_State;
} Door_t;


void Unlock(Door_t *Door);
void Lock(Door_t *Door);
void Smartlock_FSM(Door_t *Door);