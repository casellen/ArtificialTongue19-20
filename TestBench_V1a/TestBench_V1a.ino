/* Test Bench code for Artificial Tongue - V1a
 *  Basic timed inflation code to test seal on tongue/misc things
 *  Loop reads pressure sensor 1 and prints value to LCD
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
const int pres_1 = A3;       // pressure sensor 1 (white wire), A3
const int pres_2 = A2;       // pressure sensor 2 (yellow wire), A2
const int pres_3 = A1;       // pressure sensor 3 (black wire), A1

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack

// OTHER MISC CONSTANTS
int Pmin = 0;   // minimum pressure reading on sensor
//    VARIABLES FOR READINGS
int frontBtn = 0;     // Button 1 - inflate front
int midBtn = 0;       // Button 2 - inflate mid
int backBtn = 0;      // Button 3 - inflate back
int allBtn = 0;       // Button 4 - inflate ALL
float cur_pres[3];     // initialize cur_pres array to store pressure values

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
   * takes in time and Pin Val, inflates all sections for that long, then turns off solenoids
   */
   
   digitalWrite(backSol, HIGH);
   digitalWrite(midSol, HIGH);
   digitalWrite(frontSol, HIGH);
   delay(sec*1000);
   cur_pres[0] = readPressure(pres_1);    // Read out pressure sensor WHILE inflating! - Sensor 1
   cur_pres[1] = readPressure(pres_2);    // Read out pressure senor 2
   cur_pres[2] = readPressure(pres_3);    // Read out pressure sensor 3
   delay(250);
   digitalWrite(backSol, LOW);
   digitalWrite(midSol, LOW);
   digitalWrite(frontSol, LOW);
   //return cur_pres;   //This is a global variable so it shouldn't need to return it
}

float readPressure(int pin) {
  /*
   * takes in pressure sensor pin, 
   * returns output pressure 
   * modified from soft robotics toolkit
   */
   int sensorValue = analogRead(pin);       // reads sensor value
   
   // convert sensor value to voltage
   float voltage = (float)sensorValue * (5.0f / 1023.0f);

   // convert volts to PSI
   float pressure_Value = ((voltage - (0.10f * 5.0f)) / (0.80f * 5.0f)) * 30.0f;
   
   // return PSI value
   return pressure_Value;
   }

// ******** MAIN LOOP *******
void loop() {
  //lcdMain();      // Turn on LCD main menu
  inflateAll(2);
  lcd.println(cur_pres[0]);
  lcd.println(cur_pres[1]);
  lcd.println(cur_pres[2]);
  delay(500);
  lcd.clear();
  
  

}
