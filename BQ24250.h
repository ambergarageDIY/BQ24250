
#ifndef BQ24250_h
#define BQ24250_h
 
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define I2CADDR     0xD4

/** BQ24250_AG class 
 */
class BQ24250{
public:
    /** init BQ24250 class
     * @param *i2c pointer to I2C serial interface
     * @param addr sensor I2C address
     */
    BQ24250(); 

	boolean begin(int addr = I2CADDR);
	
    void enableCharging();
    
    void disableCharging();
    
    bool getCEStatus();
    
    void setChargingCurrent(int currentValue);
    
    void setMaxChargeVoltage(float maxChargeVoltage);
    
    char readStat();
    
    void setRegister1(char reg);
    
    void setRegister2(char reg);
    
    void setRegister3(char reg);
    
    void setRegister4(char reg);
    
    void setRegister5(char reg);
    
    void setRegister6(char reg);
    
    void setRegister7(char reg);
    
    
    char readRegister1();
    
    char readRegister2();
    
    char readRegister3();
    
    char readRegister4();
    
    char readRegister5();
    
    char readRegister6();
    
    char readRegister7();
    
    
protected:


private:
    int _addr;
    
};
    
#endif