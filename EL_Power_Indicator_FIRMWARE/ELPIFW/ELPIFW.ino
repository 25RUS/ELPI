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
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <math.h>

#define VREF 5.02      // точное напряжение на пине 5V (в данном случае зависит от стабилизатора на плате Arduino)
#define R1 51600  // точное значение 10 кОм резистора
#define R2 4640   // точное значение 4.7 кОм резистора
#define Rsh 0.1
#define R50i 50000
#define R4i 4460
#define R50o 51400
#define R4o 4400

//#define 

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 4, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  hello();
  Serial.begin(9600);
}

void hello()
{
  for(int i=0; i<12; i++)
  {
    lcd.setCursor(0, 0);
    lcd.print("Electronic load");
    lcd.setCursor(i, 1);
    lcd.print(">>>");
    delay(100);
    lcd.clear();
  }
  
}

float Thermistor(int Vo)    // функция для расчета значения температуры
{ 
   float T;
   float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07;
   float logRt = log(10000.0*((1024.0/Vo-1))); 
   T = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));  // рассчитываем значение температуры в кельвинах по формуле Стейнхарта-Харта
   float Tc = T - 273.15;                     // переводим температуру из кельвинов в градусы
   //Tf = (Tc * 1.8) + 32.0;              // переводим температуру в шкалу Фаренгейта
   return Tc;
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):

  
  //float voltage = (float)analogRead(0) * VREF * ((R1 + R2) / R2) / 1024;
  float voltage = (float)analogRead(0) * VREF * 12.1206896552 / 1024;
  //float current=(((float)analogRead(1) * VREF)/1024) / 0.001; //4V - выход с LM358 при Uип = 5V; Uш = 0,1V, что в 40 раза меньше 


  //float U1 = (float)analogRead(3) * VREF * ((R50i + R4i) / R4i) / 1024;
  //float U2 = (float)analogRead(4) * VREF * ((R50o + R4o) / R4o) / 1024;
  //float U1 = (float)analogRead(3) * VREF * 12.2107623318 / 1024;
  //float U2 = (float)analogRead(4) * VREF * 12.6818181818 / 1024;
  //float dU = U1 - U2; 
  //float current = fabsf(dU) / Rsh;

  float current = 0.00;
  
 

  //debug(U1, U2, dU);

  
  float power = voltage * current;
  float temperature = Thermistor(analogRead(2)); // Thermistor(256);

  pinMode(5, OUTPUT);
  
  if(current > 0.5)
  {
    digitalWrite(5, HIGH);
  }
  else if(temperature > 25)
  {
    digitalWrite(5, HIGH);
  }
  else
  {
    digitalWrite(5, LOW);
  }
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("U=");
  lcd.print(voltage, 1);
  lcd.print("V");

  lcd.setCursor(8, 0);
  lcd.print("I=");
  lcd.print(current, 2);
  lcd.print("A");

  lcd.setCursor(0, 1);
  lcd.print("P=");
  lcd.print(power, 1);
  lcd.print("W");

  lcd.setCursor(8, 1);
  lcd.print("t=");
  lcd.print(temperature, 1);
  lcd.print("C");

  
  
  delay(500);
}

void debug( float U1, float U2, float dU)
{
  //if(Serial.available() == true)
  //{
    Serial.print("U1=");
    Serial.print(U1);
    Serial.print("\tU2=");
    Serial.print(U2);
    Serial.print("\tdU=");
    Serial.print(dU);
    Serial.print('\n');
 // }
}
