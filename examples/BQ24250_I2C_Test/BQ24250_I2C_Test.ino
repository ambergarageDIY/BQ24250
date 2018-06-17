#include <BQ24250.h>
#include <Wire.h>

int addrBQ24250 = 106;//0x6A I2C Address
BQ24250 BQ24250obj;


void setup() {
  
  while(!Serial);//setup Serial port for arduino M0
  SerialUSB.begin(115200);

  BQ24250obj.begin(addrBQ24250);
  
  delay(3000);
}

void loop() {
  
  for(int i=0;i<=10;i++)//charge battery from 500mA to 1A with 50mA steps every 2 seconds
  {
    SerialUSB.print("Charging current set to ");
    int currentValue = 500 + i*50;
    SerialUSB.println(currentValue);
    BQ24250obj.enableCharging();
    BQ24250obj.setChargingCurrent(currentValue);
    delay(2000);
  }
}
