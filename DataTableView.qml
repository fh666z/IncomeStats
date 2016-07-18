import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Item {

    property int tableColumnWidth   : 120
    property int tableMinHeight     : 400
    property int tableNumColumns    : 4
    property int tableMarginSizePx  : 10

    property int     selectedRow    : dataView.currentRow
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

        onDoubleClicked: {
            showEditDialog()
        }

        onClicked : {
            selectedDate = incomeOrderModel.get(selectedRow).date
            selectedAmount = incomeOrderModel.get(selectedRow).amount
            selectedType = incomeOrderModel.get(selectedRow).type
            selectedComment = incomeOrderModel.get(selectedRow).comment
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
                    console.log(model)
                    if ((model !== null) && (model !== undefined))
                        text = model.date.toLocaleDateString(Qt.locale())
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
    }
}
