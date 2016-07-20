import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

MenuBar {
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
            onTriggered: {
                importExportDlg.selectExisting = true
                importExportDlg.operation = "import"
                importExportDlg.open()
            }
        }
        
        MenuItem {
            text    : qsTr("E&xport Data")
            shortcut: "Ctrl+X"
            onTriggered: {
                importExportDlg.selectExisting = false;
                importExportDlg.operation = "export";
                importExportDlg.open();
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
            onTriggered : оrderWindow.showAddDialog()
        }
        
        MenuItem {
            text        : qsTr("&Edit ..")
            shortcut    : "Ctrl+E"
            onTriggered : оrderWindow.showEditDialog()
        }
        
        MenuItem {
            text        : qsTr("&Remove")
            shortcut    : "Ctrl+D"
            onTriggered : deleteRowRequested(dataTableId.selectedRow)
        }
    }
}
