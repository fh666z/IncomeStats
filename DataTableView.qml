import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Item {

    property int tableColumnWidth   : 120
    property int tableMinHeight     : 400
    property int tableNumColumns    : 4
    property int tableMarginSizePx  : 10

    property int     selectedRow
    property date    selectedDate
    property double  selectedAmount
    property variant selectedType
    property string  selectedComment

    TableView {
        id    : dataView

        width : tableColumnWidth * tableNumColumns
        height: tableMinHeight

        focus : true

        model : incomeOrderModel

        alternatingRowColors: true
        backgroundVisible   : true
        headerVisible       : true
        frameVisible        : false
        sortIndicatorVisible: true

        selectionMode: SelectionMode.SingleSelection

        onDoubleClicked : showEditDialog()
        onCurrentRowChanged: setParameters()

        Keys.onPressed: {
            if ((event.key === Qt.Key_Return) || (event.key === Qt.Key_Enter))
              showEditDialog()
            else
                event.consumed = false
        }

        TableViewColumn
        {
            horizontalAlignment: Text.AlignHCenter
            elideMode: Text.ElideMiddle
            role    : "date"
            title   : "Date"
            width   : tableColumnWidth

            delegate: Text {
                text : {
                    if (styleData.row >= 0)
                        styleData.value.toLocaleDateString(Qt.locale())
                    else
                        text = ""
                }
                horizontalAlignment: Text.Center
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
        function setParameters()
        {
            selectedRow = currentRow
            selectedDate = incomeOrderModel.get(selectedRow).date
            selectedAmount = incomeOrderModel.get(selectedRow).amount
            selectedType = incomeOrderModel.get(selectedRow).type
            selectedComment = incomeOrderModel.get(selectedRow).comment
        }
    }
}
