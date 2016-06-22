import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


ApplicationWindow {

    property int windowOffset   : 50
    property int windowMinWidth : dataTable.tableColumnWidth * dataTable.tableNumColumns + 2 * dataTable.tableMarginSizePx
    property int windowMinHeight: dataTable.tableMinHeight + windowOffset

    id      : mainWinId
    title   : "Income Stats"
    width   : windowMinWidth
    height  : windowMinHeight
    visible : true

    contentItem {
        minimumHeight: windowMinHeight
        minimumWidth : windowMinWidth
    }

    menuBar: MenuBar {
        id : mainMenu

        Menu {
            title: "File"
            MenuItem {text: "File"}
            MenuItem {text: "New"}
            MenuItem {text: "Open"}
        }
    }

    Column {
        id : mainViewColumn
        anchors.fill : parent

        DataTableView {
            id : dataTable
        }
    }

    statusBar: StatusBar {
        id: appStatusBar
        Text {
            id: statusTextId
            text: qsTr("Height: " + mainViewColumn.height)
        }

    }
}

