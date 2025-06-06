void PEC11(int row, int col, bool reverse) 
{
    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }


    Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
    Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
}

void PEC11Mod(int row, int col, bool reverse) 
{
    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];
    int Reverse = reverse;

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 1)
    {
      Number += 2;
    }

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }


    Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
    Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
}

void PEC11Stack(int stackButtonRow, int stackButtonColumn, int fieldPlacement, int layers, int row, int col, bool reverse)
{
    int Row = row - 1;
    int Column = col - 1;
    int Reverse = reverse;

    int ButtonRow = stackButtonRow - 1;
    int ButtonCol = stackButtonColumn - 1;

    //Button logics
    if (pushState[ButtonRow][ButtonCol] != rawState[ButtonRow][ButtonCol] && (globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        switchTimer[ButtonRow][ButtonCol] = globalClock;
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if ((globalClock - switchTimer[ButtonRow][ButtonCol]) > buttonCooldown)
    {
        pushState[ButtonRow][ButtonCol] = rawState[ButtonRow][ButtonCol];
    }

    if (pushState[ButtonRow][ButtonCol] == 0)
    {
        latchLock[ButtonRow][ButtonCol] = false;
    }

    if (pushState[ButtonRow][ButtonCol] == 1 && !latchLock[ButtonRow][ButtonCol])
    {
        latchLock[ButtonRow][ButtonCol] = true;
        toggleTimer[ButtonRow][ButtonCol] ++;
    }
    if (toggleTimer[ButtonRow][ButtonCol] >= layers)
    {
      toggleTimer[ButtonRow][ButtonCol] = 0;
    }
    
    //Adjust button number

    int Number = buttonNumber[Row][Column] + toggleTimer[ButtonRow][ButtonCol] * 2;  

    //Encoder logic

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
    Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));

    //Push stack placement
    long push = 0;
    push = push | toggleTimer[ButtonRow][ButtonCol];
    push = push << (fieldPlacement - 1);
    rotaryField = rotaryField | push;
}

