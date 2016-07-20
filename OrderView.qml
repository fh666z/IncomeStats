import QtQml 2.2
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import CPPEnums 1.0

Window {
    id          : orderWindowId
    objectName  : "OrderViewObj"

    flags: Qt.Dialog | Qt.Window
    modality: Qt.WindowModal

    minimumWidth: mainGroup.implicitWidth
    minimumHeight: mainGroup.implicitHeight

    width: mainGroup.implicitWidth
    height: mainGroup.implicitHeight

    signal acceptButtonPressed(int currentRow, date selectedDate, string amount, variant type, string comment)

    property string btnAcceptText
    property int    recordIndex
    property date   dateChosen  : datePickerId.calendarDate
    property string amountText  : ""
    property int    typeIndex   : 0
    property string commentText : ""

    Item {
        anchors.fill: parent
        focus: true
        Keys.onEscapePressed: orderWindowId.close()
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
                        id: dateDialogId

                        property date selectedDate: dateChosen

                        anchors.fill: parent
                        horizontalAlignment: Text.Center
                        style: defaultFieldStyle
                        text: dateChosen.toLocaleDateString(Qt.locale())
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
                        id                  : amountFieldId
                        anchors.fill        : parent
                        horizontalAlignment : Text.Center
                        style               : defaultFieldStyle
                        text                : amountText

                        onActiveFocusChanged: {
                            if ((focus === true) && (style === warningFieldStyle)) {
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
                        id              : typeCombo
                        model           : incomeTypeModel
                        anchors.centerIn: parent
                        currentIndex    : typeIndex
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
                        id: commentTextId
                        anchors.fill: parent
                        text: commentText
                    }
                }
            }
            Row{
                spacing : 10
                padding : 5
                topPadding: 20
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: btnAccept
                    objectName: btnAcceptText

                    text: qsTr(btnAcceptText)
                    Keys.onReturnPressed: handleAccept()
                    Keys.onEnterPressed: handleAccept()
                    onClicked: handleAccept()

                    function handleAccept()
                    {
                        if (amountFieldId.text === "")
                        {
                            // Validate amount field
                            amountFieldId.style = warningFieldStyle
                            amountFieldId.text = "Please fill an amount"
                            amountFieldId.focus = false
                        }
                        else
                        {
                            acceptButtonPressed(recordIndex, dateDialogId.selectedDate,
                                                amountFieldId.text, typeCombo.currentIndex+1,
                                                commentTextId.text)
                            close()
                        }
                    }
                }

                Button {
                    id: btnCancel
                    text: qsTr("Cancel")
                    Keys.onReturnPressed: close()
                    Keys.onEnterPressed: close()
                    onClicked: close()
                }
            }
        }
    }

    Component {
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

    Component {
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
        onCalendarDateChanged: dateChosen = calendarDate
    }

    function showAddDialog(){
        title           = "Add new ...";
        btnAcceptText   = "Add";
        recordIndex     =  -1;
        show();
    }

    function showEditDialog(){
        if (dataTableId.selectedRow === -1)
        {
            messageDlg.text = "Please select record first before editing!";
            messageDlg.open();
        }
        else
        {
            title           = "Edit Order ...";
            btnAcceptText   = "Edit";
            recordIndex = dataTableId.selectedRow;
            dateChosen  = dataTableId.selectedDate;
            amountText  = dataTableId.selectedAmount;
            typeIndex   = incomeTypeModel.getIndexFromString(dataTableId.selectedType);
            commentText = dataTableId.selectedComment;
            show();
        }
    }
}

