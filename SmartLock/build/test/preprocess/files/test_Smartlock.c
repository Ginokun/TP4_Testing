#include "src/Smartlock.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


Door_t FrontDoor;



void setUp(void)

{

    FrontDoor.Door_State = Closed;

    FrontDoor.Lock_State = Opened;

    FrontDoor.Alarm_State = Off;

}



void tearDown(void)

{

}







void test_LockOpen(void)

{

    FrontDoor.Lock_State = Locked;



    LockOpen(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Unlocked)), (UNITY_INT)((FrontDoor.Lock_State)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT);

}







void test_LockClose(void)

{

    LockOpen(&FrontDoor);



    LockClose(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Locked)), (UNITY_INT)((FrontDoor.Lock_State)), (

   ((void *)0)

   ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_UINT);

}







void test_OpenDoorWithClosedLock(void)

{



    FrontDoor.Door_State = Opened;

    LockClose(&FrontDoor);



    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((On)), (UNITY_INT)((FrontDoor.Alarm_State)), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_UINT);

}







void test_OpenDoorWithOpenedLock(void)

{

    FrontDoor.Door_State = Opened;

    LockOpen(&FrontDoor);

    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Off)), (UNITY_INT)((FrontDoor.Alarm_State)), (

   ((void *)0)

   ), (UNITY_UINT)(70), UNITY_DISPLAY_STYLE_UINT);

}







void test_CloseLockWithOpenDoor(void)

{

    FrontDoor.Door_State = Opened;

    Smartlock_FSM(&FrontDoor);



    LockClose(&FrontDoor);

    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((On)), (UNITY_INT)((FrontDoor.Alarm_State)), (

   ((void *)0)

   ), (UNITY_UINT)(83), UNITY_DISPLAY_STYLE_UINT);

}
