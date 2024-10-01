/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Sandeep Mistry All right reserved.
  Copyright (c) 2018, Adafruit Industries (adafruit.com)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _UL_840_
#define _UL_840_

/** Master clock frequency */
#define VARIANT_MCK (64000000ul)

#define USE_LFXO // Board uses 32khz crystal for LF
// #define USE_LFRC    // Board uses RC for LF

#define GPS_BAUDRATE 38400

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Number of pins defined in PinDescription array
#define PINS_COUNT (48)
#define NUM_DIGITAL_PINS (48)
#define NUM_ANALOG_INPUTS (6)
#define NUM_ANALOG_OUTPUTS (0)

// LEDs
#define PIN_LED1 (38)
#define PIN_LED2 (24)

#define LED_BUILTIN PIN_LED1
#define LED_CONN PIN_LED2

#define LED_GREEN PIN_LED1
#define LED_BLUE PIN_LED2

#define LED_STATE_ON 1 // State when LED is litted

  /*
   * Buttons
   */

#define PIN_BUTTON1 17 // Pin for button on E-ink button module or IO expansion
#define BUTTON_NEED_PULLUP
#define PIN_BUTTON2 14
#define PIN_BUTTON3 39
// #define PIN_BUTTON4 25

/*
 * Analog pins
 */
#define PIN_A0 (5)
#define PIN_A1 (31)
#define PIN_A2 (28)
#define PIN_A3 (29)
#define PIN_A4 (30)
#define PIN_A5 (31)
#define PIN_A6 (0xff)
#define PIN_A7 (0xff)

  static const uint8_t A0 = PIN_A0;
  static const uint8_t A1 = PIN_A1;
  static const uint8_t A2 = PIN_A2;
  static const uint8_t A3 = PIN_A3;
  static const uint8_t A4 = PIN_A4;
  static const uint8_t A5 = PIN_A5;
  static const uint8_t A6 = PIN_A6;
  static const uint8_t A7 = PIN_A7;
#define ADC_RESOLUTION 14

// Other pins
#define PIN_AREF (2)
#define PIN_NFC1 (9)
#define PIN_NFC2 (10)

  static const uint8_t AREF = PIN_AREF;

/*
 * Serial interfaces
 */
#define PIN_SERIAL1_RX (6)
#define PIN_SERIAL1_TX (26)

// Connected to Jlink CDC
#define PIN_SERIAL2_RX (8)
#define PIN_SERIAL2_TX (6)

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 2

#define PIN_SPI_MISO (36)
#define PIN_SPI_MOSI (20)
#define PIN_SPI_SCK (33)
// xiaobanzi
#define PIN_SPI1_MISO (31) // (0 + 29)
#define PIN_SPI1_MOSI (23) // (0 + 30)
#define PIN_SPI1_SCK (42)  // (0 + 3)
  // danamzi
  //  #define PIN_SPI1_MISO (31) // (0 + 29)
  //  #define PIN_SPI1_MOSI (23) // (0 + 30)
  //  #define PIN_SPI1_SCK (35)   // (0 + 3)

  static const uint8_t SS = 21;
  static const uint8_t MOSI = PIN_SPI_MOSI;
  static const uint8_t MISO = PIN_SPI_MISO;
  static const uint8_t SCK = PIN_SPI_SCK;

// dabanzi
//  #define TFT_CS         34
//  #define TFT_RST        45 // Or set to -1 and connect to Arduino RESET pin
//  #define TFT_DC         42

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA (32)
#define PIN_WIRE_SCL (15)

  /* @note RAK5005-O GPIO mapping to RAK4631 GPIO ports
     RAK5005-O <->  nRF52840
     IO1       <->  P0.17 (Arduino GPIO number 17)
     IO2       <->  P1.02 (Arduino GPIO number 34)
     IO3       <->  P0.21 (Arduino GPIO number 21)
     IO4       <->  P0.04 (Arduino GPIO number 4)
     IO5       <->  P0.09 (Arduino GPIO number 9)
     IO6       <->  P0.10 (Arduino GPIO number 10)
     IO7       <->  P0.28 (Arduino GPIO number 28)
     SW1       <->  P0.01 (Arduino GPIO number 1)
     A0        <->  P0.04/AIN2 (Arduino Analog A2
     A1        <->  P0.31/AIN7 (Arduino Analog A7
     SPI_CS    <->  P0.26 (Arduino GPIO number 26)
   */

  // RAK4630 LoRa module

  /* Setup of the SX1262 LoRa module ( https://docs.rakwireless.com/Product-Categories/WisBlock/RAK4631/Datasheet/ )

  P1.10   NSS     SPI NSS (Arduino GPIO number 42)
  P1.11   SCK     SPI CLK (Arduino GPIO number 43)
  P1.12   MOSI    SPI MOSI (Arduino GPIO number 44)
  P1.13   MISO    SPI MISO (Arduino GPIO number 45)
  P1.14   BUSY    BUSY signal (Arduino GPIO number 46)
  P1.15   DIO1    DIO1 event interrupt (Arduino GPIO number 47)
  P1.06   NRESET  NRESET manual reset of the SX1262 (Arduino GPIO number 38)

  Important for successful SX1262 initialization:

  * Setup DIO2 to control the antenna switch
  * Setup DIO3 to control the TCXO power supply
  * Setup the SX1262 to use it's DCDC regulator and not the LDO
  * RAK4630 schematics show GPIO P1.07 connected to the antenna switch, but it should not be initialized, as DIO2 will do the
  control of the antenna switch

  SO GPIO 39/TXEN MAY NOT BE DEFINED FOR SUCCESSFUL OPERATION OF THE SX1262 - TG

  */

#define DETECTION_SENSOR_EN 4

#define USE_SX1262
#define SX126X_CS (21)
#define SX126X_DIO1 (19)
#define SX126X_BUSY (25)
#define SX126X_RESET (22)
// #define SX126X_TXEN (39)
// #define SX126X_RXEN (37)
// #define SX126X_POWER_EN (37)
// DIO2 controlls an antenna switch and the TCXO voltage is controlled by DIO3
// #define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8

// Testing USB detection
#define NRF_APM

  // enables 3.3V periphery like GPS or IO Module
  // Do not toggle this for GPS power savings
  // #define PIN_3V3_EN (34)

#define PIN_GPS_RESET (8)
#define PIN_GPS_EN (4)
#define PIN_GPS_PPS (17) // Pulse per second input from the GPS

#define GPS_RX_PIN PIN_SERIAL1_RX
#define GPS_TX_PIN PIN_SERIAL1_TX

  // Define pin to enable GPS toggle (set GPIO to LOW) via user button triple press

#define MAX17048 1
#define ul_840

  // #define MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR 1

#define MESHTASTIC_EXCLUDE_RANGETEST 1
#define MESHTASTIC_EXCLUDE_DETECTIONSENSOR 1
#define MESHTASTIC_EXCLUDE_TRACEROUTE 1
#define MESHTASTIC_EXCLUDE_POWERSTRESS 1
#define MESHTASTIC_EXCLUDE_ATAK 1

#define MESHTASTIC_EXCLUDE_MQTT 1
#define MESHTASTIC_EXCLUDE_WIFI 1

#define MESHTASTIC_EXCLUDE_WAYPOINT 1
#define MESHTASTIC_EXCLUDE_REMOTEHARDWARE 1
#define MESHTASTIC_EXCLUDE_INPUTBROKER 1




#ifdef __cplusplus
}
#endif

#endif