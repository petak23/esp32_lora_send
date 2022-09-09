// ++++++ túto časť sa dá zmazať +++++++
// Vzorový súbor a popis nastavení
// Pre reálnu aplikáciu je potrebné premenovať na: deffinitions.h
// ------ túto časť sa dá zmazať ------

/** Nastavenia a ich popis
 *
 * Posledná zmena(Last change): 09.09.2022
 *
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2022 - 2022 Ing. Peter VOJTECH ml.
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.1
 */

/** Nastavenie a definície senzorov */
#define DHTTYPE DHT22 // Definovanie typov pripojených senzorov
#define DHTPIN 4      // Pin, na ktorý je pripojený senzor
// ... alebo ...
#define BME280_ADD 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

/** Ostaté Nastavenia */
#define PUBLISH_TIME 1            // Perioda publikácie nameraných dát. v minútach
#define SERIAL_PORT_ENABLED false // Povolenie výstupu na sériový port - logovanie

/** Definície pinov pre vysielací modul */
#define LORA_SS 5
#define LORA_RESET 14
#define LORA_DIO0 2
// your location's frequency: 433E6 for Asia; 866E6 for Europe; 915E6 for North America
#define LORA_FREQ 866E6
// The sync word assures you don't get LoRa messages from other LoRa transceivers
// ranges from 0-0xFF
#define LORA_SYNC_WORD 0xFF

/** Parametre pre šifrovanie komunikácie */
#define DEVICE_ID "134679"                             // Dočasné nastavenie, kým sa nevyrieši prenos kľúčov...
#define PASS_PHRASE "Supersilne_heSLo_pre_zakodovanie" // Hlavné heslo pre šifrovanie komunikácie