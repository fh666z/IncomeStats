import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Item {
    width: parent.width
    height: parent.height

    property int dataRowHeight : 40

    ListView {
        anchors.fill: parent

        highlight: highlight
        highlightFollowsCurrentItem: false

        spacing: 10

        clip: true
        model: incomeOrderModel
        delegate: Row{
            width: parent.width
            height: dataRowHeight

            anchors.left: parent.left
            padding: 10

            StyledDataText {text: id}
            StyledDataText {text: amount }
            StyledDataText {text: date}
            StyledDataText {text: type}
            StyledDataText {text: comment}
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                Qt.quit();
            }
        }
    }

    Component {
        id: highlight
        Rectangle {
            width: parent.width; height: dataRowHeight
            radius: 3
            border {
                color : "lightsteelblue"
                width: 2
            }

            y: list.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }
}
