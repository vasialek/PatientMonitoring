/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

const int PikeLength = 3;
const int MaxPikePosition = 5;

struct PatientInfo {
  char name[17];
  float temperature;
  int pulse;
  int sys;
  int dia;

  // Deltas
  float dTemperature;
  int dPulse;
  int dSys;
  int dDia;
};

byte symbol1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B11011,
  B00000,
};

byte symbol2[8] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10010,
  B10010,
  B00011,
  B00010,
};

byte symbol3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01010,
  B10001,
  B00000,
};

byte symbol4[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte symbol5[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte symbol6[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte symbol7[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte symbol8[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

PatientInfo _patient;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();

  sprintf(_patient.name, "Green Frog\0");
  _patient.temperature = 37.9;
  _patient.pulse = 100;
  _patient.sys = 122;
  _patient.dia = 77;

  _patient.dTemperature = 0;
  _patient.dPulse = 0;
  _patient.dSys = 0;
  _patient.dDia = 0;

  lcd.createChar(0, symbol1);
  lcd.createChar(1, symbol2);
  lcd.createChar(2, symbol3);
  lcd.createChar(3, symbol4);
  lcd.createChar(4, symbol5);
  lcd.createChar(5, symbol6);
  lcd.createChar(6, symbol7);
  lcd.createChar(7, symbol8);
}

void loop() {
  char buf[16];
  displayPatientScreen();
  delay(3000);

  for (int i = 0; i < 10; i++) {
      _patient.dPulse = rand() % 5 - 2;
      displayTemperatureScreen();
      delay(1000);
  }

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(_patient.name);
  lcd.setCursor(10, 1);
  sprintf(buf, "P:%3d\0", _patient.pulse + _patient.dPulse);
  lcd.print(buf);
  for (byte i = 0; i < 3; i++) {
    for (byte pos = 0; pos < MaxPikePosition; pos++) {
      drawPikePeriod(pos * PikeLength);
  
      for (byte i = 0; i < 1; i++) {
        int positionToClear = pos + 2;
        if (positionToClear >= MaxPikePosition) {
          clearPikePeriod(3 * (positionToClear - MaxPikePosition));
        } else {
          clearPikePeriod(3 * positionToClear);
        }
        delay(200);
      }
      
    }
    delay(300);
  }
}

void drawPikePeriod(int pos) {
  for (int d = 0; d < 3; d++) {
    lcd.setCursor(pos + d, 0);
    lcd.write(byte(d));
    delay(200);
  }
}

void clearPikePeriod(int pos) {
  for (int d = 0; d < 3; d++) {
    lcd.setCursor(pos + d, 0);
    lcd.print(" ");
    delay(300);
  }
}
void drawHighPikeAt(int pos) {
    lcd.setCursor(pos, 0);
    lcd.write(byte(0));
    lcd.write(byte(1));
    lcd.write(byte(2));
    lcd.print(" ");
//    lcd.print(" ");
    
    lcd.setCursor(pos, 1);
    lcd.write(byte(4));
    lcd.print(" ");
    lcd.write(byte(6));
    lcd.write(byte(7));
//    lcd.print(" ");
}

void drawSmallPikeAt(int pos) {
  lcd.setCursor(pos, 1);
  lcd.write(byte(3));
  lcd.write(byte(5));
}

void displayTemperatureScreen() {
  char buf[17];
  char str[8];

  dtostrf(_patient.temperature, 5, 2, str);
  sprintf(buf, "SYS: %3d T:%s\0", _patient.sys, str);
  lcd.setCursor(0, 0);
  lcd.print(buf);

  sprintf(buf, "DIA: %3d P:%5d\0", _patient.dia, _patient.pulse + _patient.dPulse);
  lcd.setCursor(0, 1);
  lcd.print(buf);
}

void displayPatientScreen() {
  char buf[17] = "                \0";
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Patient name:");

  lcd.setCursor(0, 1);
  lcd.print(_patient.name);
}
