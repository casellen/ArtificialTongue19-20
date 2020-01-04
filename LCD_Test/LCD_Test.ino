/* Demonstration sketch for PCF8574T I2C LCD Backpack 
Uses library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads GNU General Public License, version 3 (GPL-3.0) */
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack

void setup()
{
  // activate LCD module
  lcd.begin (20,4); // for 20 x 4 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
}

void loop()
{
  lcd.home (); // set cursor to 0,0
  lcd.print("Select program:"); 
  lcd.setCursor (0,1);        // go to start of 2nd line
  lcd.print(" 1- front 2- middle");
  lcd.setCursor (0,2);
  lcd.print(" 3- back 4- inf all");
  lcd.setCursor (0,3);
  lcd.print("send help please");
 
  delay(1000);
}
