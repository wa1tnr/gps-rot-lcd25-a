/** main.cpp
 * Sun  6 Apr 18:22:37 UTC 2025
 * Sat  5 Apr 13:35:03 UTC 2025
 */

#include "lcd_uses.h"
#include <Adafruit_GPS.h>
#include <Arduino.h>
#include <stdint.h>

#define GPSSerial Serial1 // what's the name of the hardware serial port?
#define GPSECHO true      // 2 Apr 2025

uint16_t iter = 0;
uint32_t timer = millis();

Adafruit_GPS GPS(&GPSSerial);

void initGPS() {
    delay(800);
    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
    GPS.sendCommand(PGCMD_ANTENNA);
    delay(1000);
    GPSSerial.println(PMTK_Q_RELEASE);
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

void printLongLat(int32_t Longitude, int32_t Latitude) {
    iter++;
    Serial.print(iter);
    Serial.write(':');
    Serial.write(' ');
    Serial.print(Latitude);
    Serial.write(' ');
    Serial.write(' ');
    Serial.print(Longitude);
    Serial.println("");
}

void locating() {
    int32_t Longitude = 0;
    int32_t Latitude = 0;
    Longitude = GPS.longitude_fixed;
    Longitude = abs(Longitude);
    Latitude = GPS.latitude_fixed;
    Latitude = abs(Latitude);
    printLongLat(Longitude, Latitude);
}

void setup() {
    initGPIO();
    setup_LCD();
    initSerial();
    initGPS();
}

void loop() {
    GPS.read();
    if (GPS.newNMEAreceived()) {
        if (!GPS.parse(GPS.lastNMEA())) // this also sets the
                                        // newNMEAreceived() flag to false
            return;                     // we can fail to parse a sentence
        // in which case we should just wait for another
    }

    bool permitGPSFixCheck = false;

    if (timer > millis()) {
        timer = millis();
    }

    if (millis() - timer > 1700) {
        timer = millis();
        permitGPSFixCheck = true;
    }

    if (!permitGPSFixCheck) {
        return;
    }

    if (GPS.fix) {
        Serial.write(' ');
        Serial.write(' ');
        locating();
    } else {
        Serial.write('.');
        Serial.write(' ');
    }
    delay(100);
}

/* end. */
