/** main.cpp
 * Sat  5 Apr 16:35:14 UTC 2025
 * Sat  5 Apr 13:35:03 UTC 2025
 */

#include "lcd_uses.h"
#include <Arduino.h>
#include <stdint.h>

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
}

void initGPIO() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void noOperation() {
    return;
}

void setup() {
    initGPIO();
    setup_LCD();
    initSerial();
}

void loop() {
    noOperation();
    delay(100);
}

/* end. */
