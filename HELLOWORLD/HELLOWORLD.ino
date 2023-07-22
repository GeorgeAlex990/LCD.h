/*By George
 * This is an example for LCD.h library
 * With this code you can display a simple "HELLO WORLD" on yor LCD
 */

#include <avr/pgmspace.h>
#include <LCD.h>
#include <Wire.h>

LCD MyLcd;

uint16_t matrixType = 0000; // Change to match your display type

void setup() {
  // put your setup code here, to run once:
  MyLcd.Init();
  MyLcd.Display_Clear(matrixType);
}

void loop() {
  // put your main code here, to run repeatedly:
  MyLcd.Display_ASCII(2, 2, "HELLO WORLD");
}
