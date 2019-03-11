import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 1024
    height: 710
    minimumHeight: 710
    minimumWidth: 1024
    title: qsTr("PC Master Control Center")

    /**
     * Obiekt tworzy połączenie z sygnałem QML. Ustawia nick steam.
     @param[out] type:int set_nick_steam Zwraca zawartość sygnału z FrontEnd.
     @param[in] type: string back.setsteamnick Wywołanie metody z klasy c++ aktualizuje nick steam.
     */
    Connections {
        target: back
        onSendSteamNick: {
            set_nick_steam(back.setsteamnick())
        }
    }
    /**
     * Metoda ustawia nick Steam.
     @param[in] type:string arg Argument odebrany od sygnału zawiera nick steam
    */
    function set_nick_steam(arg) {
        text1.text = arg
    }
    /**
     * Obiekt tworzy połączenie z sygnałem QML. Sprawdza, czy są zainstalowane DLC
     @param[out] set_DLCstatus Zwraca zawartość sygnału z FrontEnd
     @param[in] type:int count Licznik DLC
     @param[in] type:bool back.checkdlc() Wywołanie metody z klasy c++ zwraca true, jeżeli jest zainstalowane DLC
     */
    Connections {
        target: back
        onSendDLCInstalled: {
            set_DLCstatus(count, back.checkdlc())
        }
    }
    /**
     * Metoda aktualizuje dostępność DLC.
     @param[in] type:int arg1 Zwraca numer rozkazu jaki  należy wykonać.
     @param[in] type:bool arg2 Jeżeli prawda ukrywa przycisk z DLC do kupienia.
    */
    function set_DLCstatus(arg1, arg2) {
        if (arg1 === 10) {
            if (arg2) {
                dlc1.visible = false
            } else {
                dlc1.text = "#BuyDLCToUnlck"
                keyboard.enabled = false
                keyboard.checked = true
                keyboardPage.enabled = false
            }
        } else if (arg1 === 11) {
            if (arg2) {
                dlc2.visible = false
            } else {
                dlc2.text = "#BuyDLCToUnlck"
                oled.enabled = false
                oled.checked = true
                pageOled.enabled = false
            }
        } else if (arg1 === 12) {
            if (arg2) {
                dlc3.visible = false
            } else {
                dlc3.text = "#BuyDLCToUnlck"
                led.enabled = false
                led.checked = true
                ledPage.enabled = false
            }
        } else {
            dlc1.visible = false
            dlc2.visible = false
            dlc3.visible = false
            textdlclist.y = 621
            textdlclist.text = "#AllDLC"
        }
    }
    /**
     * Obiekt tworzy połączenie między QML, a C++ dzięki sygnałowi onSendLangTextRightSidebar. Lokalizuje prawy pasek według preferencji językowej.
     @param[out]  set_RightSidebar Zwraca zawartość sygnału z FrontEnd.
     @param[out]  type:int signal_rightsidebar Zwraca numer rozkazu do wykonania.
     @param[in]  type:string back.setslangtext() Wywołanie metody z klasy c++ zwraca string z tekstem do wpisania.
     */
    Connections {
        target: back
        onSendLangTextRightSidebar: {
            set_RightSidebar(signal_rightsidebar, back.setslangtext())
        }
    }

    /**
     * Metoda aktualizuje lokalizacje dla prawego paska.
     @param[in] type:int arg1 Zwraca numer rozkazu jaki  należy wykonać.
     @param[out] type:string arg2 zwraca string z tekstem do wpisania.
    */
    function set_RightSidebar(arg1, arg2) {
        if (arg1 === 1) {
            home.text = arg2
        } else if (arg1 === 2) {
            led.text = arg2
        } else if (arg1 === 4) {
            oled.text = arg2
        } else if (arg1 === 5) {
            textdlclist.text = arg2
        } else if (arg1 === 6) {
            dlc1.text = arg2
        } else if (arg1 === 7) {
            dlc2.text = arg2
        } else if (arg1 === 8) {
            dlc3.text = arg2
        }
    }

    Rectangle {
        id: rectangle
        color: "#f9f9f9"
        anchors.right: rectangle1.left
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        SwipeView {
            id: swipeView
            anchors.fill: parent

            MainPage {
                id: mainPage
                x: 0
                y: 0
            }
            LedPage {
                id: ledPage
                x: 0
                y: 0
            }
            PageOled {
                id: pageOled
                x: 0
                y: 0
            }
        }
    }

    Rectangle {
        id: rectangle1
        x: 824
        width: 200
        color: "#363840"
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        Column {
            id: column
            x: 0
            y: 174
            width: 200
            height: 239
            antialiasing: true
            Layout.alignment: Qt.AlignCenter
            Button {
                id: home
                width: 200
                text: qsTr("#MainPage")
                onClicked: {
                    swipeView.setCurrentIndex(0)
                    home.checked = true
                    led.checked = false
                    oled.checked = false
                }
            }

            Button {
                id: led
                width: 200
                text: qsTr("#LedSettings")
                onClicked: {
                    swipeView.setCurrentIndex(1)
                    home.checked = false
                    led.checked = true
                    oled.checked = false
                }
            }
            Button {
                id: oled
                width: 200
                text: qsTr("#OLEDSettings")
                onClicked: {
                    swipeView.setCurrentIndex(2)
                    home.checked = false
                    led.checked = false
                    oled.checked = true
                }
            }
        }

        Text {
            id: text1
            x: 4
            y: 76
            color: "#ffffff"
            font.family: "Verdana"
            font.pixelSize: 20
        }

        Column {
            id: dlclist
            x: 0
            y: 563
            width: 200
            height: 147

            Button {
                id: dlc1
                width: 200
                text: qsTr("#DLC1")
            }

            Button {
                id: dlc2
                width: 200
                text: qsTr("#DLC2")
            }

            Button {
                id: dlc3
                width: 200
                text: qsTr("#DLC3")
            }
        }

        Text {
            id: textdlclist
            x: 3
            y: 532
            color: "#ffffff"
            font.family: fontAwesome.name
            text: "#buyAnotherDLC"
            font.pixelSize: 20
        }

    }
    FontLoader { id: fontAwesome; source: "qrc:/fontawesome-webfont.ttf" }
}
