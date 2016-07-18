import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {

    property int windowOffset   : 50
    property int windowMinWidth : dataTableId.tableColumnWidth * dataTableId.tableNumColumns + 2 * dataTableId.tableMarginSizePx
    property int windowMinHeight: dataTableId.tableMinHeight + windowOffset

    id      : mainWinId
    title   : "Income Stats"
    width   : windowMinWidth
    height  : windowMinHeight
    visible : true

    signal orderViewAcceptButtonPressed(int currentRow, date selectedDate, string amount, variant type, string comment)
    signal deleteRowRequested(int currentRow)

    contentItem {
        minimumHeight: windowMinHeight
        minimumWidth : windowMinWidth
    }

    menuBar: MenuBar {
        id : mainMenuId

        Menu {
            title: "Program"

            MenuItem {
                text    : qsTr("Login")
                shortcut: "Ctrl+L"
                //                onTriggered: mainWinId.color = "blue"
            }

            MenuItem {
                text        : qsTr("Exit")
                shortcut    : StandardKey.Quit
                onTriggered : Qt.quit()
            }
        }
        Menu {
            title: "Contract"
            MenuItem {
                text        : qsTr("Add ..")
                shortcut    : "Ctrl+A"
                onTriggered : newOrderWindow.show()
            }

            MenuItem {
                text        : qsTr("Edit ..")
                shortcut    : "Ctrl+E"
                onTriggered : showEditDialog()
            }

            MenuItem {
                text        : qsTr("Remove")
                shortcut    : "Ctrl+D"
                onTriggered : deleteRowRequested(dataTableId.selectedRow)
            }
        }
    }

    Column {
        id                  : contentColumn
        anchors.fill        : parent
        anchors.topMargin   :  dataTableId.tableMarginSizePx
        anchors.leftMargin  : dataTableId.tableMarginSizePx
        padding             : 10

        DataTableView {
            id : dataTableId
        }
    }

    function enableMainView()
    {
        dataTableId.enabled = true
    }

    function disableMainView()
    {
        dataTableId.enabled = false
    }

    function showEditDialog(){
        if (dataTableId.selectedRow === -1)
        {
            messageDlg.text = "Please select record first before editing!"
            messageDlg.open()
        }
        else
        {
            editOrderWindow.recordIndex = dataTableId.selectedRow
            editOrderWindow.dateChosen  = dataTableId.selectedDate
            editOrderWindow.amountText  = dataTableId.selectedAmount
            editOrderWindow.typeIndex   = incomeTypeModel.getIndexFromString(dataTableId.selectedType)
            editOrderWindow.commentText = dataTableId.selectedComment
            editOrderWindow.show()
        }
    }

    OrderView {
        id              : newOrderWindow
        title           : "Add new ..."
        btnAcceptText   : "Add"
        recordIndex     : -1
    }

    OrderView {
        id              : editOrderWindow
        title           : "Edit Order ..."
        btnAcceptText   : "Edit"
    }

    statusBar: StatusBar {
        id: appStatusBar
        Text {
            id: statusTextId
            text: qsTr("Date: "       + dataTableId.selectedDate.toLocaleDateString(Qt.locale()) +
                       " | Amount: "  + dataTableId.selectedAmount +
                       " | Type: "    + incomeTypeModel.getIndexFromString(dataTableId.selectedType) +
                       " | Comment: " + dataTableId.selectedComment)
        }
    }

    MessageDialog {
        id          : messageDlg
        title       : "Information"
        icon        : StandardIcon.Information
        onAccepted  : close()
    }
}



