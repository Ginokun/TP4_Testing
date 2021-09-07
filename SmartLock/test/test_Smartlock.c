/*

La cerradura abre si se la debloquea.       <---------------
La cerradura cierra si se la bloquea.       <---------------
Suena alarma si se abre la puerta estando Locked.       <---------------
No suena la alarma estando la puerta Unlocked.      <---------------
Suena alarma si se quiere Lockear estando abierta la puerta.        <---------------
Si la alarma se encuentra encendida, se debe apagar si se cierra la puerta o si se desbloque la cerradura.       <---------------
Se enciende un led si la puerta se encuentra abierta.       <---------------
Se apaga el led cuando la puerta se encuentra cerrada.      <---------------

*/

#include "unity.h"
#include "Smartlock.h"

door_t FrontDoor;

void setUp(void)
{
    FrontDoor.Door_State = CLOSED;   //Todos los test inician con la puerta cerrada. (esta variable va a depender de un sensor)
    FrontDoor.Lock_State = UNLOCKED; //Todos los tests inician con la cerradura desbloqueada.
    FrontDoor.Alarm_State = ALARM_OFF;     //Todos los tests inician con la alarma apagada.
    FrontDoor.Led_State = LED_OFF;  //Todos los tests inician con el led apagado.
}

void tearDown(void)
{
}

/*La cerradura se desbloquea*/

void test_Unlock(void)
{
    FrontDoor.Lock_State = LOCKED;

    Unlock(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(UNLOCKED, FrontDoor.Lock_State);
}

/*La cerradura si se cierra se la bloquea*/

void test_LockClose(void)
{
    Unlock(&FrontDoor);

    Lock(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(LOCKED, FrontDoor.Lock_State);
}

/*Suena alarma si se abre la puerta estando Locked.*/

void test_OpenDoorLocked(void)
{

    FrontDoor.Door_State = OPENED;
    Lock(&FrontDoor); //Se cierra la cerradura para hacer el test.

    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(ALARM_ON, FrontDoor.Alarm_State);
}

/*No suena la alarma si se abre la puerta sin estar la cerradura bloqueada.*/

void test_OpenDoorWithOpenedLock(void)
{
    FrontDoor.Door_State = OPENED;
    Unlock(&FrontDoor);        //Se abre la cerradura para hacer el test.
    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(ALARM_OFF, FrontDoor.Alarm_State);
}

/*Suena la alarma si se quiere bloquear la cerradura estando abierta la puerta*/

void test_CloseLockWithOpenDoor(void)
{
    FrontDoor.Door_State = OPENED;
    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    Lock(&FrontDoor);          //Se cierra la cerradura para hacer el test.
    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(ALARM_ON, FrontDoor.Alarm_State);
}

/*Si la alarma se encuentra encendida, se debe apagar si se cierra la puerta o si se desbloquea la cerradura.*/

void test_TurnOffAlarm(void)
{
    FrontDoor.Alarm_State = ALARM_ON; //Se fija como encendida la alarma.
    Smartlock_FSM(&FrontDoor);  //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(ALARM_OFF, FrontDoor.Alarm_State);
}

/*Se enciende un led si la puerta se encuentra abierta.*/

void test_TurnOnLockLed(void)
{
    FrontDoor.Door_State = OPENED; //Se abre la puerta
    Smartlock_FSM(&FrontDoor);     //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(LED_ON, FrontDoor.Led_State);
}


/*Se apaga el led cuando la puerta se encuentra cerrada.*/

void test_TurnOffLockLed(void)
{
    FrontDoor.Led_State = LED_ON; //Se abre la puerta
    Smartlock_FSM(&FrontDoor);     //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(LED_OFF, FrontDoor.Led_State);
}