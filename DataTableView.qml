import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Item {

    property int tableColumnWidth   : 120
    property int tableMinHeight     : 400
    property int tableNumColumns    : 4
    property int tableMarginSizePx  : 10

    width : parent.width
    height: parent.height

    TableView {
        id    : dataView

        width : tableColumnWidth * tableNumColumns
        height: tableMinHeight

        model: incomeOrderModel

        anchors.top     : parent.top
        anchors.bottom  : parent.bottom
//        anchors.left    : parent.left
        anchors.margins : tableMarginSizePx

        alternatingRowColors: true
        backgroundVisible   : true
        headerVisible       : true
        frameVisible        : false
        sortIndicatorVisible: true

        selectionMode: SelectionMode.SingleSelection

        TableViewColumn
        {
            horizontalAlignment: Text.AlignHCenter
            elideMode: Text.ElideMiddle
            role    : "date"
            title   : "Date"
            width   : tableColumnWidth

            delegate: Component {
                Text {
                    text: model.date.toLocaleDateString(Qt.locale(), Locale.ShortFormat)
                    horizontalAlignment: Text.Center
                }
            }
        }
        TableViewColumn
        {
            horizontalAlignment: Text.AlignHCenter
            elideMode: Text.ElideMiddle
            role    : "amount"
            title   : "Amount"
            width   : tableColumnWidth
        }
        TableViewColumn
        {
            horizontalAlignment: Text.AlignHCenter
            elideMode: Text.ElideMiddle
            role    : "type"
            title   : "Type"
            width   : tableColumnWidth
        }
        TableViewColumn
        {
            horizontalAlignment: Text.AlignHCenter
            elideMode: Text.ElideMiddle
            role    : "comment"
            title   : "Comment"
            width   : tableColumnWidth
        }

        headerDelegate: BorderImage
                        {
                            source: "images/header.png"
                            border{left:2;right:2;top:2;bottom:2}
                            Text {
                                text : styleData.value
                                anchors.centerIn : parent
                                color:"#333"
                            }
                        }
    }
}
