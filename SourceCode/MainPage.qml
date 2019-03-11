import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
Item {
    id: mainPage
    width: 824
    height: 710

    /**
     * Obiekt tworzy połączenie z sygnałem QML. Ustawia dostępność portow COM.
     @param[in] type:int signal_mainpage_comport_int Argument odebrany od sygnału. Zawiera numer rozkazu do wykonania.
     @param[out] typ:string back.setsteamnick() Wywołanie metody z klasy c++ zwraca tekst do aktualizacji lokalizacji językowej.
     @param[out] typ:string back.setslcomportname() Wywołanie metody z klasy c++ zwraca nazwę portu.
     */

    Connections {
        target: back
        onSendCOMPort: {
            set_comstatus(signal_mainpage_comport_int, back.setslangtext(), back.setslcomportname())
        }
    }
    /**
     * Metoda służy do aktualizacji koloru led.
     * @param[in] type:int arg numer rozkazu do wykonania.
     * @param[in] type:string arg1 nazwa do lokalizacji językowej.
      * @param[in] type:string arg2 nazwa portu COM.
     */
    function set_comstatus(arg, arg1, arg2) {
        if (arg === 0) {
            switchLED.text = arg1
            switchOLED.text = arg1
            switchKEYPAD.text = arg1
        } else if (arg === 1) {
            switchLED.checked = true
            switchLED.checkable = false
            switchLED.text = arg1
            textFieldLED.text = arg2
        } else if (arg === 2) {
            switchOLED.checked = true
            switchOLED.checkable = false
            switchOLED.text = arg1
            textFieldOLED.text = arg2
        } else if (arg === 4) {
            groupBoxLed.title = arg1
        } else if (arg === 5) {
            text1Com.text = arg1
            text1Com1.text = arg1
        } else if (arg === 6) {
            text1Led.text = arg1
            text1Led1.text = arg1
        } else if (arg === 7) {
            groupBoxLed1.title = arg1
        }
    }

    GroupBox {
        id: groupBoxLed
        y: 470
        width: 340
        height: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 8
        title: "#ledController"

        Text {
            id: text1Com
            x: 20
            y: 86
            text: qsTr("#COMPots")
            anchors.right: parent.right
            anchors.rightMargin: 240
            font.pixelSize: 12
        }

        Text {
            id: text1Led
            x: 20
            y: 34
            text: qsTr("#Status")
            anchors.right: parent.right
            anchors.rightMargin: 254
            font.pixelSize: 12
        }

        Switch {
            id: switchLED
            x: 76
            y: 18
            text: qsTr("#off")
            anchors.right: parent.right
            anchors.rightMargin: 151
            checkable: false

        }

        Rectangle {
            id: rectangle1
            color: "#ffffff"
            radius: 3
            border.width: 0
            z: -1
            anchors.fill: parent
        }

        TextField {
            id: textFieldLED
            x: 76
            y: 72
            width: 128
            height: 43
            anchors.right: parent.right
            anchors.rightMargin: 112
            enabled: false
        }
    }

    GroupBox {
        id: groupBoxLed1
        x: 476
        y: 470
        width: 340
        height: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 8
        title: "#OLEDController"
        Text {
            id: text1Com1
            x: 20
            y: 86
            text: qsTr("#COMPots")
            anchors.right: parent.right
            anchors.rightMargin: 240
            font.pixelSize: 12
        }

        Text {
            id: text1Led1
            x: 20
            y: 34
            text: qsTr("#Status")
            anchors.right: parent.right
            anchors.rightMargin: 254
            font.pixelSize: 12
        }

        Switch {
            id: switchOLED
            x: 76
            y: 18
            text: qsTr("#off")
            anchors.right: parent.right
            anchors.rightMargin: 151
            checked: false
            checkable: false
        }

        Rectangle {
            id: rectangle3
            color: "#ffffff"
            radius: 3
            anchors.fill: parent
            z: -1
            border.width: 0
        }

        TextField {
            id: textFieldOLED
            x: 76
            y: 72
            width: 128
            height: 43
            text: qsTr("")
            anchors.right: parent.right
            anchors.rightMargin: 112
            enabled: false
        }
    }
}
