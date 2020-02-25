/* Test Bench code for Artificial Tongue - V1 (branch 3)
 *  Includes multiple inflation functions - measure this stuff
 *  Buttons
 *  Basic LCD display
 *  Testing pressure sensors/Calibration
 */
// **** LIBRARIES TO INCLUDE ****
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// ****** CONSTANTS AND VARIABLES ******

//    PINOUTS - see pinout diagram in Claire's daily updates
const int backSol = 10;     //Back Section D10
const int midSol = 11;      // Middle section D11
const int frontSol = 12;    // Front section D12
const int btn1 = 2;         // Button 1, D2
const int btn2 = 3;         // Button 2, D3
const int btn3 = 4;         // Button 3, D4
const int btn4 = 5;         // Button 4, D5
const int pres_1 = 5;       // pressure sensor 1 (white wire), A3
const int pres_2 = 4;       // pressure sensor 2 (yellow wire), A2
const int pres_3 = 3;       // pressure sensor 3 (black wire), A1

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack

// OTHER MISC CONSTANTS
int Pmin = 0;   // minimum pressure reading on sensor
//    VARIABLES FOR READINGS
int frontBtn = 0;     // Button 1 - inflate front
int midBtn = 0;       // Button 2 - inflate mid
int backBtn = 0;      // Button 3 - inflate back
int allBtn = 0;       // Button 4 - inflate ALL

void setup() {
  // solenoids
  pinMode(backSol, OUTPUT);     // Back Section D10
  pinMode(midSol, OUTPUT);     // Middle section D11
  pinMode(frontSol, OUTPUT);     // Front section D12
  
  //buttons
  pinMode(btn1, INPUT);      // Button 1 D2
  pinMode(btn2, INPUT);      // Button 2 D3
  pinMode(btn3, INPUT);      // Button 3 D4
  pinMode(btn4, INPUT);      // Button 4 D5

  // activate LCD module
  lcd.begin (20,4);          // for 20 x 4 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);

  // set up pressure sensors
  pinMode(pres_1, INPUT);     // Pressure sensor 1
  pinMode(pres_2, INPUT);     // Pressure sensor 2
  pinMode(pres_3, INPUT);     // Pressure sensor 3

  // start serial monitor
   Serial.begin(9600);     // print pressure values to serial read out, 9600 baud rate
}
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

void inflateSection(int section, int sec) {
  /*
   * Takes in section and time, inflates for that long
   */
   digitalWrite(section, HIGH);     // section on
   delay(sec*1000);                  // run for time
   digitalWrite(section, LOW);      // turn off
}

void inflateAll(int sec) {
  /*
   * takes in time, inflates all sections for that long, then turns off solenoids
   */
   digitalWrite(backSol, HIGH);
   digitalWrite(midSol, HIGH);
   digitalWrite(frontSol, HIGH);
   delay(sec*1000);
   digitalWrite(backSol, LOW);
   digitalWrite(midSol, LOW);
   digitalWrite(frontSol, LOW);
}

float readPressure(int pin) {
  /*
   * takes in pressure sensor pin, 
   * returns output pressure 
   * modified from soft robotics toolkit
   */
   int sensorValue = analogRead(pin);       // reads sensor value
   
   // convert sensor value to voltage
   float voltage = sensorValue * (5.0 / 1023.0);

   // convert volts to PSI
   float pressure_Value = ((voltage - (0.10 * 5.0)) / (0.80 * 5.0)) * 30;
   
   // return PSI value
   return pressure_Value;
   }
// ******** MAIN LOOP *******
void loop() {
  //lcdMain();      // Turn on LCD main menu
  
  frontBtn = digitalRead(btn1);     // Check if button 1 is pressed
  midBtn = digitalRead(btn2);       // Check if button 2 is pressed
  backBtn = digitalRead(btn3);      // Check if button 3 is pressed
  allBtn = digitalRead(btn4);       // Check if button 4 is pressed
  
  // Inflate Front if button 1 is pressed, inflate for 2 seconds
  if (frontBtn == HIGH)
  {
    //lcdMain();
    inflateSection(frontSol, 5);
  }

  // inflate middle if button 2 is pressed, inflate for 2 seconds
  else if (midBtn == HIGH)
  {
    inflateSection(midSol, 5);
  }

  //inflate back if button 3 is pressed, inflate for 2 seconds
  else if (backBtn == HIGH)
  {
    inflateSection(backSol, 5);
  }

  // inflate all if button 4 is pressed
  else if (allBtn == HIGH)
  {
    inflateAll(5);
  }
  
    float pressure_1 = readPressure(pres_1);
    Serial.println(pressure_1);
}
