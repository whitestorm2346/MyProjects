#include <Adafruit_PM25AQI.h>
#include <SimpleDHT.h>
#include <IRremote.h>
#include <ISD1820.h>
#include <Adafruit_LiquidCrystal.h>

// object pin
#define PM25_PIN 0
#define DHT_PIN 1
#define MQ9_PIN 2
#define RECV_PIN 3
#define ISD_PIN 4
#define LCD_PIN 5
#define LED_PIN 6

// remote control decode
#define REPORT_ALL 0
#define REPORT_PM25 1
#define REPORT_DHT 2
#define REPORT_GAS 3

// MQ9 init

// DHT init

// IRremote init
IRrecv irrecv(RECV_PIN);
decode_results result;

// ISD1820 init

// IC_LCD init
Adafruit_LiquidCrystal LCD(0);

void setup() {
  LCD.begin(16, 2);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&result)) {
    switch (result.value) {
      case REPORT_ALL:
        break;

      case REPORT_PM25:
        break;

      case REPORT_DHT:
        break;

      case REPORT_GAS:
        break;

      default: break;
    }

    irrecv.resume();
  }
}