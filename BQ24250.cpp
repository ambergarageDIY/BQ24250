#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#include "BQ24250.h"

/** init Si7006A20_AG class
     * @param *i2c pointer to I2C serial interface
     * @param addr sensor I2C address
     */
BQ24250::BQ24250(){
}

boolean BQ24250::begin(int addr)
{
	Wire.begin();
	_addr = addr;
	return true;
}

void BQ24250::enableCharging()
{
    char toWrite0x01[2] = {0x01,0x6C};//default state plus 0 on bit 1 to enable charging
	
	Wire.beginTransmission(_addr);
    Wire.write(toWrite0x01,2);
    Wire.endTransmission();

}

void BQ24250::disableCharging()
{
    char toWrite0x01[2] = {0x01,0x6E};//default state plus 1 on bit 1 to disable charging

	Wire.beginTransmission(_addr);
    Wire.write(toWrite0x01,2);
    Wire.endTransmission();
}

bool BQ24250::getCEStatus()
{
    char cmd = 0x04;
    char buffRead0x04;
    
	Wire.beginTransmission(_addr); //transmit to device #44 (0x2c)
	Wire.write(cmd);
	Wire.endTransmission(); 
	
	delay(20);
	
    Wire.requestFrom(_addr, 1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x04 = Wire.read();    // receive a byte as character
	}

	
    char ceState = (buffRead0x04 & 0x08);//isolate bit1
    
    
    if(ceState == 8)//control bit1 of register #2
    {
        return true;//disable charging  
    } 
    else//control bit1 of register #2
    {
        return false;//enable charging
    }
    
}

void BQ24250::setChargingCurrent(int currentValue)
{
    if(getCEStatus() == false && currentValue >= 500 && currentValue <= 2000)// if charger is active yet, and current is set between 500 e 2000 mA
    {
        char currentBitSetup = char((currentValue - 500)/50) << 3;//default 500 + number from 0 to 1500, this number is convert to correct register value
        
        //char buffRead0x01 = 0;//content of the I2C read operation of 0x01 register
        //char buffRead0x03 = 0;//content of the I2C read operation of 0x03 register
        
        char toWrite0x01[2] = {0x01,0x5C};//Register#2 write 0x5C , 0b01011100
        //char toWrite2[2] = {0x04,0x42};
        char toWrite0x03[2] = {0x03,currentBitSetup};
        		
		Wire.beginTransmission(_addr);
		Wire.write(toWrite0x01,2);
		Wire.endTransmission();
        //i2c_1.read(addrBQ24250,&buffRead0x01,1);
        
        /*dbgUart.printf("Register #1: ");
        sprintf(temp, "%d",buffRead0x01);
        dbgUart.printf(temp);
        dbgUart.printf("\r\n");*/
		
		Wire.beginTransmission(_addr);
        Wire.write(toWrite0x03,2);
        Wire.endTransmission();
        //i2c_1.read(addrBQ24250,&buffRead0x03,1);
        
        /*dbgUart.printf("Register #4: ");
        sprintf(temp, "%d",buffRead0x03);
        dbgUart.printf(temp);
        dbgUart.printf("\r\n");*/
    }
}

void BQ24250::setMaxChargeVoltage(float maxChargeVoltage)
{
    //char buffRead0x02 = 0;//content of the I2C read operation of 0x02 register
    if(maxChargeVoltage >= 3.5 && maxChargeVoltage <= 4.44)// if charger is active yet, and current is set between 500 e 2000 mA
    {
        char currentBitSetup = char((maxChargeVoltage - 3.5)/0.02) << 2;
        currentBitSetup = currentBitSetup | 0b00000111;
        
        char toWrite0x02[2] = {0x02,currentBitSetup};//max xharge at 4.44V
		
		Wire.beginTransmission(_addr);
        Wire.write(toWrite0x02,2);
        Wire.endTransmission();
    //i2c_1.read(addrBQ24250,&buffRead0x02,1);
    
    /*dbgUart.printf("Register #2: ");
    sprintf(temp, "%d",buffRead0x02);
    dbgUart.printf(temp);
    dbgUart.printf("\r\n");*/
    }
}

