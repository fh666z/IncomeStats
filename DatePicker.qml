import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: datePickerWindow
    title: "Choose Date ..."

    flags: Qt.FramelessWindowHint | Qt.Window | Qt.SubWindow
    modality: Qt.WindowModal

    width: calendar.implicitWidth
    height: calendar.implicitHeight

    property date calendarDate: calendar.selectedDate

    Item {
        anchors.fill: parent
        focus: true
        Keys.onEscapePressed: datePickerWindow.close()
    }

    Calendar {
        id: calendar

        weekNumbersVisible: true
        minimumDate: "2000-01-01"
        maximumDate: "2100-01-01"

        navigationBarVisible: true
        frameVisible: true

        visible: true
        onDoubleClicked: close()
    }


}
