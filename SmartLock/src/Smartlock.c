#include "Smartlock.h"

#define OPEN_DOOR_TIME 5 //Seconds that the lock remains Unlocked.
#define OPEN_DOOR_TIME 0 //Miliseconds that the lock remains Unlocked.

void Smartlock_FSM(Door_t *Door)
{
    switch (Door->Lock_State)
    {
    case Locked:
        if (Door->Door_State == Opened)
        {
            AlarmTurnOn(Door); //suena la alarma por un tiempo para indicar que se forzo la puerta o se cerro con la puerta abierta.
        }
        else if (Door->Door_State == Closed)
        {
            AlarmTurnOff(Door);
        }
        /* code */
        break;

    case Unlocked:
        if (Door->Door_State == Opened)
        {
        }
        else if (Door->Door_State == Closed)
        {
        }
        /* code */
        break;

    default:
        while (1);
        break;
    }
}

void LockOpen(Door_t *Door)
{
    Door->Lock_State = Unlocked; //Se abre la cerradura.
}

void LockClose(Door_t *Door)
{
    //Door->Open_Time = CLOSE_DOOR_TIME; //Arranca el timer de tiempo de apertura.
    Door->Lock_State = Locked; //Se cierra la cerradura.
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void AlarmTurnOn(Door_t *Door)
{
    Door->Alarm_State = On;
}
void AlarmTurnOff(Door_t *Door)
{
    Door->Alarm_State = Off;
}