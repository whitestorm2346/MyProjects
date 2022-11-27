#include <Adafruit_PM25AQI.h>
#include <SimpleDHT.h>
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include "ISD1820.h"

// object pin
#define PM25_PIN 0
#define DHT_PIN 1
#define MQ9_PIN 2
#define RECV_PIN 3
#define ISD_REC_PIN 4
#define ISD_PLAY_E_PIN 5
#define ISD_PLAY_L_PIN 6
#define LCD_PIN 7
#define LED_PIN 8

// remote control decode
#define REPORT_ALL 0
#define REPORT_PM25 1
#define REPORT_DHT 2
#define REPORT_GAS 3

// PM25 init
Adafruit_PM25AQI pm25(PM25_PIN);

// DHT init
SimpleDHT dht(DHT_PIN);

// MQ9 init

// IRremote init
IRrecv irrecv(RECV_PIN);
decode_results result;

// ISD1820 init
ISD1820 isd(ISD_REC_PIN, ISD_PLAY_E_PIN, ISD_PLAY_L_PIN);

// IC_LCD init
LiquidCrystal_I2C LCD(0x27, 16, 2);

void report(int code);
void print(int code);

// module initial part
void setup() {
  LCD.init();
  LCD.backlight();
  irrecv.enableIRIn();
}

// main loop
void loop() {
  if (irrecv.decode(&result)) {
    report(result.value);

    irrecv.resume();
  }
}

void report(int code){
  switch(code){
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
}

void print(int code){
  switch(code){
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
}