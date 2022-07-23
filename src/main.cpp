#include <Arduino.h>
#include "Tasker.h"
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BME280.h>

#include "definitions.h"

/**
 * Program pre LoRa komunikáciu pomocou ESP32 - vysielač
 *
 * Posledná zmena(last change): 23.07.2022
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2022 - 2022 Ing. Peter VOJTECH ml.
 * @license
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.2
 */

Adafruit_BME280 bm; // use I2C interface

float temperature;  // Teplota
float humidity;     // Vlhkosť
float abs_pressure; // Absolútny tlak
float altitude;     // Nadmorská výška - nastavovaná v metóde setup
float rel_pressure; // Relatívny tlak prepočítaný na hladinu mora

// Inicialize Tasker
Tasker tasker;

void readSensor()
{
  // Načítaj hodnoty a spočítaj
  temperature = bm.readTemperature();
  abs_pressure = bm.readPressure() / 100;
  humidity = bm.readHumidity();
  rel_pressure = abs_pressure / pow(1.0 - altitude / 44330.0, 5.255);

#if SERIAL_PORT_ENABLED
  Serial.print("Teplota = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Vlhkosť = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Absolutny tlak = ");
  Serial.print(abs_pressure);
  Serial.println(" hPa");

  Serial.print("Relativny tlak = ");
  Serial.print(rel_pressure);
  Serial.println(" hPa");

  Serial.print("Nadmorska vyska = ");
  Serial.print(altitude);
  Serial.println(" m.n.m");

  Serial.println();
#endif
}

void taskReadSensor()
{
  readSensor();

  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("TE:");
  LoRa.print(temperature);
  LoRa.print(";HU:");
  LoRa.print(humidity);
  LoRa.print(";AP:");
  LoRa.print(abs_pressure);
  LoRa.print(";RP:");
  LoRa.print(rel_pressure);
  LoRa.print(";AL:");
  LoRa.print(altitude);
  LoRa.endPacket();
}

void setup()
{
#if SERIAL_PORT_ENABLED
  // initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("LoRa Sender");
#endif

  // setup LoRa transceiver module
  LoRa.setPins(LORA_SS, LORA_RESET, LORA_DIO0);

  while (!LoRa.begin(LORA_FREQ))
  {
#if SERIAL_PORT_ENABLED
    Serial.print(".");
#endif
    delay(500);
  }

  LoRa.setSyncWord(LORA_SYNC_WORD);
#if SERIAL_PORT_ENABLED
  Serial.println(" LoRa Initializing OK!");
#endif

  if (!bm.begin(BME280_ADD))
  {
#if SERIAL_PORT_ENABLED
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bm.sensorID(), 16);
    Serial.print("   ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("   ID of 0x60 represents a bm 280.\n");
    Serial.print("   ID of 0x61 represents a bm 680.\n");
#endif
    while (1)
      delay(10);
  }
#if SERIAL_PORT_ENABLED
  Serial.println("-- Weather Station Scenario --");
  Serial.println("forced mode, 1x temperature / 1x humidity / 1x pressure oversampling,");
  Serial.println("filter off");
#endif
  bm.setSampling(Adafruit_BME280::MODE_FORCED,
                 Adafruit_BME280::SAMPLING_X1, // temperature
                 Adafruit_BME280::SAMPLING_X1, // pressure
                 Adafruit_BME280::SAMPLING_X1, // humidity
                 Adafruit_BME280::FILTER_OFF);

  altitude = 784; // chata // bm.readAltitude(SEALEVELPRESSURE_HPA);

  tasker.setTimeout(readSensor, 2000); // Čakanie na senzor;

  // Publikovanie nových hodnôt od teraz každých PUBLISH_TIME sec.
  tasker.setInterval(taskReadSensor, (PUBLISH_TIME * 1000));
}

void loop()
{
  bm.takeForcedMeasurement();
  tasker.loop();
}