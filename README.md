# M5Stack-TFmini-S

This sketch works with M5Stack basic model and the TFmini-S LiDAR module.
It takes the distance measurements and displays on the LCD sceen of the M5Stack.

By default, TFmini-S communicates using the serial interface.
In order to use Serial1 of M5Stack Basic model, GPIO2 and GPIO5 pins can be used as Tx and RX respectivelly. 

(Reference: http://shinshu-makers.net/shinshu_makers/2020/09/02/%E3%80%90l-rtk%E3%80%91m5stack_serial2%E6%8E%A5%E7%B6%9A%E3%81%A7%E6%89%8B%E9%96%93%E5%8F%96%E3%81%A3%E3%81%9F%EF%BC%9Cf9p_rtcm%E5%8F%97%E4%BF%A1%E7%A2%BA%E8%AA%8D%E6%96%B9%E6%B3%95%E3%81%8C%E4%B8%8D/)
This setting can be initialized by 
```Serial1.begin(115200, SERIAL_8N1, 5, 2);```
The pin arrangement between the sensor and the M5Stack is as follows. 

| TFmini-S | M5Stack |
| :---: | :---: |
| GND  | GND |
| 5V  | 5V |
| RXD/SDA | 2 |
| TXD/SCL  | 5 |
