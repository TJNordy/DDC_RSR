//-----------------------
//-------JOYSTICK--------
//-----------------------

#define BUTTONCOUNT 105
#define HATCOUNT 1

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
    BUTTONCOUNT,   //Button count
    HATCOUNT,      //Hat switch count
    true,          //X axis, used for clutch
    true,          //Y axis, used for B field
    true,          //Z axis, used for R field
    true,          //Rx axis, used for version field
    true,          //Ry axis, used for clutch bite point
    false,         //Rz axis
    false,         //Rudder
    true,          //Throttle, used for dual clutch mode 4
    false,         //Accelerator
    true,          //Brake, used for dual clutch mode 4
    false);        //Steering
