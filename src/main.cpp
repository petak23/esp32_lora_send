#include <Arduino.h>
#include "Tasker.h"
#include <SPI.h>
#include <LoRa.h>

#include <Adafruit_BME280.h>

#include "definitions.h"

/**
 * Program pre LoRa komunikáciu pomocou ESP32 - vysielač
 *
 * Posledná zmena(last change): 12.07.2022
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2022 - 2022 Ing. Peter VOJTECH ml.
 * @license
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.1
 */

Adafruit_BME280 bm; // use I2C interface
Adafruit_Sensor *bm_temp = bm.getTemperatureSensor();
Adafruit_Sensor *bm_pressure = bm.getPressureSensor();
Adafruit_Sensor *bm_humidity = bm.getHumiditySensor();

sensors_event_t temp_event, pressure_event, humidity_event;

// Inicialize Tasker
Tasker tasker;

void readSensor()
{
  bm_temp->getEvent(&temp_event);
  bm_pressure->getEvent(&pressure_event);
  bm_humidity->getEvent(&humidity_event);

  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Humidity = "));
  Serial.print(humidity_event.relative_humidity);
  Serial.println(" %");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.println();
}

void taskReadSensor()
{
  readSensor();

  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("T:");
  LoRa.print(temp_event.temperature);
  LoRa.print("H:");
  LoRa.print(humidity_event.relative_humidity);
  LoRa.print(";P:");
  LoRa.print(pressure_event.pressure);
  LoRa.endPacket();
}

void setup()
{
  // initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("LoRa Sender");

  // setup LoRa transceiver module
  LoRa.setPins(LORA_SS, LORA_RESET, LORA_DIO0);

  while (!LoRa.begin(866E6))
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  LoRa.setSyncWord(LORA_SYNC_WORD);
  Serial.println("LoRa Initializing OK!");

  if (!bm.begin(0x76))
  {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bm.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a bm 280.\n");
    Serial.print("        ID of 0x61 represents a bm 680.\n");
    while (1)
      delay(10);
  }

  bm_temp->printSensorDetails();
  bm_pressure->printSensorDetails();
  bm_humidity->printSensorDetails();

  tasker.setTimeout(readSensor, 2000); // Čakanie na senzor;

  // Publikovanie nových hodnôt od teraz každých PUBLISH_TIME sec.
  tasker.setInterval(taskReadSensor, (PUBLISH_TIME * 1000));
}

void loop()
{
  tasker.loop();
}

/*
#include <Wire.h> //include Wire.h library

void setup()
{
  Wire.begin();         // Wire communication begin
  Serial.begin(115200); // The baudrate of Serial monitor is set in 9600
  while (!Serial)
    ; // Waiting for Serial Monitor
  Serial.println("\nI2C address Scanner CircuitSchools.com");
}

void loop()
{
  byte error, address; // variable for error and I2C address
  int devicecount;

  Serial.println("Scanning...");

  devicecount = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      devicecount++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (devicecount == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // wait 5 seconds for the next I2C scan
}*/