#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ILI9341.h" // Hardware-specific library

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.

#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Variable Deffinitions

int boostPin = A2;
int boostVal = 0;
float boostVolt = 0;
float boostKPa = 0;
float boostPSI = 0;
float atmBoostPSI = 0;
float atmBoostPSIPeak = 0;
float bmpTemp = 0;
float bmpPressure = 0;
bool debug_mode = false;

Adafruit_BMP280 bmp; // I2C interface for BMP280 --Also make sure the BMP280 Library is using the correct address 76 or 77


void setup() {

  Serial.begin(9600);
  Serial.println("Multigauge Start Up");

  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

   tft.begin();
   delay(250);
   tft.setRotation(1);
   tft.fillScreen(ILI9341_BLUE);
   tft.setCursor(30,30);
   tft.setTextColor(ILI9341_WHITE);
   tft.setTextSize(3);
   tft.print("Boost: ");
   tft.setCursor(30,60);
   tft.print("Peak: ");

}

void loop() {

// Gather Sensor Inputs

  bmpPressure = bmp.readPressure();
  bmpTemp = bmp.readTemperature();
  boostVal = analogRead(boostPin);
  boostVolt = boostVal * (5 / 1023.0);
  boostKPa = (boostVal*(.00488)/(.022)+20);
  boostPSI = (((boostVal/1023)+0.04)/0.004) * 0.145;

  atmBoostPSI = ((boostKPa * 1000) - bmpPressure) * .000145038 - .2; // Convert MPX4250AP Readings with Atomospheric Reading to bind Reletive BOOST
  tft.setCursor(150,30);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLUE);
  tft.print(atmBoostPSI);
  delay(33);
  tft.setTextColor(ILI9341_BLUE,ILI9341_BLUE);
  tft.print(atmBoostPSI);


  if (atmBoostPSI > atmBoostPSIPeak ) {
    atmBoostPSIPeak = atmBoostPSI;
    tft.setCursor(150,60);
    tft.setTextColor(ILI9341_BLUE,ILI9341_BLUE);
    tft.print(atmBoostPSIPeak);
    tft.setCursor(150,60);
    tft.setTextColor(ILI9341_WHITE,ILI9341_BLUE);
    tft.print(atmBoostPSIPeak);

}

// If Debug Mode is enabled text will be output to screen
if ( debug_mode == true) {
  Serial.println("@@@@@@@@@@@@@@@@@@@@@@@@@@");
  Serial.println("@@@@@@@@@@@@@@@@@@@@@@@@@@");
  Serial.println("Start of Boost Pressure Reading Output");
  Serial.println("Boost Analog Value");
  Serial.println(boostVal);
  Serial.println("Boost Voltage");
  Serial.println(boostVolt);
  Serial.println("Boost KPa");
  Serial.println(boostKPa);
  Serial.println("Boost PSI");
  Serial.println(boostPSI);
  Serial.println("**************************");
  Serial.println("**************************");
  Serial.println("BMP INFO START");
  Serial.println("BMP Temperature ");
  Serial.println(bmpTemp);
  Serial.println("BMP Pressure ");
  Serial.println(bmpPressure);
  Serial.println("**************************");
  Serial.println("**************************");
  Serial.println("Estimated BOOST in PSI");
  Serial.println(atmBoostPSI,1);

}


}
