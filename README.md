# Projekt esp32-lora-send

Pokusná komunikácia cez rozhranie LoRa pomocou esp32 a komunikačný modul SX1276 Lora 868MHz RFM95W.

## Špecifikácia

Cez rozhranie LoRa je posielaná informácia o teplote, vlhkosti a tlaku každých 60s(alebo iný nastavený čas).
Použitý senzor BME280. Komunikácia je šifrovaná pomocou šifry AES-CBC-256.

## Odkazy na použité knižnice

- **LoRa**: (https://github.com/sandeepmistry/arduino-LoRa)
- **Adafruit_BME280_Library**: (https://github.com/adafruit/Adafruit_BME280_Library)
- **Tasker**: (https://github.com/joysfera/arduino-tasker)
- **Tiny AES in C**: (https://github.com/kokke/tiny-AES-c)
- **CRC32**: (https://github.com/bakercp/CRC32)
- **kmackay/micro-ecc**: (https://github.com/kmackay/micro-ecc)

### Knižnice mimo platformio

- **ESP8266-Arduino-cryptolibs**: (https://github.com/CSSHL/ESP8266-Arduino-cryptolibs)
- **SHA256**: (https://github.com/CSSHL/ESP8266-Arduino-cryptolibs)

## Zdroje

- [ESP32 with LoRa using Arduino IDE – Getting Started](https://randomnerdtutorials.com/esp32-lora-rfm95-transceiver-arduino-ide/)
- [Prepočet atmosférického tlaku na hladinu mora](http://deadawp.blog.sector.sk/blogclanok/13131/prepocet-atmosferickeho-tlaku-na-hladinu-mora.htm)
- [RatatoskrIoT: IoT aplikace na ESP32/ESP8266 a serverová aplikace k tomu](https://github.com/petrbrouzda/RatatoskrIoT)

## Súčiastky

- [Vývojová doska NODE MCU ESP32 WiFi + Bluetooth](https://techfun.sk/produkt/vyvojova-doska-node-mcu-esp32-wifi-bluetooth)
- [Komunikačný modul SX1276 Lora 433 / 868 / 915 MHz - variant: 868MHz RFM95W](https://techfun.sk/produkt/komunikacny-modul-sx1276-lora-433-868-915-mhz/?attribute_pa_variant=868mhz-rfm95w)
