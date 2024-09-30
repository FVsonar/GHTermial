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
    property real dmr_opacity : 0.3

    signal hasModeChangedtoDMR(int row);
    rows: 2
    columns:2
    rowSpacing: 2
    columnSpacing: 2

    property  var combox_VFO: ["VFA", "VFB","A=B"]
    property  var combox_Split: ["ON", "OFF"]
    property  var combox_Dmode: ["USB", "LSB","CWR","CWL","AM","WFM","NFM","DIGI","FT8","DMR"]
    property var combox_Ctcss: ["None", "67.0", "69.3", "71.9",  "74.4",  "77.0",  "79.7",  "82.5",  "85.4",  "88.5",
                                "91.5", "94.8", "97.4", "100.0", "103.5", "107.2", "110.9", "114.8", "118.8", "123.0",
                                "127.3","131.8","136.5","141.3", "146.2", "150.0", "151.4", "156.7", "159.8", "162.2",
                                "165.5","167.9","171.3","173.8", "177.3", "179.9", "183.5", "186.2", "189.9", "192.8",
                                "196.6","199.5","203.5","206.5", "210.7", "213.8", "218.1", "221.3", "225.7", "229.1",
                                "233.6","237.1","241.8","245.5", "250.3", "254.1"]
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

        ListElement { headerText: "A_B"}
        ListElement { headerText: "SPLIT"}
        ListElement { headerText: "VFA_MODE"}
        ListElement { headerText: "VFB_MODE"}
        ListElement { headerText: "T_CTCSS"}
        ListElement { headerText: "R_CTCSS"}

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

    function is_Mode_DMR(index)
    {
        var isDMR = false;
        if(index < table.model.rowCount)
        {
            if((table.model.rows[index].VFA_MODE === 9) || (table.model.rows[index].VFB_MODE === 9))
            {
                isDMR = true;
            }
        }
        return isDMR
    }

    function set_ReadWriteList(index,state)
    {
        Cpp_DataProc.setReadWriteList(index,state)
    }

    function set_ReadWriteListAll(state)
    {
        var rw_index ;
        for(rw_index=0;rw_index<100;rw_index++)
        {
            Cpp_DataProc.setReadWriteList(rw_index,state)
        }
//        console.log("set_ReadWriteListAll")
//         console.log(rw_index)

    }

    Component.onCompleted: {
        root.hasModeChangedtoDMR.connect(onHasModeChangedtoDMR)
        set_ReadWriteListAll(_checkAll.checked?1:0)
    }

    RoundRect {
        id: corner
        width: rowHeader.width
        height: columnHeader.height
        color:  "#EEEDA1"
        visible: true
        topLeftCorner: true
        CheckBox {
                   checked: true
                   id: _checkAll
                   state: checked ? "checked" : "noCheck"
                   anchors {
                       verticalCenter: parent.verticalCenter
                       left: parent.left
                       leftMargin: 1
                   }
                   onCheckStateChanged: {
                      var ischeck;
                      ischeck =  (_checkAll.checked == true)?1:0;
                      root.set_ReadWriteListAll(ischeck);
                   }

        }
        Text {
            text: _checkAll.checked?"ALL":"NONE"
            anchors.verticalCenter: _checkAll.verticalCenter
            anchors.left: _checkAll.right
            font.bold: true
           // anchors.centerIn: parent
        }
        radius: height  / 4
    }
    // 横向表头
    ResizableColumnHeader {
        id: columnHeader
        Layout.fillWidth: true
        height: root.defaultRowHeight
        defaultWidth: root.defaultColumnWidth
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
        width: 70
        spacing: 1
        clip: true
        model: 100//table.rows
        delegate: HeaderDelegate {
            height: root.defaultRowHeight
            width: rowHeader.width   
           // text: index + 1
            horizentalAlignment: Text.AlignRight

            CheckBox {
                       checked: true
                       id: _checkSingal //此ID不能外部访问
                       state: checked ? "checked" : "noCheck"
                       anchors {
                           verticalCenter: parent.verticalCenter
                           left: parent.left
                           leftMargin: 1
                       }
                       Connections{
                           target: _checkAll
                           function  onCheckedChanged(){                           
                                _checkSingal.checked = _checkAll.checked? true:false;

                             }
                       }
                       onCheckedChanged: {
//                           if(index <= table.model.rowCount)  //如果超出了就需要用channel 增加 放到cpp 判断
//                           {
                               var ischeck;
                               ischeck =  (_checkSingal.checked == true)?1:0;
                               root.set_ReadWriteList(index,ischeck);
//                           }
                       }
            }
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
       columnWidthProvider: columnHeader.columnWidthProvider
       rowHeightProvider: function (column) {return root.defaultRowHeight}
       ScrollBar.horizontal:   ScrollBar { orientation: Qt.Horizontal }
       ScrollBar.vertical:     ScrollBar { }


       //定义列roles 此处放到上一层了
     // model: root.model

       //定义行代理 和 model连接
       delegate: DelegateChooser {
                role : "display"
           DelegateChoice{   // Channel
             column: 0
             delegate: Rectangle {
                 implicitWidth: root.defaultColumnWidth
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
                   placeholderText: "439770000"
                   selectByMouse: true
                   onTextEdited:  model.display = this.text
               }
           }
           DelegateChoice { //VFB_FREQ
               column: 3
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "439770000"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
               }
           }



           DelegateChoice{  //A_B
               column: 4
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model: combox_VFO
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }

           DelegateChoice { //SPLIT
               column: 5
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model: combox_Split
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }
           DelegateChoice { //VFA_MODE
               column: 6
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model: combox_Dmode
                   onActivated:
                   {
                       display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                       root.hasModeChangedtoDMR(row);
                   }
               }
           }

           DelegateChoice { //VFB_MODE
               column: 7
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model: combox_Dmode
                   onActivated:
                   {
                       display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                       root.hasModeChangedtoDMR(row);
                   }
               }
           }
           DelegateChoice { //T_CTCSS
               column: 8
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model: combox_Ctcss                     
                   onActivated:
                   {
                       display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                       root.hasModeChangedtoDMR(row);
                   }
               }
           }


           DelegateChoice { //R_CTCSS
               column: 9
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model: combox_Ctcss
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
               }
           }

           DelegateChoice{  //call_type
               column: 10
               delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   id: _CB_call
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_calltype

                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }
           DelegateChoice { //tx_cc
               column: 11
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice { //rx_cc
               column: 12
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }
           DelegateChoice {  // slot_num
               column: 13
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 2
                   stepSize: 1
                   onValueModified: model.display = this.value
                   opacity : is_Mode_DMR(row)?1.0:0.3
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : 0.3
                            })
                        }
                    }
               }
           }

           DelegateChoice { //call_id
               column: 14
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "call_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice { //owm_id
               column: 15
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   placeholderText: "own_id"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice {  //ch_type
               column: 16
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_chtype
                   onActivated: display = this.currentIndex// we've only used 'display' keyword, because combobox model doesnt have this as role name
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }
           DelegateChoice { // rxctcss
               column: 17
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_ctcss
                   onActivated: display = this.currentIndex// we've only used 'display' keyword, because combobox model doesnt have this as role name
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice {  // txctcss
               column: 18
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_ctcss
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice { //SQL
               column: 19
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }
           DelegateChoice { //SPK
               column: 20
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }
           DelegateChoice { //RX_GAIN
               column: 21
               delegate: SpinBox {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   value: model.display
                   from: 0; to: 15
                   stepSize: 1
                   onValueModified: model.display = this.value
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice { //ENCRY
               column: 22
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
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice {
               column: 23
               delegate:  TextField {
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   text: model.display
                   enabled: isEncryEnable
                   placeholderText: "XXXX"
                   selectByMouse: true
                   onTextEdited: model.display = this.text
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

           DelegateChoice { //BS_MODE
               column: 24
               delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                   implicitWidth: columnHeader.defaultWidth
                   implicitHeight: root.defaultRowHeight
                   currentIndex: display
                   model:combox_bsmode
                   onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                   opacity : is_Mode_DMR(row)?1.0:dmr_opacity
                   Component.onCompleted: {
                       root.hasModeChangedtoDMR.connect(changOwnopacity)
                   }

                    function changOwnopacity(rowindex)
                    {
                        if(row === rowindex )
                        {
                            opacity = Qt.binding(function() {
                            return is_Mode_DMR(row) ? 1.0 : dmr_opacity
                            })
                        }
                    }
               }
           }

       }

    }

}

