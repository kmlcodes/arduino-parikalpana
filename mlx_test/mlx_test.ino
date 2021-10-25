
//----include necessary libraries--------
//IR sensor library
#include <Adafruit_MLX90614.h>

//I2C library
#include <Wire.h>

Adafruit_MLX90614 ir_sensor = Adafruit_MLX90614();             // initialize ir sensor object
//-----------------------------------------

//setup
void setup()
{
  ir_sensor.begin();                              
  Serial.begin(9600);
}

//code that run in loop
void loop()
{
  Serial.print("Obect temp:");
  Serial.println(ir_sensor.readObjectTempF());

  Serial.print("Ambient temp:");
  Serial.println(ir_sensor.readAmbientTempF());
  delay(1000);
}