void PEC11Bite(int row, int col, bool reverse) 
{
    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }

        //----------------------------------------------
        //----------------BITE POINT SETTING------------
        //----------------------------------------------

        if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
        {
            if (!biteButtonBit1 && !biteButtonBit2)
            {
                biteButtonBit1 = true;
            }
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
        if (biteButtonBit1 || biteButtonBit2)
        {
            latchState[Row][Column] = true;
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if (biteButtonBit1 || biteButtonBit2)
        {
            latchState[Row][Column + 1] = true;
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Changing bite point

    if (latchState[Row][Column + 1]) //CW add to bite
    {
        if (biteButtonBit1 && !biteButtonBit2)
        {
            bitePoint = bitePoint + 100;
            if (bitePoint > 1000)
            {
                bitePoint = 1000;
            }
        }
        else if (!biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint + 10;
            if (bitePoint > 1000)
            {
                bitePoint = 1000;
            }
        }
        else if (biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint + 1;
            if (bitePoint > 1000)
            {
                bitePoint = 1000;
            }
        }
        latchState[Row][Column + 1] = false;
    }
    else if (latchState[Row][Column]) //CCW reduce bite
    {
        if (biteButtonBit1 && !biteButtonBit2)
        {
            bitePoint = bitePoint - 100;
            if (bitePoint < 0)
            {
                bitePoint = 0;
            }
        }
        else if (!biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint - 10;
            if (bitePoint < 0)
            {
                bitePoint = 0;
            }
        }
        else if (biteButtonBit1 && biteButtonBit2)
        {
            bitePoint = bitePoint - 1;
            if (bitePoint < 0)
            {
                bitePoint = 0;
            }
        }
        latchState[Row][Column] = false;
    }
    Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
    Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
}

void PEC11Brake(int row, int col, bool reverse) {

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          brakeMagicValue = brakeMagicValue + 10 - (20*Reverse);
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          brakeMagicValue = brakeMagicValue - 10 + (20*Reverse);
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Adjustment
    if (brakeMagicValue < 0)
    {
      brakeMagicValue = 0;
    }
    else if (brakeMagicValue > 1000)
    {
      brakeMagicValue = 1000;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
    }
}

void PEC11Throttle(int row, int col, bool reverse) {

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          throttleHoldValue = throttleHoldValue + 10 - (20*Reverse);
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          throttleHoldValue = throttleHoldValue - 10 + (20*Reverse);
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Adjustment
    if (throttleHoldValue < 0)
    {
      throttleHoldValue = 0;
    }
    else if (throttleHoldValue > 1000)
    {
      throttleHoldValue = 1000;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
    }
}

void PEC11Brightness(int row, int col, bool reverse) {

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          LEDBrightness = LEDBrightness + 2 - (4*Reverse);
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          LEDBrightness = LEDBrightness - 2 + (4*Reverse);
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Adjustment
    if (LEDBrightness < 0)
    {
      LEDBrightness = 0;
    }
    else if (LEDBrightness > 100)
    {
      LEDBrightness = 100;
    }

    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
    }

}

void PEC11Preset(int row, int col, bool reverse) {

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          if(switchPreset == 0 && Reverse)
          {
            switchPreset = 11;
          }
          else
          {
            switchPreset = switchPreset + 1 - (2 * Reverse);
          }
          if (switchPreset > 11)
          {
              switchPreset = 0;
          }

          presets(switchPreset);
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if(pushState[modButtonRow - 1][modButtonCol - 1] == 1)
        {
          if(switchPreset == 0 && !Reverse)
          {
            switchPreset = 11;
          }
          else
          {
            switchPreset = switchPreset - 1 + (2 * Reverse);
          }
          
          if (switchPreset > 11)
          {
              switchPreset = 0;
          }
          presets(switchPreset);
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }


    if (pushState[modButtonRow - 1][modButtonCol - 1] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
    }

    long push = 0;
    push = push | (switchPreset << 10);
    buttonField = buttonField | push;

}

void PEC11BiteAdjust(int row, int col, bool reverse, int increment) 
{

    int Row = row - 1;
    int Column = col - 1;
    int Number = buttonNumber[Row][Column];

    int Reverse = reverse;

    switchTimer[Row][Column + 1] = (rawState[Row][Column] | rawState[Row][Column + 1] << 1); //Assigning numbers to all switch states 0-3

    if //switch has been turned and is not cooling down, and no rotation direction has been engaged
        (switchTimer[Row][Column + 1] > 0
            &&
            (globalClock - switchTimer[Row][Column] > PEC11Cooldown)
            &&
            pushState[Row][Column] == 0
            &&
            pushState[Row][Column + 1] == 0)
    {
        switchTimer[Row][Column] = globalClock;
        if (switchTimer[Row][Column + 1] == 2) //CW turn started
        {
            pushState[Row][Column] = 1;
        }
        else if (switchTimer[Row][Column + 1] == 1) //CCW turn started
        {
            pushState[Row][Column + 1] = 1;
        }
    }

    //CW check gates
    if (pushState[Row][Column] == 1 && rawState[Row][Column])
    {
        pushState[Row][Column] = 2;
    }
    if (pushState[Row][Column] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column] = 3;
    }

    //CW check gates
    if (pushState[Row][Column + 1] == 1 && rawState[Row][Column + 1])
    {
        pushState[Row][Column + 1] = 2;
    }
    if (pushState[Row][Column + 1] == 2 && switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 3;
    }

    //Pushing successfully recorded rotations

    if (pushState[Row][Column] == 3)
    {
        toggleTimer[Row][Column] = globalClock;
        if(pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
        {
          bitePoint = bitePoint + increment  - (reverse * 2 * increment);
        }
    }
    else if (pushState[Row][Column + 1] == 3)
    {
        toggleTimer[Row][Column + 1] = globalClock;
        if(pushState[biteButtonRow - 1][biteButtonCol - 1] == 1)
        {
          bitePoint = bitePoint - increment  + (reverse * 2 * increment);
        }
    }

    if (switchTimer[Row][Column + 1] == 0)
    {
        pushState[Row][Column + 1] = 0;
        pushState[Row][Column] = 0;
    }

    //Adjustment
    if (bitePoint > 1000)
    {
      bitePoint = 1000;  
    }
    else if (bitePoint < 0)
    {
      bitePoint = 0;
    }

    if (pushState[biteButtonRow - 1][biteButtonCol - 1] == 0)
    {
      Joystick.setButton(Number + Reverse, (globalClock - toggleTimer[Row][Column] < PEC11Pulse));
      Joystick.setButton(Number + 1 - Reverse, (globalClock - toggleTimer[Row][Column + 1] < PEC11Pulse));
    }
}
