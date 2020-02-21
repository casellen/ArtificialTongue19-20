/* TESTING A SINGULAR BUTTON UNTIL IT WORKS
 *  Includes:
 *  Buttons AND debounce
 *  Basic LCD display
 */
// **** LIBRARIES TO INCLUDE ****
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// ****** CONSTANTS AND VARIABLES ******
//    PINOUTS
const int backSol = 10;     //Back Section D10
const int midSol = 11;      // Middle section D11
const int frontSol = 12;    // Front section D12
const int btn1 = 2;         // Button 1, D2
const int btn2 = 3;         // Button 2, D3
const int btn3 = 4;         // Button 3, D4
const int btn4 = 5;         // Button 4, D5
const int ledPin = 13;      // led is attached to pin 13, for status check

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack

//    VARIABLES FOR READINGS
int frontBtn = LOW;     // Button 1 - inflate front
int midBtn = LOW;       // Button 2 - inflate mid
int backBtn = LOW;      // Button 3 - inflate back
int allBtn = LOW;       // Button 4 - inflate ALL
int btn1State;        // current reading from input pin
int lastBtn1State = LOW;    // previous reading from input pin
int ledState = HIGH;    // turns on LED on start

// VARIABLES FOR DEBOUNCE! - unsigned longs
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


// ****** HELPER FUNCTIONS ******
void lcdMain() {
  /*
   * Prints main menu for LCD screen
   */
  lcd.home ();                  // set cursor to 0,0
  lcd.print("Select program:"); 
  lcd.setCursor (0,1);          // go to start of 2nd line
  lcd.print(" 1- front 2- middle");
  lcd.setCursor (0,2);
  lcd.print(" 3- back 4- inf all");
  lcd.setCursor (0,3);
  // lcd.print("send help please");
  delay(100);
}

// ************* SET UP ****************
void setup() {
  // solenoids
  pinMode(backSol, OUTPUT);     // Back Section D10
  pinMode(midSol, OUTPUT);     // Middle section D11
  pinMode(frontSol, OUTPUT);     // Front section D12
  pinMode(ledPin, OUTPUT);    // led pin
  
  //buttons
  pinMode(btn1, INPUT);      // Button 1 D2
  pinMode(btn2, INPUT);      // Button 2 D3
  pinMode(btn3, INPUT);      // Button 3 D4
  pinMode(btn4, INPUT);      // Button 4 D5

  // set initial LED state: 
  digitalWrite(ledPin, ledState);
  
  // activate LCD module
  lcd.begin (20,4);          // for 20 x 4 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
}

// ******** MAIN LOOP *******
void loop() {
  lcdMain();      // Turn on LCD main menu
  
  int frontBtn = digitalRead(btn1);     // Check if button 1 is pressed
//  midBtn = digitalRead(btn2);       // Check if button 2 is pressed
//  backBtn = digitalRead(btn3);      // Check if button 3 is pressed
//  allBtn = digitalRead(btn4);       // Check if button 4 is pressed
  
  // Inflate Front if button 1 is pressed, inflate for 2 seconds
  if (frontBtn != lastBtn1State)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
    
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (frontBtn != btn1State) {
      btn1State = frontBtn;

      // only toggle the LED if the new button state is HIGH
      if (btn1State == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastBtn1State = frontBtn;
  
//  // inflate middle if button 2 is pressed, inflate for 2 seconds
//  else if (midBtn == HIGH)
//  {
//    inflateSection(midSol, 5);
//  }
//
//  //inflate back if button 3 is pressed, inflate for 2 seconds
//  else if (backBtn == HIGH)
//  {
//    inflateSection(backSol, 5);
//  }
//
//  // inflate all if button 4 is pressed
//  else if (allBtn == HIGH)
//  {
//    inflateAll(5);
//  }

}
