#if (USING_CB1 == 1)

//---------------------------------------
//--------TABLE DESCRIPTION--------------
//---------------------------------------

const uint8_t rowCount = 8;
const uint8_t colCount = 8;

uint8_t buttonNumber[rowCount][colCount] =
{
  
  { 15, 5, 6, 7, 8, 9, 0, 0 },             //ROW 1, COLUMN 1-8

  { 1, 21, 27, 17, 2, 24, 30, 18 },       //ROW 2, COLUMN 1-8

  { 0, 0, 0, 0, 0, 0, 3, 0 },     //ROW 3, COLUMN 1-8

  { 16, 0, 10, 0, 11, 14, 12, 13 },     //ROW 4, COLUMN 1-8

  { 19, 0, 25, 0, 28, 0, 22, 0 },     //ROW 5, COLUMN 1-8

  { 0, 0, 0, 0, 0, 0, 0, 0 },     //ROW 6, COLUMN 1-8

  { 0, 0, 0, 0, 0, 0, 0, 0 },     //ROW 7, COLUMN 1-8

  { 0, 0, 0, 0, 0, 0, 0, 0 }      //ROW 8, COLUMN 1-8  
  
};


//---------------------------------------
//--------ANALOG DESCRIPTION-------------
//---------------------------------------

#define analogChannelCount 12

uint8_t analogPins[analogChannelCount] =              
{ ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7, ADC8, ADC9, ADC10, ADC11, ADC12 };

uint8_t analogButtonNumber[analogChannelCount] =         //ANALOG BUTTONS 1
{ 0, 55, 31, 0, 69, 83, 0, 0, 0, 0, 0, 0 };

uint8_t analogButtonNumberIncMode[analogChannelCount] =  //ANALOG BUTTONS 2
{ 0, 67, 0, 0, 81, 95, 0, 0, 0, 0, 0, 0 };


//---------------------------------------
//------------DIRECT OUTPUTS-------------
//---------------------------------------

#define enableOutput 0
uint8_t outputPins[] = { 99};
const uint8_t outputPinsCount = sizeof(outputPins) / sizeof(outputPins[0]);


//PINS FOR PULLUP
int row5Pins [8] = {19,17,20,18,21,22,24,23};
int row6Pins [8] = {12,13,10,11,9,3,1,2};


//ADC
bool sentReq1 = false;
bool sentReq2 = false;
int channelCount1 = 0;
int channelCount2 = 0;

#endif
