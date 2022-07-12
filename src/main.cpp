#include <Arduino.h>
#include "Tasker.h"
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include "definitions.h"

/**
 * Program pre LoRa komunikáciu pomocou ESP32 - vysielač
 *
 * Posledná zmena(last change): 12.07.2022
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2022 - 2022 Ing. Peter VOJTECH ml.
 * @license
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.0
 */

float humidity = 0;
float temperature = 0;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// Inicialize Tasker
Tasker tasker;

void readDHT()
{
  // Nacitaj udaje z DHT
  humidity = dht.readHumidity();       // Načítanie vlhkosti
  temperature = dht.readTemperature(); // Načítanie teploty v °C

  if (isnan(humidity) || isnan(temperature))
  { // Kontrola načítania dát zo senzora
    Serial.println("Chyba načítania údajov z DHT senzora.");
    return;
  }
}

void taskReadDHT()
{
  readDHT();

  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("T:");
  LoRa.print(temperature);
  LoRa.print(";H:");
  LoRa.print(humidity);
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

  while (!LoRa.begin(LORA_FREQ))
  {
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(LORA_SYNC_WORD);
  Serial.println("LoRa Initializing OK!");

  // Publikovanie nových hodnôt od teraz každých PUBLISH_TIME min.
  tasker.setInterval(taskReadDHT, (PUBLISH_TIME * 1000));
}

void loop()
{
  tasker.loop();
}