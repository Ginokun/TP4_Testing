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

Door_t FrontDoor;

void setUp(void)
{
    FrontDoor.Door_State = Closed;   //Todos los test inician con la puerta cerrada. (esta variable va a depender de un sensor)
    FrontDoor.Lock_State = Unlocked; //Todos los tests inician con la cerradura desbloqueada.
    FrontDoor.Alarm_State = Alarm_Off;     //Todos los tests inician con la alarma apagada.
    FrontDoor.Led_State = Led_Off;  //Todos los tests inician con el led apagado.
}

void tearDown(void)
{
}

/*La cerradura se desbloquea*/

void test_Unlock(void)
{
    FrontDoor.Lock_State = Locked;

    Unlock(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(Unlocked, FrontDoor.Lock_State);
}

/*La cerradura si se cierra se la bloquea*/

void test_LockClose(void)
{
    Unlock(&FrontDoor);

    Lock(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(Locked, FrontDoor.Lock_State);
}

/*Suena alarma si se abre la puerta estando Locked.*/

void test_OpenDoorLocked(void)
{

    FrontDoor.Door_State = Opened;
    Lock(&FrontDoor); //Se cierra la cerradura para hacer el test.

    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(Alarm_On, FrontDoor.Alarm_State);
}

/*No suena la alarma si se abre la puerta sin estar la cerradura bloqueada.*/

void test_OpenDoorWithOpenedLock(void)
{
    FrontDoor.Door_State = Opened;
    Unlock(&FrontDoor);        //Se abre la cerradura para hacer el test.
    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(Alarm_Off, FrontDoor.Alarm_State);
}

/*Suena la alarma si se quiere bloquear la cerradura estando abierta la puerta*/

void test_CloseLockWithOpenDoor(void)
{
    FrontDoor.Door_State = Opened;
    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    Lock(&FrontDoor);          //Se cierra la cerradura para hacer el test.
    Smartlock_FSM(&FrontDoor); //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(Alarm_On, FrontDoor.Alarm_State);
}

/*Si la alarma se encuentra encendida, se debe apagar si se cierra la puerta o si se desbloquea la cerradura.*/

void test_TurnOffAlarm(void)
{
    FrontDoor.Alarm_State = Alarm_On; //Se fija como encendida la alarma.
    Smartlock_FSM(&FrontDoor);  //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(Alarm_Off, FrontDoor.Alarm_State);
}

/*Se enciende un led si la puerta se encuentra abierta.*/

void test_TurnOnLockLed(void)
{
    FrontDoor.Door_State = Opened; //Se abre la puerta
    Smartlock_FSM(&FrontDoor);     //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(Led_On, FrontDoor.Led_State);
}


/*Se apaga el led cuando la puerta se encuentra cerrada.*/

void test_TurnOffLockLed(void)
{
    FrontDoor.Led_State = Led_On; //Se abre la puerta
    Smartlock_FSM(&FrontDoor);     //Se actualiza la maquina de estados.

    TEST_ASSERT_EQUAL_UINT(Led_Off, FrontDoor.Led_State);
}