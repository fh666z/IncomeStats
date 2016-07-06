import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

import CPPEnums 1.0


Window {
    id: winId

    title: "Add new income order..."

    width : 400
    height : 300

    modality: Qt.WindowModal

    Column {
        anchors.centerIn: parent

        Row {
            padding : 5
            spacing : 10

            GroupBox {
                id: dateGroup
                title: qsTr("Date:")

                implicitWidth: 250

                TextField {
                    id: dateDialog

                    anchors.fill: parent

                    text: datePicker.selectedDate.toLocaleDateString(Qt.locale())
                    horizontalAlignment: Text.Center

                    MouseArea {
                        anchors.fill: parent
                        onClicked: datePicker.visible = true
                    }
                }
            }
        }

        Row {
            padding : 5
            spacing : 10

            GroupBox {
                id: amountGroup
                title: qsTr("Amount:")

                implicitWidth: 250

                TextField {
                    id: amountDialog
                    anchors.fill: parent
                    horizontalAlignment: Text.Center

                    validator: DoubleValidator {
                        top : 100000.0
                        bottom: 0.0
                    }
                }
            }
        }
        Row {
            padding : 5
            spacing : 10

            GroupBox {
                id: typeGroup
                title: qsTr("Type:")

                implicitWidth: 250

                ComboBox {
                    model : IncomeType
                }

            }
        }
    }

    Calendar {
        id: datePicker

        minimumDate: "2000-01-01"
        maximumDate: "2100-01-01"

        navigationBarVisible: true
        frameVisible: true

        visible: false
        onDoubleClicked: visible = false
    }

    function callbackFunction() {
        console.log("Date chosen: " + dateDialog.year + " " + dateDialog.month + " " + dateDialog.day )
    }
}
