/**
 * @class Main
 *
 * @brief Plik zajmujący się obsługą LCD. Jest to klasa zajmująca się obsługą LCD od strony technicznej. Znajdują się w niej główne metody, dzięki którym można wyświetlić tekst, czy zaktualizować pamięć.
 * 
 *Plik zajmujący się obsługą LCD. Jest to klasa zajmująca się obsługą LCD od strony technicznej. Znajdują się w niej główne metody, dzięki którym można wyświetlić tekst, czy zaktualizować pamięć.
 */
#define DEBUG 0
#include <Arduino.h>
#include <Wire.h>
#include <DS1307.h>
#include <OLED.h>
#include <SoftwareSerial.h>

/// Definicja zegara
DS1307 Clock;
/// Przypisanie zmiennej do zegara
RTCDateTime DataTimer;
/**
     * Funkcja zapisująca do pamięci EEPROM 
     *@param[in]  type:int address do jakiej komórki się zapisuje
     *@param[in]  type:byte val wartość jaką się zapisuje
     */
void WriteAddress (int address, byte val);
/**
     * Funkcja odczytuje do pamięci EEPROM.
     *@param[in] type:int address do jakiej komórki się zapisuje.
     *@return[out] type:byte Zwraca zawartość komórki pamięci.
     */
byte ReadAddress (int address);
/**
     * Funkcja ułatwia przesuwanie tekstu z lewej do prawej.
     *@param[in] type:string tekst do przesunięcia.
     */
void ScrollingMarquee (String u1);
/**
     * Główna Funkcja ułatwia sterowanie urządzeniem.
     *@param[in] type:string rozkaz wraz z argumentami
     */
void ReadCommand (String Text);
/**
     * Funkcja, która ustawia wyświetlacz w trybie Graficznym.
     *@param[in] type:int Data adres pamięci od którego wyświetlacz ma czytać pamięć EEPROM.
     */
void DisplayGraphic (int Data);
/**
     * Funkcja, która wysyła z urządzenia do PC/innego urządzenia wiadomość.
     *@param[in] type:string UUID indentyfikator urządzenia.
     *@param[in] type:string NumberCommand numer rozkazu.
      *@param[in] type:string Data treść wiadomości.
     */
void WriteCommand (String UUID, String NumberCommand, String Data);
/**
     * Funkcja, która wyświetla tekst na ekranie.
     *@param[in] type:Text_1 pierwszy wiersz tekstu. Pozycja <B>(0,0)</B>.
     *@param[in] type:Text_2 drugi wiersz tekstu. Pozycja <B>(0,1)</B>.
     */
void DrawText (String Text_1, String Text_2);
/**
     * Funkcja, która wyświetla dzien i godzinę na ekranie.
     */
void DisplayTime();
/// Uruchomienie wirtualnego portu COM
SoftwareSerial SoftUart (9, 10);
/// Ustawienie adresu pamięci EEPROM
#define EEPROM_I2C_ADDRESS 0x50
/// Definicja wyświetla OLED
OLED lcd (OLED_V2, 8, 7, 6, 5, 4, 3, 2);
/// Zmienne do obsługi mikrorozkazów
String RawMicrocode = "", RawMicrocode2 = "";
byte t = 0, f = 0;

/**
     * Funkcja, która uruchamiana jest w momencie startu układu.
     */
void setup ()
{
#if DEBUG == 1
    Serial.begin (9600);
#endif
    /// Uruchomienie transmisji I2C z pamięci EEPROM
    Wire.begin ();
    /// Nawiązania połączenia z zegarem.
    Clock.begin ();
    /// Uruchomienie transmisji UART z kontrolerem
    SoftUart.begin (4800);
    /// Uruchomienie wyświetlacza
    lcd.begin (16, 2);
    
}
/**
     * Funkcja, która uruchamiana co cykl procesora.
     */
void loop ()
{
    if (SoftUart.available ())
    {
        
        RawMicrocode = SoftUart.readString ();
        ReadCommand (RawMicrocode);
    }
    else
    {
        if (t == 0)
        {
            if (ReadAddress (000) == 001)
            {
                DisplayGraphic (2);
            }
            else if (ReadAddress (000) == 002)
            {
                DisplayTime ();
            }
            else
            {
                DrawText ("Witaj", "Swiecie!");
            }
            
            t = 1;
        }
        
    }
}
/**
     * Funckja zapisuje do pamięci EEPROM.
     *@param[in] type:int address do jakiej komórki się zapisuje.
	  *@param[in] type:byte val wartość jaką należy zapisać w pamięci
     *@return[out] type:byte Zwraca zawartość komórki pamięci.
     */
void WriteAddress (int address, byte val)
{
    int rdata = val;
    Wire.beginTransmission (EEPROM_I2C_ADDRESS);
    Wire.write ((int) (address >> 8));
    Wire.write ((int) (address & 0xFF));
    Wire.write (rdata);
    Wire.endTransmission ();
    delay (5);
}
/**
     * Funckja odczytuje do pamięci EEPROM.
     *@param[in] type:int address do jakiej komórki mamy się odwłować
     *@return[out] type:byte Zwraca zawartość komórki pamięci.
     */
