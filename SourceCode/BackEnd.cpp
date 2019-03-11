#include "BackEnd.h"
using namespace BackEndSpace;
BackEnd::BackEnd(QObject *parent):
    QObject(parent)
{
}

bool BackEnd::CreateFile(QString FileName)
{
    ///Przypisuje ściężkę danych do folderu aplikacji.
    QString FilePath=qApp->applicationDirPath()+"/"+FileName;
    ///Sprawdza, czy plik istnieje, jeśli nie to go tworzy.
    if(!CheckFileExist(FilePath))
    {
        /// Przygotowanie do zapisania pliku.
        QFile WriteFile(FilePath);
        /// Sprawdzanie, czy jest dostęp do edycji pliku.
        if(WriteFile.open(QFile::Append | QFile::Text))
        {
            /// Zapisywanie pliku
            QTextStream in(&WriteFile);
            in << "";
        }
        /// Zamykanie pliku
        WriteFile.close();
        /// Sprawdzanie, czy plik został poprawnie zapisany.
        return CheckFileExist(FilePath);
    }
    else
    {
        return false;
    }
}
bool BackEnd::CheckFileExist(QString FileName)
{
    /// Sprawdzanie, czy plik istnieje.
    QFileInfo CheckFile(FileName);
    if (CheckFile.exists() && CheckFile.isFile()) {
        /// Jeśli tak, to zwraca prawdę
        return true;
    } else {
        /// Jeśli nie, to zwraca fałsz
        return false;
    }
}

bool BackEnd::CheckDLCisInstalled(AppId_t ID)
{
    /// Sprawdzanie, czy DLC jest zainstalowane dzięki SteamAPI.
    if(SteamApps()->BIsDlcInstalled(ID))
    {
        /// Jeśli tak, to zwraca prawdę
        return true;
    }
    else
    {
        /// Jeśli nie, to zwraca fałsz
        return false;
    }

}
QString BackEnd::SteamLang()
{
    /// Zwracanie ustawionego języka dzięki SteamAPI.
    return SteamApps()->GetCurrentGameLanguage();
}


void BackEnd::SelectLanguage(QString LanguageName)
{
    /// Otwieranie całego pliku Json i zapisywanie jego zawartości do zmiennej <B>RawJsonData</B>.
    RawJsonData=OpenJsonFile(LanguageName);
}

void BackEnd::SelectSettingFile(QString LanguageName)
{
    /// Otwieranie całego pliku Json i zapisywanie jego zawartości do zmiennej <B>RawJsonData</B>.
    RawJsonData=OpenJsonFile(LanguageName);
}
QJsonDocument BackEnd::OpenJsonFile(QString FileName)
{
    QString Data;
    QFile File;
    ///Przypisuje ściężkę danych do folderu aplikacji.
    File.setFileName(qApp->applicationDirPath()+"/"+FileName);
    /// Sprawdzanie, czy jest dostęp do czytania pliku.
    File.open(QIODevice::ReadOnly | QIODevice::Text);
    /// Zapisuje całą zawartość pliku do zmiennej Data.
    Data = File.readAll();
    /// Zamyka plik JSON.
    File.close();
    /// Przypisuje zmiennej RawData zawartość pliku i koduje do UTF-8.
    QJsonDocument RawData = QJsonDocument::fromJson(Data.toUtf8());
    return RawData;
}

QString BackEnd::SelectFromJson(QString SearchName)
{
    /// Przypisuje zmiennej <b>sett2</b> zawartość obiektu pliku językowego.
    QJsonObject sett2 = RawJsonData.object();
    /// Zwraca szukaną zawartość obiektu.
    return sett2[SearchName].toString();
}
QString BackEnd::SelectFromArrayJson(QString nazwaarray, QString nazwaposzukiwana)
{
    /// Przypisuje zmiennej <b>sett2</b> zawartość obiektu pliku językowego.
    QJsonObject obj2 = RawJsonData.object();
    /// Zwraca obiekt tablicy o podanej nazwie.
    QJsonObject finalObject = obj2[nazwaarray].toObject();
    /// Zwraca szukaną zawartość obiektu.
    QString text = finalObject[nazwaposzukiwana].toString();
    return text;
}

QString BackEnd::ScanCOMPort(QString ProductID)
{
    /// Sprawdzenie dostępnych portów.
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    /// Jeżeli nie znaleziono portu, to przypisuje wartość 0.
    const QString blankString = QObject::tr("0");
    /// Pętla do sprawdzenia wszystkich portów COM.
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        ///Przypisanie do zmiennej <b>description</b> numeru indentyfikacyjnego urządzenia.
        description=(serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString);
        ///Przypisanie do zmiennej <b>signal_mainpage_comport_string</b> numeru portu COM urządzenia.
        signal_mainpage_comport_string=serialPortInfo.portName();
        if(ProductID==description)
        {
            ///Zwraca numeru portu COM urządzenia.
            return signal_mainpage_comport_string;
        }
    }
    return "COM0";
}

void BackEnd::InitSendMessageToPort(QString ComPort, QString message)
{
    /// Użycie obiektu do połączenia się z urządzeniem i ustawienie wymaganych parametrów.
    SerialPort = new QSerialPort;
    SerialPort->setPortName(ComPort);
    SerialPort->setBaudRate(4800);
    SerialPort->setDataBits(QSerialPort::Data8);
    SerialPort->setFlowControl(QSerialPort::NoFlowControl);
    SerialPort->setStopBits(QSerialPort::OneStop);
    SerialPort->setParity(QSerialPort::NoParity);
    SerialPort->open(QIODevice::ReadWrite);

}

void BackEnd::SendMessageToPort(QString message)
{
    /// Użycie obiektu do wysłania wiadomości do urządzenia.
    SerialPort->write(message.toUtf8());
}
