import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

FileDialog {
    id: importExportDlg
    
    property string operation
    
    title: "Please choose a CSV file to " + operation
    
    folder: shortcuts.home
    modality: Qt.WindowModal
    nameFilters: [ "CSV files (*.csv)"]
    onAccepted: {
        mainWinId.dbImportExportRequest(operation, importExportDlg.fileUrl);
        close();
    }
    onRejected: {
        console.log("Canceled");
        close();
    }
}
