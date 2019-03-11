import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
Item {
    id: ledPage
    width: 824
    height: 710
    property variant colors: ["#FF0000", "#00FF00", "#0000FF", "#00A7FF", "#FFE90D", "#FF7500", "#7BFFFF", "#00FF23"]

    /**
     * Obiekt tworzy połączenie między QML, a C++ dzięki sygnałowi onSendLangTextLed. Pozwala na aktualizację diod LED.
     @see set_ledstatus
     @param[in] type:int signal_led Zwraca zawartość sygnału z FrontEnd.
     @param[out] type:string back.setslangtext() Wywołanie metody z klasy c++. Zwraca string z tekstem do tłumaczenia.
     */
    Connections {
        target: back
        onSendLangTextLed: {
            set_ledstatus(signal_led, back.setslangtext())
        }
    }
    /**
     * Metoda lokalizuje stronę do tłumaczenia według preferencji językowej
      @param[in] type:int arg1 Argument odebrany od sygnału. Zawiera numer rozkazu do wykonania.
      @param[in] type:string arg2 Argument odebrany od funkcji C++. Zwiera tekst do przetłumaczenia
    */
    function set_ledstatus(arg1, arg2) {
        if (arg1 === 0) {
            model.get(0).text = arg2
        } else if (arg1 === 1) {
            model.get(1).text = arg2
        } else if (arg1 === 2) {
            model.get(2).text = arg2
        } else if (arg1 === 3) {
            model.get(3).text = arg2
        } else if (arg1 === 4) {
            model.get(4).text = arg2
        } else if (arg1 === 5) {
            model.get(5).text = arg2
        } else if (arg1 === 6) {
            model.get(6).text = arg2
        } else if (arg1 === 7) {
            model.get(7).text = arg2
        } else if (arg1 === 8) {
            groupBox1.title = arg2;
        } else if (arg1 === 9) {
            groupBox2.title = arg2;
        } else if (arg1 === 10) {
            text3.text = arg2
        } else if (arg1 === 11) {
            text4.text = arg2;
        } else if (arg1 === 12) {
            text_setleds.text = arg2;
        } else if (arg1 === 13) {
            button4.text = arg2;
        }
    }
    GroupBox {
        id: groupBox2
        anchors.left: parent.left
        anchors.leftMargin: 62
        anchors.right: parent.right
        anchors.rightMargin: 61
        anchors.top: parent.top
        anchors.topMargin: 342
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 137
        title: qsTr("#ledpage")

        Grid {
            id: grid
            anchors.top: parent.top
            anchors.topMargin: 58
            anchors.left: parent.left
            anchors.leftMargin: 44
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 58
            anchors.right: parent.right
            anchors.rightMargin: 44
            columns: 7
            spacing: 19
            rows: 1

            Rectangle {
                id: led0
                width: 64
                height: 64
                color: "red"
                border.color: "black"
                border.width: 0
                radius: 10
            }

            Rectangle {
                id: led1
                width: 64
                height: 64
                color: "#ff0000"
                radius: 10
                border.width: 0
                border.color: "#000000"
            }

            Rectangle {
                id: led2
                width: 64
                height: 64
                color: "#ff0000"
                radius: 10
                border.width: 0
                border.color: "#000000"
            }

            Rectangle {
                id: led3
                width: 64
                height: 64
                color: "#ff0000"
                radius: 10
                border.width: 0
                border.color: "#000000"
            }

            Rectangle {
                id: led4
                width: 64
                height: 64
                color: "#ff0000"
                radius: 10
                border.width: 0
                border.color: "#000000"
            }

            Rectangle {
                id: led5
                width: 64
                height: 64
                color: "#ff0000"
                radius: 10
                border.width: 0
                border.color: "#000000"
            }

            Rectangle {
                id: led6
                width: 64
                height: 64
                color: "#ff0000"
                radius: 10
                border.width: 0
                border.color: "#000000"
            }

        }

        Rectangle {
            id: rectangle
            color: "#ffffff"
            radius: 3
            border.width: 0
            z: -1
            anchors.fill: parent
        }
    }

    GroupBox {
        id: groupBox1
        height: 200
        anchors.right: parent.right
        anchors.rightMargin: 61
        anchors.left: parent.left
        anchors.leftMargin: 62
        anchors.top: parent.top
        anchors.topMargin: 136
        title: qsTr("#settingsled")
        Item
        {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 153
            anchors.left: parent.left
            anchors.leftMargin: 0
            ComboBox {
                id: comboBoxLed
                x: 125
                y: 18
                editable: true
                model: ListModel {
                    id: model
                    ListElement {
                        text: "elements"
                    }
                    ListElement {
                        text: "elements"
                    }
                    ListElement {
                        text: "elements"
                    }
                    ListElement {
                        text: "elements"
                    }
                    ListElement {
                        text: "elements"
                    }
                    ListElement {
                        text: "elements"
                    }
                    ListElement {
                        text: "elements"
                    }
                    ListElement {
                        text: "elements"
                    }
                }
            }
            Text {
                id: text_setleds
                x: 22
                y: 36
                text: qsTr("#SetColor")
                font.pixelSize: 12
            }
            Button {
                id: button4
                x: 22
                y: 65
                width: 223
                height: 48
                text: qsTr("#Send")
                onClicked: {
                    back.receiveFromLedPage(1, comboBoxLed.currentIndex)
                    changeColorLed(colors[comboBoxLed.currentIndex])
                }
            }
        }

        Rectangle {
            id: rectangle1
            color: "#ffffff"
            radius: 3
            border.width: 0
            z: -1
            anchors.fill: parent
        }

        GroupBox {
            id: groupBoxMemory
            x: 292
            y: 0
            width: 371
            height: 153
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 14
            title: qsTr("Debug")

            TextField {
                id: textFieldAddressMemory
                x: 77
                y: -7
                width: 270
                height: 43
                placeholderText: "12345"
            }

            TextField {
                id: textFieldValueMemory
                x: 77
                y: 37
                width: 48
                height: 43
                placeholderText: "255"
            }

            Button {
                id: button5
                x: 136
                y: 29
                width: 216
                height: 77
                text: qsTr("#SendToCPU")
                onClicked: {
                    back.receiveFromLedPage(textFieldValueMemory.text, textFieldAddressMemory.text)
                }
            }

            Text {
                id: text_value
                x: -6
                y: 47
                text: qsTr("#SetValue")
                font.pixelSize: 12
            }

            Text {
                id: text_address
                x: -6
                y: 7
                width: 54
                height: 15
                text: qsTr("#Setaddres")
                font.pixelSize: 12
            }
        }
    }

    /**
     * Metoda służy do aktualizacji koloru led.
     * @param[in] type:string arg Kolor zapisany w kodzie szesnastkowym.
     */
    function changeColorLed(arg) {
        led0.color = arg;
        led1.color = arg;
        led2.color = arg;
        led3.color = arg;
        led4.color = arg;
        led5.color = arg;
        led6.color = arg;
    }
}
