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

    Connections {
        target: viewManagerClass
        onNotifyStatus : statusText = status
    }

    contentItem {
        minimumHeight: windowMinHeight
        minimumWidth : windowMinWidth
    }

    menuBar: MainMenu {
        id: mainMenuId
    }

    statusBar: StatusBar {
        id: appStatusBar
        Text {
            id: statusTextId
            text: qsTr(statusText)
        }
    }

    // TableView with all records
    Column {
        id                  : contentColumn
        anchors.fill        : parent
        anchors.topMargin   : dataTableId.tableMarginSizePx
        anchors.leftMargin  : dataTableId.tableMarginSizePx
        padding             : 10

        DataTableView {
            id              : dataTableId
        }
    }

    // Window for order ADD/EDIT
    OrderView {
        id  : оrderWindow
    }

    // Message dialog for errors/warnings
    MessageDialog {
        id          : messageDlg
        title       : "Information"
        icon        : StandardIcon.Information
        modality    : Qt.WindowModal
        onAccepted  : close()
    }

    // Dialog window for selecting file for Import/Export
    ImportExport {
        id: importExportDlg
    }
}



