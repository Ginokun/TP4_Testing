#include <stdio.h>

typedef enum
{
    UNLOCKED,
    LOCKED,
    VALID_ACCESS,
    INVALID_ACCESS
} lock_state_t;


typedef enum
{
    CLOSED,
    OPENED
} door_state_t;

typedef enum
{
    ALARM_OFF,
    ALARM_ON
} alarm_state_t;

typedef enum
{
    LED_OFF,
    LED_ON
} led_state_t;

typedef struct
{
    door_state_t Door_State;
    lock_state_t Lock_State;
    alarm_state_t Alarm_State;
    led_state_t Led_State;
} door_t;


void Unlock(door_t *Door);
void Lock(door_t *Door);
void Smartlock_FSM(door_t *Door);