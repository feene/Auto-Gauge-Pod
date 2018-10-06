#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

int boostPin = A2;
int boostVal = 0;
float boostVolt = 0;
float boostKPa = 0;
float boostPSI = 0;
float atmBoostPSI = 0;

float bmpTemp = 0;
float bmpPressure = 0;


bool debug_mode = true;

Adafruit_BMP280 bmp; // I2C


void setup() {

  Serial.begin(9600);
  Serial.println("Multigauge Start Up");

  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop() {

// Gather Sensor Inputs

  bmpPressure = bmp.readPressure();
  bmpTemp = bmp.readTemperature();
  boostVal = analogRead(boostPin);
  boostVolt = boostVal * (5 / 1023.0);
  boostKPa = (boostVal*(.00488)/(.022)+20);
  boostPSI = (((boostVal/1023)+0.04)/0.004) * 0.145;

  atmBoostPSI = ((boostKPa * 1000) - bmpPressure) * .000145038; // Convert MPX4250AP Readings with Atomospheric Reading to bind Reletive BOOST

// If Debug Mode is enabled text will be output to screen
if ( debug_mode == true) {
  Serial.println("**************************");
  Serial.println("**************************");
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
  delay(500);

}
