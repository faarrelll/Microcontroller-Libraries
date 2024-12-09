/***************************************************
 DFRobot Gravity: Analog TDS Sensor/Meter
 <https://www.dfrobot.com/wiki/index.php/Gravity:_Analog_TDS_Sensor_/_Meter_For_Arduino_SKU:_SEN0244>
 
 ***************************************************
 This sample code shows how to read the tds value and calibrate it with the standard buffer solution.
 707ppm(1413us/cm)@25^c standard buffer solution is recommended.
 
 Created 2018-1-3
 By Jason <jason.ling@dfrobot.com@dfrobot.com>
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution.
 ****************************************************/
 
 /***********Notice and Trouble shooting***************
 1. This code is tested on Arduino Uno with Arduino IDE 1.0.5 r2 and 1.8.2.
 2. Calibration CMD:
     enter -> enter the calibration mode
     cal:tds value -> calibrate with the known tds value(25^c). e.g.cal:707
     exit -> save the parameters and exit the calibration mode
 ****************************************************/

#include <EEPROM.h>
#include "CustomGravityTDS.h"

CustomGravityTDS gravityTds;

float temperature = 25,tdsValue = 0;
float volt = 0.9; //your variable voltage of sensor
float kValue = 1.0;

void setup()
{
    Serial.begin(115200);
    gravityTds.setModeCalibrate(false); //set false to disable calibrate by serial
    gravityTds.setKvalue(kValue);
    gravityTds.begin(false);  //initialization, set false to disable use adc
}

void loop()
{
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update(volt);  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    delay(1000);
}
