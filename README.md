# ESP32-RTOS-SATELLITE
The software is in still development stage. Implemenatation will based on WiFi

-> The sensors should connected with SPI or seperated I2C bases. Because when the first sensor try to reads a info from I2C context switch can be happen at this time and other sensors could request some information from I2C.
At this point, unwanted circumstance will occur.

-> Communucation will be asynchronous, so that in every time user can send a package, command or desired structure.

-> Descent Control algorithm will implemented in seperated task so, according to altitude sensor we will control simultaneously our motor speed as we desired.

-> Sensors data and (included SATELLITE status , altitude , GPS , IMU datas etc.) will be sended in 1Hz.

The purpose of the system is being perfect in SATELLITE category.

