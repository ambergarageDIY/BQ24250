# BQ24250

This is a library for BQ24250 IC from Texas Instruments
It is for the breakout board that you can find at this link: 
https://www.tindie.com/products/ambergarage/bq24250-breakout-board-lipo-switching-charger/

With this library you can manage this feautures:

-Enable and disable charging

-get the CE pin status

-get the STAT pin status

-set the fast charging current, with this function you are able to set the fast charge current from 500 to 2000mA however a maximum of       1500mA chrging current is recommended

-set the maximum charge voltage of the battery, with this function you can set the maximum voltage that the battery could be reach during   charging (set this voltage to a typical 4.2V is recommended and it is the default state)

These are the main and “black box” functions but you can also set or get the status of all 7 registers of the BQ24250 with these functions:

setRegister1, setRegister2, setRegister3, setRegister4, setRegister5, setRegister6, setRegister7
setRegister1, setRegister2, setRegister3, setRegister4, setRegister5, setRegister6, setRegister7

With these last 14 functions you can control and monitoring the BQ24250 in all of its features.

Take a look to the .cpp and .h files to see all available functions!
Enjoy!
