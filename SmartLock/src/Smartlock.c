#include "Smartlock.h"

static void AlarmTurnOn(Door_t *Door);
static void AlarmTurnOff(Door_t *Door);
static void LedTurnOn(Door_t *Door);
static void LedTurnOff(Door_t *Door);

void Smartlock_FSM(Door_t *Door)
{
    switch (Door->Lock_State)
    {
    case Locked:
        if (Door->Door_State == Opened)
        {
            LedTurnOn(Door);
            AlarmTurnOn(Door); //suena la alarma por un tiempo para indicar que se forzo la puerta o se cerro con la puerta abierta.
        }
        else if (Door->Door_State == Closed)
        {
            AlarmTurnOff(Door);
            LedTurnOff(Door);
        }
        /* code */
        break;

    case Unlocked:
        AlarmTurnOff(Door);
        if (Door->Door_State == Opened)
        {
            LedTurnOn(Door);
        }else if (Door->Door_State == Closed)
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

void Unlock(Door_t *Door)
{
    Door->Lock_State = Unlocked; //Se abre la cerradura.
}

void Lock(Door_t *Door)
{
    //Door->Open_Time = CLOSE_DOOR_TIME; //Arranca el timer de tiempo de apertura.
    Door->Lock_State = Locked; //Se cierra la cerradura.
}

static void AlarmTurnOn(Door_t *Door)
{
    Door->Alarm_State = Alarm_On;
}

static void AlarmTurnOff(Door_t *Door)
{
    Door->Alarm_State = Alarm_Off;
}

static void LedTurnOn(Door_t *Door)
{
    Door->Led_State = Led_On;
}

static void LedTurnOff(Door_t *Door)
{
    Door->Led_State = Led_Off;
}