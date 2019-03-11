/**
 * @class LED
 *
 * @brief Plik zajmujący się obsługą LED. Jest to klasa zajmująca się obsługą LED od strony technicznej. Znajdują się w niej główne metody, dzięki którym można wyświetlić dany kolor, czy zaktualizować pamięć.
 * 
 *Plik zajmujący się obsługą LED. Jest to klasa zajmująca się obsługą LCD od strony technicznej. Znajdują się w niej główne metody, dzięki którym można wyświetlić dany kolor, czy zaktualizować pamięć.
 */
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <TinyWireM.h>  
#define EEPROM_I2C_ADDRESS 0x50
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN          1
#define NUMLeds      8
Adafruit_NeoPixel Leds = Adafruit_NeoPixel(NUMLeds, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial SoftSerial(3, 4);

String RawMicrocode;
byte start=0;
int PrimaryAdress;
/**
     * Funkcja, która uruchamiana jest w momencie startu układu.
     */
void setup() {
   #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  SoftSerial.begin(4800);
  TinyWireM.begin();
  Leds.begin(); 
  ReadCommand("", 0);

}

/**
     * Funkcja, która uruchamiana co cykl procesora.
     */
void loop() {
  if (SoftSerial.available()) {
    RawMicrocode = SoftSerial.readString();
    ReadCommand(RawMicrocode, 1);
  }
}
/**
     * Funkcja zapisuje do pamięci EEPROM.
     *@param[in] type:int address do jakiej komórki się zapisuje.
	  *@param[in] type:byte val wartość jaką należy zapisać w pamięci
     *@return[out] type:byte Zwraca zawartość komórki pamięci.
     */
void writeAddress(int address, byte val)
{
  int rdata = val;
  TinyWireM.beginTransmission(EEPROM_I2C_ADDRESS);
  TinyWireM.send((int)(address >> 8));
  TinyWireM.send((int)(address & 0xFF));
  TinyWireM.send(rdata);
  TinyWireM.endTransmission();
  delay(5);
}
/**
     * Funkcja odczytuje do pamięci EEPROM.
     *@param[in] type:int address do jakiej komórki mamy się odwłować
     *@return[out] type:byte Zwraca zawartość komórki pamięci.
     */
byte readAddress(int address)
{
 byte rdata = 0xFF;
  TinyWireM.beginTransmission(EEPROM_I2C_ADDRESS);
  TinyWireM.send((int)(address >> 8));
  TinyWireM.send((int)(address & 0xFF));
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(EEPROM_I2C_ADDRESS,1);
  if (TinyWireM.available())
  {
    rdata = TinyWireM.receive();
  }
  return rdata;
}
/**
     * Funkcja, która ustawia LED i pozwala aktualizować pamięć EEPROM
     *@param[in] type:String Text rozkaz w postaci tekstu do wykonania 
	  *@param[in] type:byte Def podstawowy rozkaz do wykonania
     */
void ReadCommand(String Text, byte Def)
{
  if (Def == 1)
  {
     PrimaryAdress = Text.substring(9, 29).toInt();
  }
  else
  {
  PrimaryAdress = readAddress(readAddress(2));
  }
  if (Text.substring(5, 8) == "001" || Def == 0)
  {
    byte R;
    byte G;
    byte B;
    for (int i = 0; i < NUMLeds; i++) {
      R = PrimaryAdress;
      G = R + 1;
      B = R + 2;
     Leds.setPixelColor(i, Leds.Color(readAddress(R), readAddress(G), readAddress(B)));
      PrimaryAdress = R + 3;
      Leds.show();
      delay(10);
    }
  }
  if (Text.substring(5, 8) == "002")
  {
    SoftSerial.println(readAddress(Text.substring(9, 29).toInt()));
  }
  if (Text.substring(5, 8) == "003")
  {
    byte val = Text.substring(9, 12).toInt();
    int adress = Text.substring(12, 29).toInt();
      writeAddress(adress, val);
      if(readAddress(adress)==val)
      {
         SoftSerial.println(0001|003|255);
      }
      else
      {
         SoftSerial.println(0001|003|0);
      }
  }
}
