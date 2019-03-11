#ifndef BackEnd_H
#define BackEnd_H
/**
 * @class BackEnd
 *
 * @brief Klasa zajmująca się Back-Endem aplikacji. Jest to klasa zajmująca się obsługą aplikacji od strony technicznej. Znajdują się w niej główne metody, dzięki którym można stworzyć plik, czy połączyć się z portem COM.
 *
 * @note Klasa zajmująca się Back-Endem aplikacji.
 * Klasa zajmująca się Back-Endem aplikacji. Jest to klasa zajmująca się obsługą aplikacji od strony technicznej. Znajdują się w niej główne metody, dzięki którym można stworzyć plik, czy połączyć się z portem COM.
 *
 */

/// Przestrzeni nazw zajmująca się Back-Endem aplikacji. Jest to klasa zajmująca się obsługą aplikacji od strony technicznej. Znajdują się w niej główne metody, dzięki którym można stworzyć plik, czy połączyć się z portem COM.
#include "librarycollection.h"
#include "FrontEnd.h"
/// Użycie przestrzeni nazw
namespace BackEndSpace
{
class BackEnd: public QObject
{
    /// Stworzenie obiektu dla QT
    Q_OBJECT
public:

    /// Używamy aby zapobiec nie jawnej konwersji typu.
    explicit BackEnd(QObject *parent = nullptr);
    /**
     * Metoda tworzącay dowolny plik
     *@param[in]  type:QString file Nazwa pliku jaki należy stworzyć
     *@return[out] type:bool Zwraca prawdę albo fałsz
     */
    Q_INVOKABLE bool CreateFile(QString file);
    /**
     * Metoda sprawdzająca, czy plik istnieje
     *@param[in]  type:QString file Nazwa pliku
     *@return[out] type:bool Zwraca prawdę albo fałsz
     */
    Q_INVOKABLE bool CheckFileExist(QString file);
    /**
     * Metoda sprawdzająca, czy DLC jest zainstalowane
    * @param[in]  type:AppId_t ID Numer SteamID
     *@return[out] type:bool Zwraca prawdę albo fałsz
     */
    Q_INVOKABLE bool CheckDLCisInstalled(AppId_t ID);
    /**
     * Metoda sprawdzająca, jaki język został ustawiony
     *@return[out] type:QString Zwraca identyfikator  dla odpowiedniego języka
     */
    Q_INVOKABLE QString SteamLang();
    /**
     * Metoda przypisuje do zmiennej RawJsonData całą zawartość pliku Json z odpowiednimi plikami językowymi
	  *@return[out] type:QString Zwraca tekst do przetłumaczenia
	  * @param[in]  type:QString LanguageName nazwa języka
     */
    Q_INVOKABLE void SelectLanguage(QString LanguageName);
    /**
     * Metoda przypisuje do zmiennej RawJsonData całą zawartość pliku Json z odpowiednimi plikami językowymi
     @param[in]  type:QString LanguageName nazwa języka
  *@return[out] type:QJsonDocument Zwraca dump pliku językowego	
	*/
    Q_INVOKABLE void SelectSettingFile(QString LanguageName);
    /**
     * Metoda otwiera plik Json
     * @param[in]  type:QString filename nazwa pliku językowego
     *@return[out] type:QJsonDocument Zwraca dump pliku językowego
     */
    Q_INVOKABLE QJsonDocument OpenJsonFile(QString filename);
    /**
     * Metoda czyta plik Json i wybiera element nie znajdujący się w klasie
     * @param[in]  type:QString SearchName nazwa pliku językowego
     *@return[out] type:QJsonDocument Zwraca odpowiedną wartość z pliku
     */
    Q_INVOKABLE QString SelectFromJson(QString SearchName);
    /**
     * Metoda czyta plik Json i wybiera element <B>znajdujący</B> się w klasie
	  * @param[in]  type:QString NameOfArray nazwa tablicy w pliku językowego
     * @param[in]  type:QString SearchName nazwa elemetnu w tablicy pliku językowego
     *@return[out] type:QJsonDocument Zwraca odpowiedną wartość z pliku
     */
    Q_INVOKABLE QString SelectFromArrayJson(QString NameOfArray, QString SearchName);
    /**
     * Metoda skanuje wszystkie porty COM
     * @param[in]  type:QString ProductID nazwa poszukiwanego produktu o podanym indentyfikatorze produktu
     *@return[out] type:QString Zwraca nazwę portu COM
     */
    Q_INVOKABLE QString ScanCOMPort(QString ProductID);
    /**
     * Metoda inicjalizuje port COM (Otwiera go)
     * @param[in]  type:QString ComPort nazwa portu COM
     * @param[in]  type:QString message wiadomość do przesyłu
     */
    Q_INVOKABLE void InitSendMessageToPort(QString ComPort, QString message);
    /**
     * Metoda Pozwalająca na przesłanie wiadomości do portu COM
     * @param[in]  type:QString ComPort nazwa portu COM
     * @param[in]  type:QString message wiadomość do przesyłu
     */
    Q_INVOKABLE void SendMessageToPort(QString message);
private:
    /// Typ danych QJsonDocument służy do zapisania całego pliku json w postaci raw do zmiennej
    QJsonDocument RawJsonData;
    /// Obiekt do którego przypisuje się ustawienia portu COM
    QSerialPort *SerialPort;
    /// Zmienne QString do obsługi ScanCOMPort
    QString signal_mainpage_comport_string,description;
};
}
#endif // BackEnd_H
