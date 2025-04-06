/** main.cpp
 * Sun  6 Apr 12:52:38 UTC 2025
 * Sat  5 Apr 13:35:03 UTC 2025
 */

#include "lcd_uses.h"
#include <Adafruit_GPS.h>
#include <Arduino.h>
#include <stdint.h>

#define GPSSerial Serial1 // what's the name of the hardware serial port?
#define GPSECHO true      // 2 Apr 2025

Adafruit_GPS GPS(&GPSSerial);

void initGPS() {
    delay(800);
    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
    GPS.sendCommand(PGCMD_ANTENNA);
    delay(1000);
    GPSSerial.println(PMTK_Q_RELEASE);
    Serial.println("initGPS() exits here..");
}

void blinkWaiting() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(20);
    digitalWrite(LED_BUILTIN, LOW);
    delay(9100);
}

void initSerial() {
    delay(5200);
    Serial.begin(115200);
    while (!Serial) {
        blinkWaiting();
    }
    delay(800);
    Serial.println(" Serial connection detected!");
    Serial.print(__DATE__);
    Serial.write(' ');
    Serial.write(' ');
    Serial.print(__TIME__);
    Serial.println("");
}

void initGPIO() {
    pinMode(LED_BUILTIN, OUTPUT);
}

uint16_t iter = 0;

void noOperation() {
    // int32_t sampled = random(33);
    // int32_t Latitude; Latitude = GPS.latitude_fixed;
    GPS.read();

    if (GPS.newNMEAreceived()) {
        if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived()
                                        // flag to false
            return;                     // we can fail to parse a sentence
        // in which case we should just wait for another
    }

    if (!GPS.fix) {
        return;
    }

    int32_t Latitude = 0;
    int32_t Longitude = 0;
    delayMicroseconds((7));
    Serial.print(" LINE: ");
    Serial.print(__LINE__);
    Serial.print("  GPS.fix active  ");
    delayMicroseconds((7));
    Latitude = GPS.latitude_fixed;
    // Latitude = Latitude - sampled;
    delayMicroseconds((7));
    delayMicroseconds((7));
    Serial.print(" LINE: ");
    Serial.print(__LINE__);
    Serial.print("  GPS.fix active  ");
    delayMicroseconds((7));
    Longitude = GPS.longitude_fixed;
    // Longitude = Longitude - sampled;
    delayMicroseconds((7));
    iter++;
    Serial.print(iter);
    Serial.write(':');
    Serial.write(' ');
    Serial.print(Latitude);
    Serial.write(' ');
    Serial.write(' ');
    Serial.println(Longitude);
    // Serial.println(sampled);
    return;
}

void setup() {
    initGPIO();
    setup_LCD();
    initSerial();
    initGPS();
}

void loop() {
    noOperation();
    delay(100);
}

/* end. */