char BQ24250::readStat()
{
    char buffRead0x00;//content of the I2C read operation of 0x00 register
    char cmd = 0x00;
	
	Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x00 = Wire.read();    // receive a byte as character
	}
	
    buffRead0x00 = (buffRead0x00 & 0x30) >> 4;
    
    return buffRead0x00;
}
    
void BQ24250::setRegister1(char reg)
{
    char toWrite0x00[2] = {0x00,reg};
	
	Wire.beginTransmission(_addr);
    Wire.write(toWrite0x00,2);
    Wire.endTransmission();
}
    
void BQ24250::setRegister2(char reg)
{
    char toWrite0x01[2] = {0x01,reg};
    
    Wire.beginTransmission(_addr);
    Wire.write(toWrite0x01,2);
    Wire.endTransmission();
}
    
void BQ24250::setRegister3(char reg)
{
    char toWrite0x02[2] = {0x02,reg};
    
    Wire.beginTransmission(_addr);
    Wire.write(toWrite0x02,2);
    Wire.endTransmission();
}
    
void BQ24250::setRegister4(char reg)
{
    char toWrite0x03[2] = {0x03,reg};
    
    Wire.beginTransmission(_addr);
    Wire.write(toWrite0x03,2);
    Wire.endTransmission();
}
    
void BQ24250::setRegister5(char reg)
{
    char toWrite0x04[2] = {0x04,reg};
    
    Wire.beginTransmission(_addr);
    Wire.write(toWrite0x04,2);
    Wire.endTransmission();
}
    
void BQ24250::setRegister6(char reg)
{
    char toWrite0x05[2] = {0x05,reg};
    
    Wire.beginTransmission(_addr);
    Wire.write(toWrite0x05,2);
    Wire.endTransmission();
}
    
void BQ24250::setRegister7(char reg)
{
    char toWrite0x06[2] = {0x06,reg};
    
    Wire.beginTransmission(_addr);
    Wire.write(toWrite0x06,2);
    Wire.endTransmission();
}
    
    
char BQ24250::readRegister1()
{
    char buffRead0x00 = 0;//content of the I2C read operation of 0x00 register
    char cmd = 0x00;
	
	Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    //wait_ms(20);
	
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x00 = Wire.read();    // receive a byte as character
	}
    
    return buffRead0x00;
    
}
    
char BQ24250::readRegister2()
{
    char buffRead0x01 = 0;//content of the I2C read operation of 0x00 register
    char cmd = 0x01;
    
    Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    //wait_ms(20);
	
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x01 = Wire.read();    // receive a byte as character
	}
    
    return buffRead0x01;
}
    
char BQ24250::readRegister3()
{
    char buffRead0x02 = 0;//content of the I2C read operation of 0x00 register
    char cmd = 0x02;
    
    Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    //wait_ms(20);
	
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x02 = Wire.read();    // receive a byte as character
	}
	
	return buffRead0x02;
}
    
char BQ24250::readRegister4()
{
    char buffRead0x03 = 0;//content of the I2C read operation of 0x00 register
    char cmd = 0x03;
    
    Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    //wait_ms(20);
	
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x03 = Wire.read();    // receive a byte as character
	}
    
    return buffRead0x03;
}
    
char BQ24250::readRegister5()
{
    char buffRead0x04 = 0;//content of the I2C read operation of 0x00 register
    char cmd = 0x04;
    
    Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    //wait_ms(20);
	
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x04 = Wire.read();    // receive a byte as character
	}
    
    return buffRead0x04; 
}
    
char BQ24250::readRegister6()
{
    char buffRead0x05 = 0;//content of the I2C read operation of 0x00 register
    char cmd = 0x05;
    
    Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    //wait_ms(20);
	
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x05 = Wire.read();    // receive a byte as character
	}
    
    return buffRead0x05;
}
    
char BQ24250::readRegister7()
{
    char buffRead0x06 = 0;//content of the I2C read operation of 0x00 register
    char cmd = 0x06;
    
    Wire.beginTransmission(_addr);
    Wire.write(cmd);
    Wire.endTransmission();
    //wait_ms(20);
	
	Wire.requestFrom(_addr,1);
    while(Wire.available())    // slave may send less than requested
	{ 
		buffRead0x06 = Wire.read();    // receive a byte as character
	}
    
    return buffRead0x06;
}
    
