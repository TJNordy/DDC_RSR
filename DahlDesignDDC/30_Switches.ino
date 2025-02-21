  //--------------------------------------
  //---------SWITCHES START HERE----------
  //--------------------------------------
  if(!ADCfirst)
  {
  quickRotary1PulseBite(2,1,0,2323,4647,6975,9305,11621,13941,16258,18576,20905,23224,25540,true,6,1,1);
  multiFunction2Button24(3,1,7,4,4,true,0,2308,4619,6933,9248,11552,13858,16162,18372,20675,22970,25261);
  quickRotary2Pulse(5,2,0,2308,4623,6925,9226,11542,13844,16148,18451,20761,23071,25380,true,6,1,1);
  SW1PresetRotaryPulse(6,3,0,2316,4630,6945,9266,11582,13899,16212,18530,20843,23161,25480,true,0,1,1);
  }
  
  pushButton(1,1);
  pushButton(1,2);
  downshiftAndReverse(2,1,1,3,1);
  pushButton(1,4);
  modButton(1,5);
  pushButton(1,6);

  clutchCalibrate(2,2);
  firmwareUploadMode(2,3,2,7,5000);
  pushButton(2,3);
  pushButton(2,7); 
  quickSwitch(2,4);
  upshift(2,5,150);
  presetButton(2,6);
  pushButton(2,8); //this is the top right shifter function switch - may want to put modify later

  funkyHat(3,4,3,2,5,1);
  funkyPushBite(3,6,4,3,2,5);
  funkyRotary(3,7,8,false);

  pushButton(4,1);
  pushButton(4,3);
  pushButton(4,5);
  pushButton(4,6);
  pushButton(4,7);
  pushButton(4,8);

  funkyBrightness(5,1,2,false);
  funkyRotary(5,3,4,false);
  funkyRotary(5,5,6,false);
  funkyRotary(5,7,8,false);

  dualClutchCal(1,4,false);

  //--------------------------------------
  //---------SWITCHES END HERE------------
  //--------------------------------------

	Joystick.setZAxis(rotaryField - 32767);
	Joystick.setYAxis(buttonField - 32767);

	Joystick.sendState();

} //LOOP ENDS HERE

#if (BOARDTYPE == 2)
  void loop()
  {
	#if (LED1COUNT + LED2COUNT + LED3COUNT + LED4COUNT > 0)
		processCommands();
	#endif
  #if(USING_CB1 == 1 || ENABLE_OVERSAMPLING == 1)
    CB1Oversampling();
  #endif
  }
#endif
