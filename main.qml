import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {

    property int windowOffset   : 50
    property int windowMinWidth : dataTableId.tableColumnWidth * dataTableId.tableNumColumns + 2 * dataTableId.tableMarginSizePx
    property int windowMinHeight: dataTableId.tableMinHeight + windowOffset

    property string statusText

    id      : mainWinId
    title   : "Income Stats"
    width   : windowMinWidth
    height  : windowMinHeight
    visible : true


    signal orderViewAcceptButtonPressed(int currentRow, date selectedDate, string amount, variant type, string comment)
    signal deleteRowRequested(int currentRow)
    signal dbExportRequest(string outFile)

    contentItem {
        minimumHeight: windowMinHeight
        minimumWidth : windowMinWidth
    }

    menuBar: MenuBar {
        id : mainMenuId

        Menu {
            title: "&Program"

            MenuItem {
                text    : qsTr("&Login")
                shortcut: "Ctrl+L"
            }

            MenuItem {
                text    : qsTr("&Import Data")
                shortcut: "Ctrl+I"
                onTriggered: importExportFileDlg.open()
            }

            MenuItem {
                text    : qsTr("E&xport Data")
                shortcut: "Ctrl+X"
                onTriggered: {
                    importExportDlg.selectExisting = false
                    importExportDlg.operation = "export"
                    importExportDlg.open()
                }
            }

            MenuItem {
                text        : qsTr("E&xit")
                shortcut    : StandardKey.Quit
                onTriggered : Qt.quit()
            }
        }
        Menu {
            title: "Income &Order"
            MenuItem {
                text        : qsTr("&Add ..")
                shortcut    : "Ctrl+A"
                onTriggered : newOrderWindow.show()
            }

            MenuItem {
                text        : qsTr("&Edit ..")
                shortcut    : "Ctrl+E"
                onTriggered : showEditDialog()
            }

            MenuItem {
                text        : qsTr("&Remove")
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
            id          : dataTableId
        }
    }

    onNotifyUIStatus {
        statusText = "Shano"
    }


    statusBar: StatusBar {
        id: appStatusBar
        Text {
            id: statusTextId
            text: qsTr(statusText)
        }
    }

    OrderView {
        id              : newOrderWindow
        title           : "Add new ..."
        btnAcceptText   : "Add"
        //recordIndex     : -1
    }

    OrderView {
        id              : editOrderWindow
        title           : "Edit Order ..."
        btnAcceptText   : "Edit"
    }

    MessageDialog {
        id          : messageDlg
        title       : "Information"
        icon        : StandardIcon.Information
        modality    : Qt.WindowModal
        onAccepted  : close()
    }

    FileDialog {
        id: importExportDlg

        property string operation

        title: "Please choose a CSV file to " + operation

        folder: shortcuts.home
        modality: Qt.WindowModal
        nameFilters: [ "CSV files (*.csv)"]
        onAccepted: {
            mainWinId.dbExportRequest(importExportDlg.fileUrl)
            close()
        }
        onRejected: {
            console.log("Canceled")
            close()
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
}



