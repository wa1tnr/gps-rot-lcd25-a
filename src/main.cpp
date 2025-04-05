/* Sat  5 Apr 13:35:03 UTC 2025 */

#include <Arduino.h>
#include <stdint.h>

void blinkWaiting() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
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
    initSerial();
}

void loop() {
    noOperation();
    delay(100);
}

/* end. */