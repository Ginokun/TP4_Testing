#include "src/Smartlock.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


Door_t FrontDoor;



void setUp(void)

{

    FrontDoor.Door_State = Closed;

    FrontDoor.Lock_State = Unlocked;

    FrontDoor.Alarm_State = Alarm_Off;

    FrontDoor.Led_State = Led_Off;

}



void tearDown(void)

{

}







void test_Unlock(void)

{

    FrontDoor.Lock_State = Locked;



    Unlock(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Unlocked)), (UNITY_INT)((FrontDoor.Lock_State)), (

   ((void *)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT);

}







void test_LockClose(void)

{

    Unlock(&FrontDoor);



    Lock(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Locked)), (UNITY_INT)((FrontDoor.Lock_State)), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_UINT);

}







void test_OpenDoorLocked(void)

{



    FrontDoor.Door_State = Opened;

    Lock(&FrontDoor);



    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Alarm_On)), (UNITY_INT)((FrontDoor.Alarm_State)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT);

}







void test_OpenDoorWithOpenedLock(void)

{

    FrontDoor.Door_State = Opened;

    Unlock(&FrontDoor);

    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Alarm_Off)), (UNITY_INT)((FrontDoor.Alarm_State)), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_UINT);

}







void test_CloseLockWithOpenDoor(void)

{

    FrontDoor.Door_State = Opened;

    Smartlock_FSM(&FrontDoor);



    Lock(&FrontDoor);

    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Alarm_On)), (UNITY_INT)((FrontDoor.Alarm_State)), (

   ((void *)0)

   ), (UNITY_UINT)(87), UNITY_DISPLAY_STYLE_UINT);

}







void test_TurnOffAlarm(void)

{

    FrontDoor.Alarm_State = Alarm_On;

    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Alarm_Off)), (UNITY_INT)((FrontDoor.Alarm_State)), (

   ((void *)0)

   ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_UINT);

}







void test_TurnOnLockLed(void)

{

    FrontDoor.Door_State = Opened;

    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Led_On)), (UNITY_INT)((FrontDoor.Led_State)), (

   ((void *)0)

   ), (UNITY_UINT)(107), UNITY_DISPLAY_STYLE_UINT);

}









void test_TurnOffLockLed(void)

{

    FrontDoor.Led_State = Led_On;

    Smartlock_FSM(&FrontDoor);



    UnityAssertEqualNumber((UNITY_INT)((Led_Off)), (UNITY_INT)((FrontDoor.Led_State)), (

   ((void *)0)

   ), (UNITY_UINT)(118), UNITY_DISPLAY_STYLE_UINT);

}
