void LEDStartup()
{
#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
//----------------------------------------------------------------------------
// ------------------------ LED CALLS START HERE------------------------------
//----------------------------------------------------------------------------
  

//----------------------------------------------------------------------------
// ------------------------ LED CALLS END HERE--------------------------------
//----------------------------------------------------------------------------
#endif

  #if(LED1COUNT > 0)
    LED1.show();
  #endif
  #if(LED2COUNT > 0)
    LED2.show();
  #endif
  #if(LED3COUNT > 0)
    LED3.show();
  #endif
  #if(LED4COUNT > 0)
    LED4.show();
  #endif

}
