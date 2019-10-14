/*
  SD card datalogger

  Adapted from "SD card datalogger" example sketch by Tom Igoe

  Author: Luke Smith, Augusto Dantas de Oliveira
  Class: AE199
  University of Illinois Urbana-Champaign

 */

#include <SPI.h> // Library for communicating with SPI devices a.k.a. the SD board
#include <SD.h>  // Library for easy writing/reading from SD card
#include <Adafruit_Sensor.h> // Adafruit unified sensor library https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_BMP280.h> // BMP280 sensor library https://github.com/adafruit/Adafruit_BMP280_Library
#include <Wire.h> // Library for communicating with I2C devices (I2C is a protocol for sending data over two wires between many devices)

const int chipSelect = 4; // define which pin the CS pin is connected to
Adafruit_BMP280 bmp; 
/*
 * Initializes a BMP280 object (Creates a data structure representing the sensor so the program can keep
 * track of important information about the sensor as well as establish an initial connection to, kind of
 * like saying hello to the BMP280 chip.
 */
unsigned long time;

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");
  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  }
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("New Recording");

    /********Change the Header to Reflect all the data you are logging!*********/
    String header = "Miliseconds";
    /***************************************************************************/
    
    dataFile.println(header);
    Serial.println(header);
    dataFile.close();
  }
}

void loop() {


  // make a string for assembling the data to log:
  
  String dataString = "";

  time = millis();

  // This adds the time to the data String to be recorded.
  dataString += String(time);
  // This adds a comma and a space to follow the measruement.
  dataString += ", ";

  // To Read the Temperature: bmp.readTemperature();
  // To Read the Pressure:    bmp.readPressure();

  /*****Your Code Here! Add the temperature and pressure to the datalog******/
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure();
  dataString += String(temp);
  dataString += ", ";
  dataString += String(pressure);
  datastring += ", ";
  
  float temp_based(float temp){
    float h = -154.0832*temp + 2317.411;
    return h;  
  }
  
  /**************************************************************************/


  /*****Calculate approximate altitude based on pressure or temperature*****/
  

  
  /*************************************************************************/
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
    delay(100);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

float altitude_temp(float temp){
float x = (-154.0832 * temp) + 2317.411
return x;
  
}

float altitude_pressure_EXP(float pressure) {
float y = 44405.24-44383.67*pow((pressure/101290),(1/5.265));
return y;
  
}

float altitude_pressure_LINEAR(float pressure) {
float z = (-0.087284 * pressure)+8863.6544
return z;

}



