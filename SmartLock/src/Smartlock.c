#include "Smartlock.h"

static void AlarmTurnOn(door_t *Door);
static void AlarmTurnOff(door_t *Door);
static void LedTurnOn(door_t *Door);
static void LedTurnOff(door_t *Door);

void Smartlock_FSM(door_t *Door)
{
    switch (Door->Lock_State)
    {
    case LOCKED:
        if (Door->Door_State == OPENED)
        {
            LedTurnOn(Door);
            AlarmTurnOn(Door); //suena la alarma por un tiempo para indicar que se forzo la puerta o se cerro con la puerta abierta.
        }
        else if (Door->Door_State == CLOSED)
        {
            AlarmTurnOff(Door);
            LedTurnOff(Door);
        }
        /* code */
        break;

    case UNLOCKED:
        AlarmTurnOff(Door);
        if (Door->Door_State == OPENED)
        {
            LedTurnOn(Door);
        }else if (Door->Door_State == CLOSED)
        {
            LedTurnOff(Door);
        }

        break;

    default:
        while (1)
            ;
        break;
    }
}

void Unlock(door_t *Door)
{
    Door->Lock_State = UNLOCKED; //Se abre la cerradura.
}

void Lock(door_t *Door)
{
    //Door->Open_Time = CLOSE_DOOR_TIME; //Arranca el timer de tiempo de apertura.
    Door->Lock_State = LOCKED; //Se cierra la cerradura.
}

static void AlarmTurnOn(door_t *Door)
{
    Door->Alarm_State = ALARM_ON;
}

static void AlarmTurnOff(door_t *Door)
{
    Door->Alarm_State = ALARM_OFF;
}

static void LedTurnOn(door_t *Door)
{
    Door->Led_State = LED_ON;
}

static void LedTurnOff(door_t *Door)
{
    Door->Led_State = LED_OFF;
}