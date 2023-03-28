void shiftRegisterScan()
{
    if (SRCOUNT == 0)
    {
        return;
    }
    //SR1
    if (SRCOUNT >= 1)
    {
        digitalWrite(SR1LATCH, 0); //Enable parallel inputs
        digitalWrite(SR1CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR1CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR1LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR1CHAIN; i++)
        {
            uint8_t rowNumber = i / 8; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR1DATA); //Set the bit to rawState
            digitalWrite(SR1CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR1CLOCK, 1); //Clock high to get new bit to SR1DATA
        }
    }

    if (SRCOUNT >= 2)
    {
        digitalWrite(SR2LATCH, 0); //Enable parallel inputs
        digitalWrite(SR2CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR2CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR2LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR2CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR2DATA); //Set the bit to rawState
            digitalWrite(SR2CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR2CLOCK, 1); //Clock high to get new bit to SR2DATA
        }
    }

    if (SRCOUNT >= 3)
    {
        digitalWrite(SR3LATCH, 0); //Enable parallel inputs
        digitalWrite(SR3CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR3CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR3LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR3CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN + SR2CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR3DATA); //Set the bit to rawState
            digitalWrite(SR3CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR3CLOCK, 1); //Clock high to get new bit to SR3DATA
        }
    }

    if (SRCOUNT >= 4)
    {
        digitalWrite(SR4LATCH, 0); //Enable parallel inputs
        digitalWrite(SR4CLOCK, 0); //Clock low to get ready to load data
        digitalWrite(SR4CLOCK, 1); //Clock high to load data to shift register
        digitalWrite(SR4LATCH, 1); //Disable parallel inputs and enable serial output

        //Scan through the serial output, set switch states a matrix with 8 columns and up to 4 rows. 
        for (uint8_t i = 0; i < 8 * SR4CHAIN; i++)
        {
            uint8_t rowNumber = i / 8 + SR1CHAIN + SR2CHAIN + SR3CHAIN; //Identify which row we're on
            uint8_t colNumber = 7 - (i % 8); //Identify which column we're on
            rawState[rowNumber][colNumber] = !digitalRead(SR4DATA); //Set the bit to rawState
            digitalWrite(SR4CLOCK, 0); //Clock low to ready for new bit
            digitalWrite(SR4CLOCK, 1); //Clock high to get new bit to SR4DATA
        }
    }
}

void PCA9555Run(int address, int interruptPin, int row, bool firstReversed, bool secondReversed)
{
  if (digitalRead(interruptPin) == 0)
  {
    Wire.beginTransmission(address);
    Wire.write(0x01);
    Wire.endTransmission();
    
    Wire.requestFrom(address,2);
    int firstByte = Wire.read();
    int lastByte = Wire.read();
    
    for ( int i = 0; i < 8; i++)
    {
      uint8_t col1 = i;
      uint8_t col2 = i;

      if (secondReversed)
      {
        col1 = 7-col1;
      }
      if (firstReversed)
      {
        col2 = 7-col2;
      }
      rawState[row][col1] = !bitRead(firstByte,i);
      rawState[row-1][col2] = !bitRead(lastByte, i);
    }
  }
}

void PCA9555Run1(int address, int interruptPin, int row, bool firstReversed, bool secondReversed)
{
  if (digitalRead(interruptPin) == 0)
  {
    Wire1.beginTransmission(address);
    Wire1.write(0x01);
    Wire1.endTransmission();
    
    Wire1.requestFrom(address,2);
    int firstByte = Wire1.read();
    int lastByte = Wire1.read();
    
    for ( int i = 0; i < 8; i++)
    {
      rawState[row][(7*secondReversed)-i] = !bitRead(firstByte,i);
      rawState[row-1][(7*firstReversed)-i] = !bitRead(lastByte, i);
    }
  }
}

void ADS1115Run(int address,int chipNumber, int channelCount, int rate)
{
  uint8_t Chip = chipNumber - 1;
  
  if (!ADS1115sentReq[Chip])
  {
    Wire1.beginTransmission(address);
    Wire1.write(0b00000001);
    Wire1.write(0b11000011 | (ADS1115channelCounter[Chip] << 4));
    Wire1.write(0b00000011 | (rate << 5));
    Wire1.endTransmission();
    
    Wire1.beginTransmission(address);
    Wire1.write(0b00000001);
    Wire1.endTransmission();

    ADS1115sentReq[Chip] = true;
  }

  if (ADS1115sentReq[Chip])
  {
    Wire1.requestFrom(address, 2);
    int convStatus = (Wire1.read()>>7);
    if (convStatus == 1)
    {
      Wire1.beginTransmission(address);
      Wire1.write(0b00000000);
      Wire1.endTransmission();

      uint8_t valAddress = (4*Chip)+ADS1115channelCounter[Chip];
      
      Wire1.requestFrom(address, 2);
      ADS1115value[valAddress]= Wire1.read()<<8;
      ADS1115value[valAddress] |= Wire1.read();
      ADS1115sentReq[Chip] = false;

      ADS1115channelCounter[Chip] ++;

      if (ADS1115channelCounter[Chip] >= channelCount)
      {
        ADS1115channelCounter[Chip] = 0;
      }
      
    }
  }
}
