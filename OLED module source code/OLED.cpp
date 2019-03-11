// Derived from LiquidCrystal by David Mellis
// Initialization sequence fixed by Technobly - 9/22/2013

#include "OLED.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>
#include "Arduino.h"

OLED::OLED(uint8_t ver, uint8_t rs, uint8_t rw, uint8_t enable,
			     uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  init(ver, rs, rw, enable, d4, d5, d6, d7);
}

void OLED::init(uint8_t ver, uint8_t rs, uint8_t rw, uint8_t enable,
			 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
  _oled_ver = ver;
  if(_oled_ver != OLED_V1 && _oled_ver != OLED_V2) {
    _oled_ver = OLED_V2;
  }
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;
  
  _data_pins[0] = d4;
  _data_pins[1] = d5;
  _data_pins[2] = d6;
  _data_pins[3] = _busy_pin = d7;

  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  
  _displayfunction = LCD_FUNCTIONSET | LCD_4BITMODE;
   
  begin(16, 2);  
}

void OLED::begin(uint8_t cols, uint8_t lines) 
{
  _numlines = lines;
  _currline = 0;
  
  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  
  digitalWrite(_rs_pin, LOW);
  digitalWrite(_enable_pin, LOW);
  digitalWrite(_rw_pin, LOW);
  
  delayMicroseconds(50000); 
  for (int i = 0; i < 4; i++) {
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], LOW);
  }

  write4bits(0x03); 
  delayMicroseconds(5000);
  if(_oled_ver == OLED_V2) { 
    write4bits(0x08);
    delayMicroseconds(5000);
  }
  write4bits(0x02);
  delayMicroseconds(5000);
  write4bits(0x02);
  delayMicroseconds(5000);
  write4bits(0x08);
  delayMicroseconds(5000);
  
  command(0x08);	// Turn Off
  delayMicroseconds(5000);
  command(0x01);	// Clear Display
  delayMicroseconds(5000);
  command(0x06);	// Set Entry Mode
  delayMicroseconds(5000);
  command(0x02);	// Home Cursor
  delayMicroseconds(5000);
  command(0x0C);	// Turn On - enable cursor & blink
  delayMicroseconds(5000);
}

/********** high level commands, for the user! */
void OLED::clear()
{
  command(LCD_CLEARDISPLAY);  
}

void OLED::home()
{
  command(LCD_RETURNHOME);  
}

void OLED::setCursor(uint8_t col, uint8_t row)
{
  uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row >= _numlines ) 
  {
    row = 0;
  }
  
  command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void OLED::noDisplay() 
{
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void OLED::display() 
{
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void OLED::noCursor() 
{
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void OLED::cursor() 
{
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void OLED::noBlink() 
{
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void OLED::blink() 
{
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void OLED::scrollDisplayLeft(void) 
{
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void OLED::scrollDisplayRight(void) 
{
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void OLED::leftToRight(void) 
{
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

void OLED::rightToLeft(void) 
{
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

void OLED::autoscroll(void) 
{
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

void OLED::noAutoscroll(void) 
{
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

void OLED::createChar(uint8_t location, uint8_t charmap[]) 
{
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) 
  {
    write(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void OLED::command(uint8_t value) 
{
  send(value, LOW);
  waitForReady();
}

inline size_t OLED::write(uint8_t value) 
{
  send(value, HIGH);
  waitForReady();
}

/************ low level data pushing commands **********/

void OLED::send(uint8_t value, uint8_t mode) 
{
  digitalWrite(_rs_pin, mode);
  pinMode(_rw_pin, OUTPUT);
  digitalWrite(_rw_pin, LOW);
  
  write4bits(value>>4);
  write4bits(value);
}

void OLED::pulseEnable(void) 
{
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(50);  
  digitalWrite(_enable_pin, LOW);
}

void OLED::write4bits(uint8_t value) 
{
  for (int i = 0; i < 4; i++) 
  {
    pinMode(_data_pins[i], OUTPUT);
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }
  delayMicroseconds(50);
  pulseEnable();
}

void OLED::waitForReady(void) 
{
  unsigned char busy = 1;
  pinMode(_busy_pin, INPUT);
  digitalWrite(_rs_pin, LOW);	
  digitalWrite(_rw_pin, HIGH);      
  do
  {
  	digitalWrite(_enable_pin, LOW);
  	digitalWrite(_enable_pin, HIGH);

  	delayMicroseconds(10);
  	busy = digitalRead(_busy_pin);
  	digitalWrite(_enable_pin, LOW);
  	
  	pulseEnable();
  }
  while(busy);
  
  pinMode(_busy_pin, OUTPUT);
  digitalWrite(_rw_pin, LOW);
}



/**
 * @class OLED
 *
 * @brief Klasa zajmuj¹ca siê konfiguracj¹ wyœwietlacza OLED, dziêki jej mamy podstawowe mo¿liwoœci obs³ugi wyœwietlacza.
 *
 * Klasa zajmuj¹ca siê konfiguracj¹ wyœwietlacza OLED, dziêki jej mamy podstawowe mo¿liwoœci obs³ugi wyœwietlacza.
 */
//=================== WYSWIETLANIE BUFORA NA LCD ===========================
/**
     * Metoda wyœwietlaj¹ca bufor pamiêci.
     * @param[in]  type:uint16_t address pamiêci EEPROM
*/
void OLED::displayBuf(uint16_t address) {
	setCursor(0, 0);
	for (uint16_t i = address; i < ((100 * 16 / 8) + address); i++) {
		write(readAddress(i));
		delay(25);
	}
}

/**
     * Metoda odczytuj¹ca pamiêæ EEPROM
     * @param[in]  type:uint16_t address pamiêci EEPROM
*/
int8_t OLED::readAddress(uint16_t address)
{
	byte rData = 0xFF;
	Wire.beginTransmission(EEPROM_I2C_ADDRESS);
	Wire.write((int16_t)(address >> 8));   // MSB
	Wire.write((int16_t)(address & 0xFF)); // LSB
	Wire.endTransmission();
	Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);
	rData = Wire.read();
	return rData;
}