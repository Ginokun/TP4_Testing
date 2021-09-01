/*

La cerradura abre si se la debloquea. 
La cerradura cierra si se la bloquea.
Suena alarma si se abre la puerta estando Locked.
No suena la alarma estando la puerta Unlocked. 
Suena alarma si se quiere Lockear estando abierta la puerta.

*/

#include "unity.h"
#include "Smartlock.h"

Door_t FrontDoor;

void setUp(void)
{
    FrontDoor.Door_State = Closed; //Todos los test inician con la puerta cerrada.
    FrontDoor.Lock_State = Opened; //Todos los tests inician con la cerradura abierta.
    FrontDoor.Alarm_State = Off;   //Todos los tests inician con la alarma apagada.
}

void tearDown(void)
{
}

/*La cerradura abre si se la desbloquea*/

void test_LockOpen(void)
{
    FrontDoor.Lock_State = Locked;

    LockOpen(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(Unlocked, FrontDoor.Lock_State);
}

/*La cerradura si se cierra se la bloquea*/

void test_LockClose(void)
{
    LockOpen(&FrontDoor);

    LockClose(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(Locked, FrontDoor.Lock_State);
}

/*Suena alarma si se abre la puerta estando Locked.*/

void test_OpenDoorWithClosedLock(void)
{

    FrontDoor.Door_State = Opened;
    LockClose(&FrontDoor); //Se cierra la cerradura para hacer el test.

    Smartlock_FSM(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(On, FrontDoor.Alarm_State);
}

/*No suena la alarma estando la puerta Unlocked.*/

void test_OpenDoorWithOpenedLock(void)
{
    FrontDoor.Door_State = Opened;
    LockOpen(&FrontDoor); //Se abre la cerradura para hacer el test.
    Smartlock_FSM(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(Off, FrontDoor.Alarm_State);
}

/*Suena la alarma si se quiere Lockear estando abierta la puerta*/

void test_CloseLockWithOpenDoor(void)
{
    FrontDoor.Door_State = Opened;
    Smartlock_FSM(&FrontDoor);      //Se actualiza la maquina de estados.

    LockClose(&FrontDoor); //Se cierra la cerradura para hacer el test.
    Smartlock_FSM(&FrontDoor);

    TEST_ASSERT_EQUAL_UINT(On, FrontDoor.Alarm_State);
}