byte ReadAddress (int address)
{
    byte rdata = 0xFF;
    Wire.beginTransmission (EEPROM_I2C_ADDRESS);
    Wire.write ((int) (address >> 8));
    Wire.write ((int) (address & 0xFF));
    Wire.endTransmission ();
    Wire.requestFrom (EEPROM_I2C_ADDRESS, 1);
    if (Wire.available ())
    {
        rdata = Wire.read ();
    }
    return rdata;
}


void ScrollingMarquee (String u1)
{
    
    for (int j = 0; j < 40; j++)
    {
        lcd.scrollDisplayLeft ();
        delay (250);
    }
    lcd.setCursor (1, 0);
    delay (250);
    ScrollingMarquee (u1);
}

void ReadCommand (String Text)
{
    
    if (Text.substring (5, 8) == "001")
    {
        DrawText (Text.substring (9, 29), Text.substring (29, 50));
    }
    if (Text.substring (5, 8) == "002")
    {
        DrawText (Text.substring (9, 29), "    " + Text.substring (29, 50));
        delay (250);
        ScrollingMarquee (Text.substring (9, 50));
    }
    if (Text.substring (5, 8) == "004")
    {
        lcd.command (0x1F);
        lcd.clear ();
        delay (250);
        lcd.displayBuf (0);
    }
    if (Text.substring (5, 8) == "003")
    {
        
        byte val = Text.substring (9, 12).toInt ();
        int adress = Text.substring (12, 29).toInt ();
        
        WriteAddress (adress, val);
        if (ReadAddress (adress) == val)
        {
            SoftUart.println ("0001|003|255");
        }
        else
        {
            SoftUart.println ("0001|003|0");
        }
    }
    if (Text.substring (5, 8) == "006")
    {
        RawMicrocode = Text.substring (9, 29);
        lcd.clear ();
        lcd.setCursor (0, 0);
        lcd.print (ReadAddress (RawMicrocode.toInt ()));
    }
    if (Text.substring (5, 8) == "005")
    {
        WriteCommand ("0001", "005", "255");
    }
    
    if (Text.substring (5, 8) == "007")
    {
        RawMicrocode = Text.substring (9, 29);
        DisplayGraphic (RawMicrocode.toInt ());
    }
    
    if (Text.substring (5, 8) == "008")
    {
        int year = 2000 + ReadAddress (410);
        int mont = ReadAddress (411);
        int day = ReadAddress (412);
        int hour = ReadAddress (413);
        int minutes = ReadAddress (414);
        int second = ReadAddress (415);
        Clock.setDateTime (year, mont, day, hour, minutes, second);
        SoftUart.println ("0001|008|255");
    }
    if (Text.substring (5, 8) == "009")
    {
        DataTimer = Clock.getDateTime ();
        RawMicrocode =
                "Dzis jest: " + String (DataTimer.day) + "-" +
                String (DataTimer.month) + "-" + String (DataTimer.year);
        RawMicrocode2 =
                "Godzina:   " + String (DataTimer.hour) + ":" +
                String (DataTimer.minute);
        DrawText (RawMicrocode, RawMicrocode2);
    }
    if (Text.substring (5, 8) == "010")
    {
        WriteAddress (000, 002);
        delay (200);
        DisplayTime ();
    }
    if (Text.substring (5, 8) == "011")
    {
        WriteAddress (000, 000);
    }
    
    
#if DEBUG == 1
    if (Text.substring (5, 8) == "012")
    {
        for (int i = 0; i < 403; i++)
        {
            Serial.println (ReadAddress (i));
            delay (50);
        }
    }
#endif
    
}

void DisplayGraphic (int Data)
{
    lcd.command (0x01);
    lcd.command (0x02);
    lcd.command (0x1F);
    lcd.displayBuf (Data);
    
}

void DisplayTime ()
{
    while (ReadAddress (000) == 002)
    {
        RawMicrocode = SoftUart.readString ();
        ReadCommand (RawMicrocode);
        DataTimer = Clock.getDateTime ();
        RawMicrocode =
                "Dzis jest: " + String (DataTimer.day) + "-" +
                String (DataTimer.month) + "-" + String (DataTimer.year);
        RawMicrocode2 =
                "Godzina: " + String (DataTimer.hour) + ":" +
                String (DataTimer.minute);
        DrawText (RawMicrocode, RawMicrocode2);
        delay (999);
    }
}

void WriteCommand (String UUID, String NumberCommand, String Data)
{
    SoftUart.println (UUID + "|" + NumberCommand + "|" + Data + "\n");
}

void DrawText (String Text_1, String Text_2)
{
    lcd.clear ();
    delayMicroseconds (1000);
    lcd.noDisplay ();
    delayMicroseconds (1000);
    lcd.display ();
    delayMicroseconds (1000);
    lcd.command (0x17);
    delayMicroseconds (1000);
    lcd.command (0x01);
    delayMicroseconds (1000);
    lcd.command (0x02);
    delayMicroseconds (1000);
    delayMicroseconds (1000);
    asm volatile ("    ldi  r18, 136" "\n"
                  "    ldi  r19, 15" "\n"
                  "1:  dec  r19" "\n"
                  "    brne 1b" "\n"
                  "    dec  r18" "\n"
                  "    brne 1b" "\n" "    rjmp 1f" "\n" "1:" "\n");
    
    lcd.setCursor (0, 0);
    delayMicroseconds (1000);
    lcd.print (Text_1);
    delayMicroseconds (1000);
    lcd.setCursor (0, 1);
    delayMicroseconds (1000);
    lcd.print (Text_2);
}
