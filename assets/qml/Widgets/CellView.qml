import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

import Qt.labs.qmlmodels 1.0
import "../delegate"




GridLayout {
    id: root
    property int defaultRowHeight : 30
    property int defaultColumnWidth: 70
    property bool readonly: false
    property bool intteractive: true

    property bool isEncryEnable: false   //加密是否使能
  //  property alias delegate: table.delegate
    property alias  model : table.model

    rows: 2
    columns:2
    rowSpacing: 2
    columnSpacing: 2

    // 与columnheader中不需要显示的项保持一致
    property int ex_start :4
    property int ex_stop : 9

    property  var combox_calltype: ["Single", "Group","All"]

    property  var combox_chtype: ["DMR", "DFM"]
    property  var combox_ctcss: ["OFF", "67.0Hz"]
    property  var combox_bsmode: ["BS", "MS"]

    ListModel {
        id: headerModel
        ListElement { headerText: "CHANNEL"}

        ListElement { headerText: "NAME"}
        ListElement { headerText: "VFA_FREQ"}
        ListElement { headerText: "VFB_FREQ"}

//        ListElement { headerText: "A_B"}
//        ListElement { headerText: "SPLIT"}
//        ListElement { headerText: "VFA_MODE"}
//        ListElement { headerText: "VFB_MODE"}
//        ListElement { headerText: "T_CTCSS"}
//        ListElement { headerText: "R_CTCSS"}

        ListElement { headerText: "CALL_TYPE"}
        ListElement { headerText: "TX_CC"}
        ListElement { headerText: "RX_CC"}
        ListElement { headerText: "SLOT"}
        ListElement { headerText: "CALL_ID"}
        ListElement { headerText: "OWN_ID"}
        ListElement { headerText: "CH_TYPE"}
        ListElement { headerText: "RX_CTCSS"}
        ListElement { headerText: "TX_CTCSS"}
        ListElement { headerText: "SQL"}
        ListElement { headerText: "SPK"}
        ListElement { headerText: "RX_GAIN"}
        ListElement { headerText: "ENCRY"}
        ListElement { headerText: "SEED"}
        ListElement { headerText: "BSMODE"}
    }


    RoundRect {
        id: corner
        width: rowHeader.width
        height: columnHeader.height
        color:  "#EEEDA1"
        visible: true
        topLeftCorner: true
        Text {
            text: "Index"
            font.bold: true
            anchors.centerIn: parent
        }
        radius: height  / 4
    }


    // 横向表头
    ResizableColumnHeader {
        id: columnHeader
        Layout.fillWidth: true
        height: root.defaultRowHeight
        defaultWidth: columnHeader.defaultWidth
        spacing: 1
        model: headerModel

        contentX: table.contentX
        interactive: false
        onColumnWidthChanged: table.forceLayout()

    }

    // 竖向表头
    ListView {
        id: rowHeader
        Layout.fillHeight: true
        width: 50
        spacing: 1
        clip: true
        model: table.rows
        delegate: HeaderDelegate {
            height: root.defaultRowHeight
            width: rowHeader.width
            text: index + 1
            horizentalAlignment: Text.AlignRight
        }
        contentY: table.contentY
        interactive: false
    }

    // Table本体
    TableView {
       id: table
       Layout.fillWidth: true
       Layout.fillHeight: true
       columnSpacing: 1
       rowSpacing: 1
       clip: true
       columnWidthProvider:
           function (column)
           {
               if (column < root.ex_start)
               {
                   return   columnHeader.columnWidthProvider(column)
               }
               else  if (column<= root.ex_stop)
               {
                    return 0
               }
                else
               {
                    return   columnHeader.columnWidthProvider(column - 6)
               }
           }
       rowHeightProvider: function (column) {return root.defaultRowHeight}
       ScrollBar.horizontal:   ScrollBar { orientation: Qt.Horizontal }
       ScrollBar.vertical:     ScrollBar { }


       //定义列roles 此处放到上一层了
     //  model: root.model

       //定义行代理 和 model连接
       delegate: DelegateChooser {

           DelegateChoice{   // Channel
             column: 0
             delegate: Rectangle {
                 implicitWidth: columnHeader.defaultWidth
                 implicitHeight: root.defaultRowHeight
                 border.width: 0
                 color: "#21373F"
                 Text {
                     text:  index
                     color: "white"
                     anchors.centerIn: parent
                     onTextChanged: model.display = index;
                 }
            }
           }
           DelegateChoice { //NAME
               column: 1
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "call_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }

           DelegateChoice { //VFA_FREQ
               column: 2
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "call_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }
           DelegateChoice { //VFB_FREQ
               column: 3
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "call_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }

           DelegateChoice{  column: 4 ;delegate: Item {}}
           DelegateChoice{  column: 5 ;delegate: Item {}}
           DelegateChoice{  column: 6 ;delegate: Item {}}
           DelegateChoice{  column: 7 ;delegate: Item {}}
           DelegateChoice{  column: 8 ;delegate: Item {}}
           DelegateChoice{  column: 9 ;delegate: Item {}}

           DelegateChoice { //VFB_FREQ
               column: 9
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "call_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }




           DelegateChoice{  //call_type
               column: ex_stop + 1
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_calltype
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }

           DelegateChoice { //tx_cc
               column: ex_stop + 2
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
               }
           }

           DelegateChoice { //rx_cc
               column: ex_stop + 3
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
               }
           }
           DelegateChoice {  // slot_num
               column: ex_stop + 4
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 2
                   stepSize: 1
                   onValueModified: model.display = this.value
               }
           }

           DelegateChoice { //call_id
               column: ex_stop + 5
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "call_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }

           DelegateChoice { //owm_id
               column: ex_stop + 6
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "own_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }

           DelegateChoice {  //ch_type
               column: ex_stop + 7
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_chtype
                   onActivated: display = this.currentIndex// we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }
           DelegateChoice { // rxctcss
               column: ex_stop + 8
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_ctcss
                   onActivated: display = this.currentIndex// we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }

           DelegateChoice {  // txctcss
               column: ex_stop + 9
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_ctcss
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }

           DelegateChoice { //SQL
               column: ex_stop + 10
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
               }
           }
           DelegateChoice { //SPK
               column: ex_stop + 11
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
               }
           }
           DelegateChoice { //RX_GAIN
               column: ex_stop + 12
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
               }
           }

           DelegateChoice { //ENCRY
               column: ex_stop + 13
               delegate: Rectangle
               {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   border.width: 0
                   color: "#21373F"
                   CheckBox {
                      checkState: model.display
                      onToggled: model.display = isEncryEnable?this.checkState:0;
                    }
               }
           }

           DelegateChoice {
               column: ex_stop + 14
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   enabled: isEncryEnable
                   placeholderText: "XXXX"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }

           DelegateChoice { //BS_MODE
               column: ex_stop + 15
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_bsmode
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }

       }

    }

}

