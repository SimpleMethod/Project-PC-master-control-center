import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
Item {
    id: pageOled
    width: 824
    height: 710
    
    /**
     * Obiekt tworzy połączenie z sygnałem QML. Pozwala na aktualizację wyświetlacza OLED.
     @param[in] type:int signal_oled Argument odebrany od sygnału. Zawiera numer rozkazu do wykonania.
     @param[out] typ:string back.setsteamnick() Wywołanie metody z klasy c++ zwraca tekst do aktualizacji lokalizacji językowej.
     */
    Connections {
        target: back
        onSendLangTextOled: {
            set_oledstatus(signal_oled, back.setslangtext())
        }
    }
    /**
     * Metoda set_oledstatus służy do aktualizacji lokalizacji językowej.
     * @param[in] type:int arg1 numer rozkazu do wykonania.
     * @param[out]  type:string arg2 nazwa do lokalizacji językowej.
     */
    function set_oledstatus(arg1, arg2) {
        if (arg1 === 0) {
            groupBox1.title = arg2
        } else if (arg1 === 1) {
            text2.text = arg2
        } else if (arg1 === 2) {
            button4.text = arg2
        } else if (arg1 === 3) {
            textField.placeholderText = arg2
        } else if (arg1 === 4) {
            model.get(0).text = arg2
        } else if (arg1 === 5) {
            model.get(1).text = arg2
        } else if (arg1 === 6) {
            model.get(2).text = arg2
        } else if (arg1 === 7) {
            button5.text = arg2
        }
    }
    
    GroupBox {
        id: groupBox1
        y: 255
        height: 259
        anchors.left: parent.left
        anchors.leftMargin: 62
        anchors.right: parent.right
        anchors.rightMargin: 61
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 196
        title: "#oledsettings"
        
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
            x: 312
            y: 30
            width: 354
            height: 153
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 29
            anchors.right: parent.right
            anchors.rightMargin: 11
            title: qsTr("Debug")

            TextField {
                id: textFieldAddressMemory
                x: 77
                y: -7
                width: 253
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
                id: button9
                x: 136
                y: 29
                width: 194
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
        Item {
            id: item1
            y: 6
            width: 369
            height: 200
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 6

            ComboBox {
                id: comboBoX1
                x: 101
                y: 6
                editable: true
                model: ListModel {
                    id: model
                    ListElement {
                        text: "#text"
                    }
                    ListElement {
                        text: "#graphic"
                    }
                    ListElement {
                        text: "#timer"
                    }
                }
                onCurrentIndexChanged: {
                    if (comboBoX1.currentIndex >= 1) {
                        itemText.visible = false
                    } else {
                        itemText.visible = true
                    }

                    if(comboBoX1.currentIndex==1)
                    {
                        back.receiveFromOledPage(7,"202")
                    }else if(comboBoX1.currentIndex==2)
                    {
                        back.receiveFromOledPage(9,"")
                    }
                }
            }

            Text {
                id: text2
                x: 9
                y: 22
                text: qsTr("#text/graphic")
                font.pixelSize: 12
            }

            Item {
                id: itemText
                x: 8
                y: 56
                width: 200
                height: 200

                TextField {
                    id: textField
                    x: 0
                    y: 0
                    width: 224
                    height: 43
                    placeholderText: "Podaj tekst do wysłania"
                }

                Button {
                    id: button4
                    x: 230
                    y: -2
                    text: qsTr("#send")
                    onClicked: {
                        back.receiveFromOledPage(1,textField.text)
                    }
                }

                Button {
                    id: button5
                    x: 0
                    y: 35
                    text: qsTr("#displaydata")
                    onClicked: {
                        back.receiveFromOledPage(9,"")
                    }
                }
            }
        }
    }
}
