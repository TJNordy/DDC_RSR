//------------------------------
//------BUTTON FUNCTIONS--------
//------------------------------

void pushButton(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    Joystick.setButton(Number, pushState[Row][Column]);
}

void pushButtonM(int8_t row, int8_t column, int8_t fieldPlacement)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];
    int8_t FieldPlacement = fieldPlacement;

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    //Change switch mode
    if (pushState[Row][Column] == 0)
    {
        switchModeLock[Row][Column] = false;
    }

    if (pushState[Row][Column] == 1 && pushState[modButtonRow - 1][modButtonCol - 1] == 1 && FieldPlacement != 0 && !switchModeLock[Row][Column])
    {
        switchModeLock[Row][Column] = true;
        switchMode[Row][Column] = !switchMode[Row][Column];
        latchLock[Row][Column] = false;
        latchState[Row][Column] = false;
    }

    //Push switch mode
    long push = 0;
    push = push | switchMode[Row][Column];
    push = push << (FieldPlacement - 1);
    buttonField = buttonField | push;

    //SWITCH MODE 1: MOMENTARY BUTTON
    if (!switchMode[Row][Column])
    {
        Joystick.setButton(Number, pushState[Row][Column]);
    }

    //SWITCH MODE 2: LATCHING BUTTON
    else if (switchMode[Row][Column])
    {
        if (pushState[Row][Column] == 0)
        {
            latchLock[Row][Column] = false;
        }

        if (pushState[Row][Column] == 1 && !latchLock[Row][Column])
        {
            latchLock[Row][Column] = true;
            latchState[Row][Column] = !latchState[Row][Column];
        }

        Joystick.setButton(Number, latchState[Row][Column]);
    }
}


void pushButtonL(int8_t row, int8_t column)
{
    int8_t Row = row - 1;
    int8_t Column = column - 1;
    int8_t Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        switchTimer[Row][Column] = globalClock;
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if (pushState[Row][Column] == 0)
    {
        latchLock[Row][Column] = false;
    }

    if (pushState[Row][Column] == 1 && !latchLock[Row][Column])
    {
        latchLock[Row][Column] = true;
        latchState[Row][Column] = !latchState[Row][Column];
    }

    Joystick.setButton(Number, latchState[Row][Column]);
}

void repeaterButton(int row, int column, unsigned long pulseDuration, int repeats)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > (pulseDuration + (2 * repeats * pulseDuration)))
    {
        if(rawState[Row][Column] == 1)
        {
          switchTimer[Row][Column] = globalClock;          
        }
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > (pulseDuration + (2 * repeats * pulseDuration)))
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) < (2 * repeats * pulseDuration))
    {
        if(globalClock % (2*pulseDuration) < pulseDuration)
        {
            Joystick.setButton(Number, 1);
        }
        else
        {
            Joystick.setButton(Number, 0);
        }
    }
    else
    {
        Joystick.setButton(Number, 0);
    }
}

void pulseButton(int row, int column)
{
    int Row = row - 1;
    int Column = column - 1;
    int Number = buttonNumber[Row][Column];

    if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        if(rawState[Row][Column] == 1)
        {
          switchTimer[Row][Column] = globalClock;          
        }
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
    {
        pushState[Row][Column] = rawState[Row][Column];
    }

    if ((globalClock - switchTimer[Row][Column]) < buttonCooldown)
    {
        toggleTimer[Row][Column] = globalClock;
    }

    if ((globalClock - toggleTimer[Row][Column]) < togglePulse)
    {
        Joystick.setButton(Number, 1);
    }
    else
    {
        Joystick.setButton(Number, 0);
    }
}

#if(ENABLE_MOUSE == 1)

void leftMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(pushState[Row][Column] == 1)
  {
    Mouse.press(1);
  }
  else
  {
    Mouse.release(1);
  }
}

void middleMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(pushState[Row][Column] == 1)
  {
    Mouse.press(4);
  }
  else
  {
    Mouse.release(4);
  }
}

void rightMouseButton(int row, int col)
{
  int8_t Row = row - 1;
  int8_t Column = col - 1;

  if (pushState[Row][Column] != rawState[Row][Column] && (globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      switchTimer[Row][Column] = globalClock;
      pushState[Row][Column] = rawState[Row][Column];
  }

  if ((globalClock - switchTimer[Row][Column]) > buttonCooldown)
  {
      pushState[Row][Column] = rawState[Row][Column];
  }  

  if(pushState[Row][Column] == 1)
  {
    Mouse.press(2);
  }
  else
  {
    Mouse.release(2);
  }
}

#endif
