import QtQml 2.2
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import CPPEnums 1.0

Window {
    id: winId

    flags: Qt.Dialog | Qt.Window
    modality: Qt.WindowModal

    width: mainGroup.implicitWidth
    height: mainGroup.implicitHeight

    property string btnAddEditText

    Item {
        anchors.fill: parent
        focus: true
        Keys.onEscapePressed: winId.close()
    }

    GroupBox {
        id: mainGroup
        title: qsTr("Income Order")

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
                        horizontalAlignment: Text.Center
                        style: defaultFieldStyle

                        text: datePickerId.calendarDate

                        MouseArea {
                            anchors.fill: parent
                            onClicked: datePickerId.show()
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
                        id: amountField
                        anchors.fill: parent
                        horizontalAlignment: Text.Center
                        style : defaultFieldStyle

                        onActiveFocusChanged: {
                            if (focus) {
                                text = ""
                                style = defaultFieldStyle
                            }
                        }

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
                        id: typeCombo
                        model : incomeTypeModel
                        anchors.centerIn: parent
                    }
                }
            }

            Row {
                id: commentRow
                padding : 5
                spacing : 10

                GroupBox {
                    id: commentGroup
                    title: qsTr("Comment:")

                    implicitWidth: 250

                    TextArea {
                        id: commentText
                        anchors.fill: parent
                        text: ""
                    }
                }
            }
            Row{
                spacing : 10
                padding : 5
                topPadding: 20
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: btnAddEdit
                    text: qsTr(btnAddEditText)
                    onClicked: {
                        if (amountField.text === "")
                        {
                            // Validate amount field
                            amountField.style = warningFieldStyle
                            amountField.text = "Please fill an amount"
                            amountField.focus = false
                        }
                    }
                }

                Button {
                    id: btnCancel
                    text: qsTr("Cancel")
                    onClicked: close()
                }
            }
        }
    }

    Component
    {
        id: defaultFieldStyle
        TextFieldStyle {
            textColor: "black"
            background: Rectangle {
                radius: 3
                border.color: "#333"
                border.width: 1
            }
        }
    }

    Component
    {
        id: warningFieldStyle
        TextFieldStyle {
            textColor: "red"
            background: Rectangle {
                radius: 3
                border.color: "red"
                border.width: 2
            }
        }
    }

    DatePicker {
        id: datePickerId

    }

}






