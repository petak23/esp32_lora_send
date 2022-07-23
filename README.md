# Projekt esp32-lora-send

Pokusná komunikácia cez rozhranie LoRa pomocou esp32, komunikačný modul SX1276 Lora 868MHz RFM95W.

## Špecifikácia

Cez rozhranie LoRa je posielaná informácia o teplote, vlhkosti a tlaku každých 60s(alebo iný nastavený čas).
Použitý senzor BME280.

## Odkazy na použité knižnice

- **LoRa**: [https://github.com/sandeepmistry/arduino-LoRa](https://github.com/sandeepmistry/arduino-LoRa)
- **Adafruit_BME280_Library**: [https://github.com/adafruit/Adafruit_BME280_Library](https://github.com/adafruit/Adafruit_BME280_Library)
- **Tasker**: [https://github.com/joysfera/arduino-tasker](https://github.com/joysfera/arduino-tasker)

## Zdroje

- [ESP32 with LoRa using Arduino IDE – Getting Started](https://randomnerdtutorials.com/esp32-lora-rfm95-transceiver-arduino-ide/)
- [Prepočet atmosférického tlaku na hladinu mora](http://deadawp.blog.sector.sk/blogclanok/13131/prepocet-atmosferickeho-tlaku-na-hladinu-mora.htm)
