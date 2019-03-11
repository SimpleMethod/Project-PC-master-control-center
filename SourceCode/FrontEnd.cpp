#include "FrontEnd.h"
using namespace BackEndSpace;
using namespace FrontEndSpace;
BackEnd functionbox,led,oled;
FrontEnd::FrontEnd(QObject *parent) :
    QObject(parent)
{
}

void FrontEnd::receiveFromLedPage(int option,int value)
{
    ///Inicjalizacja portu LED.
    if(init_led==0)
    {
        led.InitSendMessageToPort(COMPORT1,"00");
    }
    init_led=1;
    ///Wysłanie wiadomości do portu.
    led.SendMessageToPort(QStringLiteral("0000|00%1|%2").arg(option).arg(Leds_Color[value]));
}

void FrontEnd::receiveFromOledPage(int option,QString OLED)
{
    ///Inicjalizacja portu OLED.
    if(init_oled==0)
    {
        oled.InitSendMessageToPort(COMPORT2,"01");
    }
    init_oled=1;
    ///Wysłanie wiadomości do portu.
    oled.SendMessageToPort(QStringLiteral("0000|00%1|%2\n").arg(option).arg(OLED));
}

QString FrontEnd::setsteamnick(){
    /// Przy użyciu steam api mamy możliwość pobrać nick, który ustawiamy.
    return SteamFriends()->GetPersonaName();
}
bool FrontEnd::checkdlc(){
    ///Przypisanie wartości, czy DLC jest zainstalowane z BackEnd.
    DLCisInstalated=functionbox.CheckDLCisInstalled(iddlc);
    return DLCisInstalated;
}

QString FrontEnd::setslangtext(){
    ///Zwaraca przetłumaczony tekst.
    return langtext;
}
QString FrontEnd::setslcomportname(){
    ///Zwraca port COM.
    return signal_mainpage_comport_string;
}
void FrontEnd::initialization_QML()
{
    ///Ładuje plik językowy.
    functionbox.SelectSettingFile(functionbox.SteamLang()+".lang");
}
void FrontEnd::initialization_QML_MAIN()
{
    ///Inicjalizuje poprzez załadowanie pliku JSON.
    initialization_QML();
    ///Przypisanie portu COM do zmiennej <B>COMPORT1</B> Gdzie indentyfikator sprzętu wynosi <B>1</B>.
    COMPORT1=functionbox.ScanCOMPort("1");
    ///Przypisanie portu COM do zmiennej <B>COMPORT2</B> Gdzie indentyfikator sprzętu wynosi <B>2</B>.
    COMPORT2=functionbox.ScanCOMPort("2");
    ///Przypisanie nazwy tablicy poszukiwanej na <B>MainPage</B> dla pliku językowego.
    NameOfArray="MainPage";
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"switchoff");
    signal_mainpage_comport_string="";
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    const QString blankString = QObject::tr("0");
    QString description;
    sendCOMPort(0);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"switchon");

    ///Sprawdza, które port COM są dostępne
    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description=(serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString);
        signal_mainpage_comport_string=serialPortInfo.portName();
        if(description=="1")
        {
            sendCOMPort(1);
        }
        else if(description=="2")
        {
            sendCOMPort(2);
        }
    }

    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ControllerLedSetting");
    sendCOMPort(4);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"COMPorts");
    sendCOMPort(5);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"Status");
    sendCOMPort(6);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ControllerOledSetting");
    sendCOMPort(7);
}
void FrontEnd::initialization_QML_RIGHTBAR()
{
    NameOfArray="RightSidebar";
    initialization_QML();
    bool dlc1,dlc2,dlc3;
    sendSteamNick(12);
    iddlc=740421;
    sendDLCInstalled(10);
    iddlc=710910;
    sendDLCInstalled(11);
    iddlc=740420;
    sendDLCInstalled(12);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"LockedDLC");
    sendLangTextRightSidebar(5);
    dlc1=functionbox.CheckDLCisInstalled(740421);dlc2=functionbox.CheckDLCisInstalled(710910);dlc3=functionbox.CheckDLCisInstalled(740420);
    if(dlc1 && dlc2 && dlc3)
    {
        sendDLCInstalled(14);
        langtext=functionbox.SelectFromArrayJson(NameOfArray,"UnlockedAllDLC");
        sendLangTextRightSidebar(5);
    }
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ButtonMainPage");
    sendLangTextRightSidebar(1);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ButtonLEDSettingsPage");
    sendLangTextRightSidebar(2);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ButtonKeyPadSettingsPage");
    sendLangTextRightSidebar(3);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ButtonOLEDSettingsPage");
    sendLangTextRightSidebar(4);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"DLC1");
    sendLangTextRightSidebar(6);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"DLC2");
    sendLangTextRightSidebar(7);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"DLC3");
    sendLangTextRightSidebar(8);

}

void FrontEnd::initialization_QML_LED()
{
    NameOfArray="LedPage";
    initialization_QML();
    for(int i=0; i<=7;i++)
    {
        langtext=functionbox.SelectFromArrayJson(NameOfArray,"LedColor"+ QString::number(i));
        sendLangTextLed(i);
    }
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"GroupBox1Title");
    sendLangTextLed(8);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"GroupBox2Title");
    sendLangTextLed(9);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ActivationStatus");
    sendLangTextLed(10);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"CurrentColor");
    sendLangTextLed(11);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"SetColor");
    sendLangTextLed(12);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"Send");
    sendLangTextLed(13);
}
void FrontEnd::initialization_QML_OLED()
{
    NameOfArray="OledPage";
    initialization_QML();
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"ControllerOledSetting");
    sendLangTextOled(0);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"OperatingMode");
    sendLangTextOled(1);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"SendButton");
    sendLangTextOled(2);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"PlaceholderText");
    sendLangTextOled(3);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"Combobox_1");
    sendLangTextOled(4);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"Combobox_2");
    sendLangTextOled(5);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"Combobox_3");
    sendLangTextOled(6);
    langtext=functionbox.SelectFromArrayJson(NameOfArray,"DisplayDate");
    sendLangTextOled(7);
}
