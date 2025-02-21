void SW1PresetRotary(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse)
{
    int N = analogChannel - 1;

    int Number = analogButtonNumber[N];
    int FieldPlacement = fieldPlacement;

    int maxPos = 12;

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

    int value;
    if (analogPins[N] > 49)
    {
      value = ADS1115value[analogPins[N] - ADC_CORR];
    }
    else
    {
      value = analogRead(analogPins[N]);
    }
    
    #else

    int value = analogRead(analogPins[N]);
    
    #endif

    int positions[12] = { pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11, pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }

    result--;

    if (reverse)
    {
        result = 11 - result;
    }

    if (bootPreset) //Load boot preset on startup
    {
        switchPreset = result;
        presets(switchPreset);
        bootPreset = false;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
        {

            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.
            //If you want to avoid switching mode, set fieldPlacement to 0.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                for (int i = 0; i < maxPos + 1; i++) //Remove the remnants from SWITCH MODE 1
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                analogSwitchMode1[N] = !analogSwitchMode1[N]; //SWAP MODE
            }

            //Engage encoder pulse timer
            analogTimer2[N] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            analogTempState[N] = result - analogLastCounter[N];

            //Give new value to pushState

            analogLastCounter[N] = result;

            if (pushState[presetButtonRow - 1][presetButtonCol - 1] == 1) //Standard
            {
                //Set the preset value
                switchPreset = result;

                //Set new preset
                presets(switchPreset);
            }
        }
    }

    //SWITCH MODE 1: 12 - position switch

    if (!analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2 && !pushState[presetButtonRow - 1][presetButtonCol - 1])
    {
        analogTempState[N] = 0; //Refreshing encoder mode difference

        uint8_t value = analogLastCounter[N];
        if (quickSwitchState || quickSwitch34State)
        {
            value = quickValue3;
        }

        for (int i = 0; i < 12; i++)
        {
            if (i == value)
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
        }
    }

    //SWITCH MODE 2: Incremental switch

    else if (analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2 && !pushState[presetButtonRow - 1][presetButtonCol - 1])
    {
        Number = analogButtonNumberIncMode[N];
        int difference = analogTempState[N];
        if (difference != 0)
        {
            if (globalClock - analogTimer2[N] < encoderPulse)
            {
                if ((difference > 0 && difference < 5) || difference < -5)
                {
                    Joystick.setButton(Number, 1);
                    Joystick.setButton(Number + 1, 0);
                }
                else
                {
                    Joystick.setButton(Number, 0);
                    Joystick.setButton(Number + 1, 1);
                }
            }
            else
            {
                analogTempState[N] = 0;
                Joystick.setButton(Number, 0);
                Joystick.setButton(Number + 1, 0);
            }
        }
    }

    //Push the switch mode
    long push = 0;
    push = push | analogSwitchMode1[N];
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;

    //Push the preset number
    long pesh = 0;
    pesh = pesh | (switchPreset << 10);
    buttonField = buttonField | pesh;


}

void SW1PresetRotaryPulse(int analogChannel, int fieldPlacement, int pos1, int pos2, int pos3, int pos4, int pos5, int pos6, int pos7, int pos8, int pos9, int pos10, int pos11, int pos12, bool reverse, uint8_t offset, int8_t starterRow, int8_t starterCol)
{
    int N = analogChannel - 1;

    int Number = analogButtonNumber[N];
    int FieldPlacement = fieldPlacement;

    int maxPos = 12;

    #if(USING_ADS1115 == 1 || USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)

    int value;
    if (analogPins[N] > 49)
    {
      value = ADS1115value[analogPins[N] - ADC_CORR];
    }
    else
    {
      value = analogRead(analogPins[N]);
    }
    
    #else

    int value = analogRead(analogPins[N]);
    
    #endif

    int positions[12] = { pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11, pos12 };

    int differ = 0;
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        if (i == 0 || abs(positions[i] - value) < differ)
        {
            result++;
            differ = abs(positions[i] - value);
        }
    }

    result--;

    if (offset != 0)
    {
        result = result + offset;
        if (result > 11)
        {
            result = result - maxPos;
        }
    }

    if (reverse)
    {
        result = 11 - result;
    }

    if (bootPreset) //Load boot preset on startup
    {
        switchPreset = result;
        presets(switchPreset);
        bootPreset = false;
    }

    //Short debouncer on switch rotation

    if (analogLastCounter[N] != result)
    {
        if (globalClock - analogTimer1[N] > analogPulse)
        {
            analogTimer1[N] = globalClock;
        }
        else if (globalClock - analogTimer1[N] > analogWait)
        {

            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.
            //If you want to avoid switching mode, set fieldPlacement to 0.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
            {
                for (int i = 0; i < maxPos + 1; i++) //Remove the remnants from SWITCH MODE 1
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                analogSwitchMode1[N] = !analogSwitchMode1[N]; //SWAP MODE
            }

            //Engage encoder pulse timer
            analogTimer2[N] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            analogTempState[N] = result - analogLastCounter[N];

            //Give new value to pushState

            analogLastCounter[N] = result;

            if (pushState[presetButtonRow - 1][presetButtonCol - 1] == 1) //Standard
            {
                //Set the preset value
                switchPreset = result;

                //Set new preset
                presets(switchPreset);
            }
        }
    }

    //SWITCH MODE 1: 12 - position switch

    if (!analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2 && !pushState[presetButtonRow - 1][presetButtonCol - 1])
    {
        analogTempState[N] = 0; //Refreshing encoder mode difference
        uint8_t value = analogLastCounter[N];

        if (quickSwitchState || quickSwitch34State)
        {
            value = quickValue3;
        }

        for (int i = 0; i < 12; i++)
        {
            if (i == value)
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
        }
    }

    //SWITCH MODE 2: Rotary Analog Pulse

    else if (analogSwitchMode1[N] && !biteButtonBit1 && !biteButtonBit2 && !pushState[presetButtonRow - 1][presetButtonCol - 1])
    {
        analogTempState[N] = 0;
        uint8_t value = analogLastCounter[N];

        if (quickSwitchState || quickSwitch34State)
        {
          value = quickValue3;
        }

        if (!qs3LastState && (quickSwitchState || quickSwitch34State))
        {
          qs3LastState = true;
          analogTimer2[N] = globalClock;
        }
        else if (qs3LastState && (!quickSwitchState && !quickSwitch12State))
        {
          qs3LastState = false;
          analogTimer2[N] = globalClock;
        }

        if (pushState[starterRow - 1][starterCol - 1] == 1)
        {
          analogTimer2[N] = globalClock; 
        }

        if (globalClock - analogTimer2[N] < encoderPulse)
        {
          for (int i = 0; i < 12; i++)
          {
            if (i == value)
            {
                Joystick.pressButton(i + Number);
            }
            else
            {
                Joystick.releaseButton(i + Number);
            }
          }
        }
        else
        {
          for (int i = 0; i < 12; i++)
          {
              Joystick.releaseButton(i + Number);
          }
        }

    }

    //Push the switch mode
    long push = 0;
    push = push | analogSwitchMode1[N];
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;

    //Push the preset number
    long pesh = 0;
    pesh = pesh | (switchPreset << 10);
    buttonField = buttonField | pesh;
}

