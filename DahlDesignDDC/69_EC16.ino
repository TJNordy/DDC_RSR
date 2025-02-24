void EC16Multis(int row, int column, int fieldPlacement, int positions1, int positions2, int positions3, bool reverse)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int Number = buttonNumber[Row][Column];
    int8_t FieldPlacement = fieldPlacement;
    int8_t Reverse = reverse;

    //Find switch absolute position

    bool Pin1 = rawState[Row][Column];
    bool Pin2 = rawState[Row][Column + 1];
    bool Pin3 = rawState[Row][Column + 2]

    int maxPos = max(positions3, (max(positions2, max(12, positions1))));

    bool array[4] = { Pin1, Pin2, Pin3, Pin4 };

    int pos = 0;

    for (int i = 0; i < 3; i++)
    {
        if (array[i])
        {
            pos = i;
        }
    }
    
    int result = pos;

    //Store Counting Positions

    uint8_t CountPos;

    if (!switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Counting 1
    {
        CountPos = positions1;
    }
    else if (switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Counting 2
    {
        CountPos = positions2;
    }
    else if (!switchMode[Row][Column] && switchMode[Row][Column + 1]) //Counting 3
    {
        CountPos = positions3;
    }

    //Short debouncer on switch rotation
    if (pushState[Row][Column] != result)
    {
        if (globalClock - switchTimer[Row][Column] > encoderPulse)
        {
            switchTimer[Row][Column] = globalClock;
        }
        else if (globalClock - switchTimer[Row][Column] > encoderWait)
        {

            //----------------------------------------------
            //----------------MODE CHANGE-------------------
            //----------------------------------------------

            //Due to placement of this scope, mode change will only occur on switch rotation.
            //If you want to avoid pushing mode, set fieldPlacement to 0.

            if (pushState[modButtonRow - 1][modButtonCol - 1] == 1 && FieldPlacement != 0)
            {
                for (int i = 1; i <= maxPos; i++) //Remove the remnants from SWITCH MODE 1
                {
                    Joystick.releaseButton(i - 1 + Number);
                }

                if (!switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Going to mode 2
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = true;
                    CountPos = positions2;
                }
                else if (switchMode[Row][Column] && !switchMode[Row][Column + 1]) //Going to mode 3
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = false;
                    CountPos = positions3;
                }
                else if (!switchMode[Row][Column] && switchMode[Row][Column + 1]) //Going to mode 4
                {
                    switchMode[Row][Column + 1] = true;
                    switchMode[Row][Column] = true;
                }
                else if (switchMode[Row][Column] && switchMode[Row][Column + 1]) //Going to mode 1
                {
                    switchMode[Row][Column + 1] = false;
                    switchMode[Row][Column] = false;
                    CountPos = positions1;
                }
            }

            //Engage encoder pulse timer
            switchTimer[Row][Column + 1] = globalClock;

            //Update difference, storing the value in pushState on pin 2
            pushState[Row][Column + 1] = result - pushState[Row][Column];

            //Give new value to pushState
            pushState[Row][Column] = result;

            //If we're in pseudomulti, change counter
            if (!(switchMode[Row][Column] && switchMode[Row][Column + 1]))
            {
                if ((pushState[Row][Column + 1] > 0 && pushState[Row][Column + 1] < 6) || pushState[Row][Column + 1] < -6)
                {
                    pushState[Row][Column + 2] = pushState[Row][Column + 2] + 1 - (2 * Reverse);
                }
                else
                {
                    pushState[Row][Column + 2] = pushState[Row][Column + 2] - 1 + (2 * Reverse);
                }
                if (pushState[Row][Column + 2] < 0)
                {
                    pushState[Row][Column + 2] = CountPos - 1; 
                }
            }

            //If we're not in hybrid at all, reset counter
            else
            {
                pushState[Row][Column + 2] = 0;
            }
        }
        
        //SWITCH MODE 4: Incremental encoder

        if (switchMode[Row][Column] && switchMode[Row][Column + 1])
        {
            Number = buttonNumber[Row][Column + 1];
            int difference = pushState[Row][Column + 1];
            if (difference != 0)
            {
                if (globalClock - switchTimer[Row][Column + 1] < encoderPulse)
                {
                    if ((difference > 0 && difference < 6) || difference < -6)
                    {
                        Joystick.setButton(Number + Reverse, 1);
                        Joystick.setButton(Number + 1 - Reverse, 0);
                    }
                    else
                    {
                        Joystick.setButton(Number + Reverse, 0);
                        Joystick.setButton(Number + 1 - Reverse, 1);
                    }
                }
                else
                {
                    pushState[Row][Column + 1] = 0;
                    Joystick.setButton(Number, 0);
                    Joystick.setButton(Number + 1, 0);
                }
            }
        }

        //SWITCH MODE 1-3: Multiposititon switches
          
        else
        {
            for (int i = 1; i <= CountPos; i++) 
            {
                int e = pushState[Row][Column + 2] % CountPos;
                if (e == 0)
                {
                    e = CountPos;
                }
                if (i == e)
                {
                    Joystick.pressButton(i - 1 + Number);
                }
                else
                {
                    Joystick.releaseButton(i - 1 + Number);
                }
            }
        }
    }
    //Push switch mode
    long push = 0;
    push = push | switchMode[Row][Column];
    push = push | (switchMode[Row][Column + 1] << 1);
    push = push << (FieldPlacement - 1);
    rotaryField = rotaryField | push;
}
