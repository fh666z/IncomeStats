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

    signal deleteRowRequested(int currentRow)
    signal dbImportExportRequest(string operation, string outFile)

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
            text: qsTr("")
        }
        Timer {
            id          : statusClearTimerId
            interval    : 3000
            running     : false
            repeat      : false
            onTriggered :  statusTextId.text = ""
        }
    }
    Connections {
        target: viewManagerClass
        onNotifyStatus : {
            statusTextId.text = status
            statusClearTimerId.start()
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
        property bool exitAfterClose

        id          : messageDlg
        title       : "Information"
        icon        : StandardIcon.Information
        modality    : Qt.WindowModal
        onAccepted  : {
            if (exitAfterClose)
                Qt.quit()
            else
                close()
        }
    }
    Connections {
        target: viewManagerClass
        onNotifyError : {
            messageDlg.text = errText
            messageDlg.detailedText = errDetailedText
            messageDlg.exitAfterClose = shouldExit
            messageDlg.open()
        }
    }

    // Dialog window for selecting file for Import/Export
    ImportExport {
        id: importExportDlg
    }
}



