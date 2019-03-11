#ifndef FrontEnd_H
#define FrontEnd_H
/**
 * @class FrontEnd
 *
 * @brief Klasa zajmująca się Front-Endem aplikacji. Jest to klasa zajmująca się obsługą aplikacji od strony wizualnej. Znajdują się w niej główne metody, dzięki którym można komunikować się z JavaScript.
 *
 * @note Klasa zajmująca się Front-Endemaplikacji.
 * Klasa zajmująca się Front-Endem aplikacji. Jest to klasa zajmująca się obsługą aplikacji od strony wizualnej. Znajdują się w niej główne metody, dzięki którym można komunikować się z JavaScript.
 *
 */

///Przestrzeni nazw zajmująca się Front-Endem aplikacji. Jest to klasa zajmująca się obsługą aplikacji od strony wizualnej. Znajdują się w niej główne metody, dzięki którym można komunikować się z JavaScript.

#include "BackEnd.h"
/// Użycie przestrzeni nazw.
namespace FrontEndSpace
{
class FrontEnd : public QObject
{
    /// Stworzenie obiektu dla QT.
    Q_OBJECT
private:
    /// Zmienna, w której zapisane są adresy dla pamięci eeprom ledów.
    int Leds_Color[11]={10,34,58,82,106,130,154,178,202,226,250};
    /// Zmienna, w której zapisany jest status zainstalowanego DLC.
    bool DLCisInstalated;
    /// Zmienna, w której zapisany ID DLC.
    AppId_t iddlc;
    /// Zmienna, w której zapisywany jest tekst do przetłumaczenia.
    QString langtext;
    /// Zmienne wymagane do przesyłania numeru sygnału do JavaScript.
    int signal_led,signal_mainpage,signal_rightsidebar,send_led,signal_oled,signal_keypad,count;
    /// Zmienne do przesyłu aktualnej nazwy potu COM.
    QString signal_mainpage_comport_string;
    /// Zmienne do przesyłu aktualnejgo numeru potu COM.
    int signal_mainpage_comport_int;
    /// Zmienne służące do przechowywania portu COM, oraz nazwy tablicy w pliku językowym.
    QString COMPORT1,COMPORT2,OLED,NameOfArray;
    /// Inicjalizacja portu LED.
    bool init_led=0;
    /// Inicjalizacja portu OLED.
    bool init_oled=0;
public:
    /// Używamy aby zapobiec nie jawnej konwersji typu.
    explicit FrontEnd(QObject *parent = nullptr);
    /**
         * Metoda ustawia nick w JavaScript.
         *@return type:QString Zwraca nick steam.
    */
    Q_INVOKABLE QString setsteamnick();
    /**
         * Metoda ustawia pole językowe w JavaScript.
         *@return type:QString Zwraca polę w którym jest tekst do tłumaczenia.
    */
    Q_INVOKABLE QString setslangtext();
    /**
         * Metoda ustawia port COM w JavaScript.
         *@return type:QString Zwraca nazwę portu COM.
    */
    Q_INVOKABLE QString setslcomportname();
    /**
         * Metoda ustawia DLC w JavaScript.
         *@return type:bool Zwraca prawdę jeśli DLC jest zainstalowane.
    */
    Q_INVOKABLE bool checkdlc();
    /**
         * Metoda inicjalizuje JavaScript poprzez załadowanie pliku językowego.
    */
    Q_INVOKABLE void initialization_QML();
    /**
         * Metoda zarządza stroną główną, sprawdza, czy porty COM są dostępne oraz tłumaczy ją na określony język.
    */
    Q_INVOKABLE void initialization_QML_MAIN();
    /**
         * Metoda zarządza prawym paskiem, sprawdza, czy DLC są zainstalowane oraz tłumaczy ją na określony język.
    */
    Q_INVOKABLE void initialization_QML_RIGHTBAR();
    /**
         * Metoda zarządza stroną LED tłumaczy ją na określony język.
    */
    Q_INVOKABLE void initialization_QML_LED();
    /**
         * Metoda zarządza stroną OLLED tłumaczy ją na określony język.
    */
    Q_INVOKABLE void initialization_QML_OLED();

signals:
    /**
         * Sygnał wysyła rozkaz zwarty w zmiennej <B>count</B> do JavaScript i zapisuje Steam nick.
    */
    void sendSteamNick(int count);
    /**
         * Sygnał wysyła rozkaz zwarty w zmiennej <B>count</B> do JavaScript i jest aktywne jeśli DLC jest zainstalowane.
    */
    void sendDLCInstalled(int count);
    /**
         * Sygnał wysyła rozkaz zwarty w zmiennej <B>signal_led</B> do JavaScript. Ten sygnał zajmuje się tłumaczeniem i zarządzaniem strony LED.
    */
    void sendLangTextLed(int signal_led);
    /**
         * Sygnał wysyła rozkaz zwarty w zmiennej <B>signal_rightsidebar</B> do JavaScript. Ten sygnał zajmuje się tłumaczeniem i zarządzaniem prawym paskiem.
    */
    void sendLangTextRightSidebar(int signal_rightsidebar);
    /**
       * Sygnał wysyła rozkaz zwarty w zmiennej <B>signal_mainpage_comport_int</B> do JavaScript. Ten sygnał zajmuje się tłumaczeniem i zarządzaniem głównym oknem. Dodatkowo zajmuje się przypisaniem portów COM.
    */
    void sendCOMPort(int signal_mainpage_comport_int);
    /**
       * Sygnał wysyła rozkaz zwarty w zmiennej <B>signal_oled</B> do JavaScript. Ten sygnał zajmuje się tłumaczeniem i zarządzaniem oken OLED.
    */
    void sendLangTextOled(int signal_oled);
public slots:
    /**
       * Slots zajmuje się odebraniem danych ze strony OLED JavaScript i przekazaniem ich do C++.
       * @param[out]  type:int option Zwraca numer rozkazu do wykonania.
       * @param[out]  type:QString OLED Zwraca zawartość rozkazu do wykonania.
    */
    void receiveFromOledPage(int option,QString OLED);
    /**
       * Slots zajmuje się odebraniem danych ze strony LED JavaScript i przekazaniem ich do C++.
       * @param[out]  type:int option Zwraca numer rozkazu do wykonania.
       * @param[out]  type:int value Zwraca zawartość rozkazu do wykonania.
    */
    void receiveFromLedPage(int option,int value);
};
}
#endif // FrontEnd_H
