/** lcd_uses.cpp
 * Sun  6 Apr 18:22:37 UTC 2025
 */

#include "ST7565.h"
#include <Arduino.h>
ST7565 glcd(11, 10, 9, 6, 5);

void lcd_revision(void) {
    char buffer[64];
    glcd.clear();
    snprintf(buffer, sizeof(buffer), "%s", "Sun  6 Apr 18:22:37z");
    glcd.drawstring(1, 1, buffer);

    snprintf(buffer, sizeof(buffer), "%s", "  CHUPACABRA");
    glcd.drawstring(3, 3, buffer);

    glcd.display();
}

void setup_LCD() {
    glcd.begin(0x18);
    glcd.display();
    glcd.clear();
    delay(2800);
    lcd_revision();
}

/* end. */
