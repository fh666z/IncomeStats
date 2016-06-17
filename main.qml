import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Income Stats"

    DataTableView {
        id : dataTable
    }

    statusBar: StatusBar {
        id: appStatusBar

    }
}
