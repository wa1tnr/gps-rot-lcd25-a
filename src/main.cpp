/* main.cpp */

#include "ST7565.h"
#include <Arduino.h>
#include <stdint.h>

/***
 *
 * Sat  5 Apr 14:06:27 UTC 2025
 * Sat  5 Apr 13:35:03 UTC 2025
 *
 */

ST7565 glcd(11, 10, 9, 6, 5);

void lcd_revision(void) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%s",
             " Rev. RB-07a4 Apr 5 2025                                14:05z");

    glcd.drawstring(1, 1, buffer);

    snprintf(buffer, sizeof(buffer), "%s", "  CHUPACABRA");
    glcd.drawstring(1, 3, buffer);

    snprintf(buffer, sizeof(buffer), "%s", " Fracas Fandango Show ");
    glcd.drawstring(1, 5, buffer);

    snprintf(buffer, sizeof(buffer), "%s", " dr strangegrove     ");
    glcd.drawstring(1, 7, buffer);

    glcd.display();
    glcd.clear();
}

void setup_LCD() {
    glcd.begin(0x18);
    glcd.display();
    glcd.clear();
    delay(2800);
    lcd_revision();
}

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
    setup_LCD();
    initSerial();
}

void loop() {
    noOperation();
    delay(100);
}

/* end. */
