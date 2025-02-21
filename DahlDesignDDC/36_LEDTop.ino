void LEDTop()
{
#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
  if(LEDCounter == 0 || ecoTrig)
  {
    #if (ECOLED == 0)
    SimHubImport(); 
    #endif
//----------------------------------------------------------------------------
// ------------------------ LED CALLS START HERE------------------------------
//----------------------------------------------------------------------------

//Quickswitch notification
triggerLED(0,2,buttonFieldBit(9),0xFF00FF,25,false,true,500,1000);
triggerLED(13,15,buttonFieldBit(9),0xFF00FF,25,false,true,500,1000);
//preset show when button pressed
triggerLED(3,3,buttonPressed(2,6) && presetSearch(1), 0xFF0000,15,false,false);
triggerLED(4,4,buttonPressed(2,6) && presetSearch(2), 0xFF0000,15,false,false);
triggerLED(5,5,buttonPressed(2,6) && presetSearch(3), 0xFF0000,15,false,false);
triggerLED(6,6,buttonPressed(2,6) && presetSearch(4), 0xFF0000,15,false,false);
triggerLED(7,7,buttonPressed(2,6) && presetSearch(5), 0xFF0000,15,false,false);
triggerLED(8,8,buttonPressed(2,6) && presetSearch(6), 0xFF0000,15,false,false);
triggerLED(9,9,buttonPressed(2,6) && presetSearch(7), 0xFF0000,15,false,false);
triggerLED(10,10,buttonPressed(2,6) && presetSearch(8), 0xFF0000,15,false,false);
triggerLED(11,11,buttonPressed(2,6) && presetSearch(9), 0xFF0000,15,false,false);
triggerLED(12,12,buttonPressed(2,6) && presetSearch(10), 0xFF0000,15,false,false);
triggerLED(13,13,buttonPressed(2,6) && presetSearch(11), 0xFF0000,15,false,false);
triggerLED(14,14,buttonPressed(2,6) && presetSearch(12), 0xFF0000,15,false,false);

biteLED(0,2,15,3,15); 

//----------------------------------------
//---------PRESET SPECIFIC CALLS----------
//----------------------------------------




//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------

  }

  if (ecoTrig)
  {
    ecoTrig = false;
  }
#endif
  
  #if(LED1COUNT > 0 && !strip1Block)
    if(LEDCounter == 1)
    {
      LED1.show();
    }
  #endif
  #if(LED2COUNT > 0)
    if(LEDCounter == 2)
    {
      LED2.show();
    }
  #endif
  #if(LED3COUNT > 0)
    if(LEDCounter == 3)
    {
      LED3.show();
    }
  #endif
  #if(LED4COUNT > 0)
    if(LEDCounter == 4)
    {
      LED4.show();
    }
  #endif
}
