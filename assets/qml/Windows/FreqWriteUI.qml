import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.qmlmodels 1.0
import "../Widgets"


Rectangle{
    id: root
    visible: true
    color: "#aaa"

    property int active_page_index: 0
    property bool is_reading: false
    property bool is_sending: false
    signal sentStartSignal(string str);
    signal sentLoadChannelSignal();
    property int readcount:0xff;

    MessageDialog {
           id: _mesDialog
           title: "Message"
           icon: StandardIcon.Information
           text: "?"
           standardButtons: StandardButton.Yes //|StandardButton.No

           Component.onCompleted: visible = false

//           onYes: console.log("YES")
//           onNo: console.log("NO")
//           onRejected: console.log("Close")
       }



    TableModel {
       id: tablemodel
         TableModelColumn{ display: "CHANNEL"   }

         //BASIC
         TableModelColumn{ display: "NAME"      }
         TableModelColumn{ display: "VFA_FREQ"  }
         TableModelColumn{ display: "VFB_FREQ"  }
         TableModelColumn{ display: "A_B"       }
         TableModelColumn{ display: "SPLIT"     }
         TableModelColumn{ display: "VFA_MODE"  }
         TableModelColumn{ display: "VFB_MODE"  }
         TableModelColumn{ display: "T_CTCSS"   }
         TableModelColumn{ display: "R_CTCSS"   }

         // DMR
         TableModelColumn{ display: "CALL_TYPE" }
         TableModelColumn{ display: "TX_CC"     }
         TableModelColumn{ display: "RX_CC"     }
         TableModelColumn{ display: "SLOT"      }
         TableModelColumn{ display: "CALL_ID"   }
         TableModelColumn{ display: "OWN_ID"    }
         TableModelColumn{ display: "CH_TYPE"   }
         TableModelColumn{ display: "RX_CTCSS"  }
         TableModelColumn{ display: "TX_CTCSS"  }
         TableModelColumn{ display: "SQL"       }
         TableModelColumn{ display: "SPK"       }
         TableModelColumn{ display: "RX_GAIN"   }
         TableModelColumn{ display: "ENCRY"     }
         TableModelColumn{ display: "SEED"      }
         TableModelColumn{ display: "BSMODE"    }

         // checked
      //   TableModelColumn{ display: "CHECKED"    }


    }

    function startAutoConnect()
    {
        Cpp_AutoConn.startConnDevive();
    }

    function load_channelParam()
    {
        if(root.is_reading == false)
        {
            console.log("load channel start")
            Cpp_DataProc.loadChannelParamater()
            tablemodel.clear()
            root.is_reading = true
        }
    }

    function sent_table_model(str)
    {
        if(root.is_sending == false)
        {
         Cpp_DataProc.parseTableJsonArry(str)
        }
    }

    function get_SentCount()
    {
        var progress;
        progress = Cpp_DataProc.getSendCount();

        progress = (Math.round( progress / 100 * 100) / 100.00); //
//        console.log("progress is")
//        console.log(progress)

        return  progress;
    }

    function get_ReadCount()
    {
        var progress;
        progress = Cpp_DataProc.getReadCount();

        progress = (Math.round( progress / 100 * 100) / 100.00); //
//        console.log("progress is")
//        console.log(progress)

        return  progress;
    }

    function startWriteData(data){

    }

    function stopload()
    {
        Cpp_DataProc.stopLoad();
    }

    function appand_tableModleFromCpp(){
        var row_data = {
            CHANNEL: 0,
            NAME: "RENAME",
            VFA_FREQ: "439770000",
            VFB_FREQ: "439770000",
            A_B:   0,
            SPLIT: 0,
            VFA_MODE: 0,
            VFB_MODE: 0,
            T_CTCSS: 0,
            R_CTCSS: 0,
            CALL_TYPE: 0,
            TX_CC: 1,
            RX_CC: 1,
            SLOT: 0,
            CALL_ID: "12",
            OWN_ID: "34",
            CH_TYPE: 0,
            RX_CTCSS: 0,
            TX_CTCSS: 0,
            SQL:  1,
            SPK:  8,
            RX_GAIN: 80,
            ENCRY: 0,
            SEED: "0",
            BSMODE: 0,
         //   CHECKED: 1
        }
        var readcount;
        var jsonObject ;
        var tempString;     
        var parse_ret;
        var channel_num ;
        readcount = Cpp_DataProc.getReadCount();
        tempString =  Cpp_DataProc.getJsonArrayFromByte()
//        console.log("Channel value:");
//        console.log(tempString);
//        console.log("readcount:");
//        console.log(readcount);

//               console.log("Josn Count");
//              console.log( countBak);   
            if (tempString !== "NONE")
            {
                try {
                 jsonObject = JSON.parse(tempString,parse_ret);
                }catch(err)
                {
                    console.log("Josn Parse err!");
                     console.log(tempString);
                }

                if (parse_ret)
                {
                      console.log("Josn Parse err!");
                     console.log(tempString);
                     tablemodel.appendRow(row_data)
                }
                else
                {
                    channel_num = jsonObject["CHANNEL"];
                    if (channel_num !== root.readcount)
                    {
//                        console.log("Channel value:",channel_num);
//                        console.log("Channel bak:",root.readcount);
                        root.readcount = channel_num;
                        if (readcount < 100)
                        {
                            //    tablemodel.insertRow(readcount,row_data);
                            // tablemodel.setRow(channel_num,jsonObject);
                            if(channel_num >= tablemodel.rowCount) {
                                for(let i = tablemodel.rowCount; i < channel_num; i++)
                                {
                                    row_data.CHANNEL = i;
                                    tablemodel.appendRow(row_data)
                                }
                            }

                            tablemodel.setRow(channel_num,jsonObject);

                        }
//                        else{
//                            countBak = 0xff;
//                            channel_bak = 0xff;
//                        }
                    }

                }

            }
    }

    //更新model
    function update_table_model(new_rows_number)
    {
        var row_data = {
            CHANNEL: 0,
            NAME: "RENAME",
            VFA_FREQ: "439770000",
            VFB_FREQ: "439770000",
            A_B:   0,
            SPLIT: 0,
            VFA_MODE: 0,
            VFB_MODE: 0,
            T_CTCSS: 0,
            R_CTCSS: 0,
            CALL_TYPE: 0,
            TX_CC: 1,
            RX_CC: 1,
            SLOT: 0,
            CALL_ID: "12",
            OWN_ID: "34",
            CH_TYPE: 0,
            RX_CTCSS: 0,
            TX_CTCSS: 0,
            SQL:  1,
            SPK:  8,
            RX_GAIN: 80,
            ENCRY: 0,
            SEED: "0",
            BSMODE: 0,
         //   CHECKED:1
        }

        if(new_rows_number === 0 || isNaN(new_rows_number)){
            tablemodel.clear()
        }
        else if  (new_rows_number <= 99)
        {
            if(new_rows_number > tablemodel.rowCount) {
                for(let i = tablemodel.rowCount; i < new_rows_number; i++)
                {
                    row_data.CHANNEL = i;
                    tablemodel.appendRow(row_data)
                }
            }
            else if(new_rows_number < tablemodel.rowCount){
                tablemodel.removeRow(new_rows_number,tablemodel.rowCount - new_rows_number)
            }
        }
    }

    Timer {
        id: _checkTimer
        interval: 8000
        repeat: false
        running: false

        onTriggered: {
            var state  = 0;
           state = Cpp_AutoConn.getconnState();
            if(state == 3)
            {
                _mesDialog.text =  "Connect Device Failed!!";
                _mesDialog.open();

            }
        }
    }

    Component.onCompleted: {
        root.sentStartSignal.connect(sent_table_model)
        root.sentLoadChannelSignal.connect(load_channelParam)
        root.update_table_model(10)
        //root.startAutoConnect()  会闪退 测试完恢复
        //_checkTimer.start();测试完恢复
        //调试用
       // root.sentStartSignal.connect(display_table_model)
    }


    function display_table_model()
    {

        console.log ("row is:")
        console.log(tablemodel.rows[0].CALL_TYPE);
    }


        // file dialog to pick json File
    FileDialog {
        id: filedialog
        title: "select a json file"
        folder: shortcuts.documents
        nameFilters: ["Json (*.json)"]
        onAccepted: {
            // updates model with json data
            tablemodel.rows = JSON.parse(Cpp_JsonUtils.getFileContent(filedialog.fileUrl))
            // updating textfield value
            rowsnumber.text = tablemodel.rowCount
            //  100 最好改成宏定义或者 默认参数
            if (100 < tablemodel.rowCount){
                        tablemodel.removeRow(new_rows_number,tablemodel.rowCount - new_rows_number)
                    }

        }

    }


     Column {
          height: parent.height; width: parent.width
          spacing : 3

          Rectangle {
            id : header_rec
            height :50
            width: parent.width
            border.width: 1
            color: "#333333"





           RowLayout {   //Todo 添加 增加  减少  按钮
                spacing: 10
                height: parent.height
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

//                Button {
//                    id: _dmrviewBT
//                    text: _tableviewDMR.visible?"BASIC":"DMR"
//                    onClicked: {

////                            if ( _tableviewDMR.visible)
////                            {
////                               _tableviewDMR.visible = false;
////                                _tableviewBasic.visible = true;
////                            }
////                            else
////                            {
////                               _tableviewDMR.visible = true;
////                                _tableviewBasic.visible = false;
////                            }
//                    }
//                }


                Label {
                    text: "Channel："
                    color: "white"
                }
                TextField {
                    id: rowsnumber
                    text: "0"
                    selectByMouse: true
                    validator: IntValidator{}
                    onEditingFinished: update_table_model(parseInt(this.text))
                }
                Button {
                    text: qsTr("Save File")
                    //passing table model data as string to bankend
                    onClicked: {
                        Cpp_JsonUtils.saveJson(JSON.stringify(tablemodel.rows))
                    }
                }
                Button {
                    text: qsTr("Load File")
                    onClicked: filedialog.open()  // dialog to select json file
                }

                Button {
                    id: read_bt
                    implicitWidth: 80
                    flat: false
                    font.bold: true
                    opacity: enabled ? 1 : 0.9
                    icon.color: palette.buttonText
                    Layout.leftMargin: 5
                    //checked: Cpp_Serial_Manager.connected
                    enabled: (Cpp_Serial_Manager.connected && (root.is_sending == false))

                    palette.buttonText: enabled ? "#2eed5c" : "#d72d60"
                    text: qsTr("READ")
                    //passing table model data as string to bankend
                    onClicked: {
                      //  Cpp_JsonUtils.saveJson(JSON.stringify(tablemodel.rows))


                     //   var jsonObject = JSON.parse(Cpp_DataProc.getJsonArrayFromByte());
                      //  console.log("cpp QJsonObject is",jsonObject);
                      //  console.log("Channel value:",jsonObject["CHANNEL"]);

//                        var tempobject = {
//                            "name": "222"
//                        }
//                        console.log("cpp QJsonObject is",tempobject);
//                        console.log("Channel value:",tempobject["name"]);
                        if(root.is_reading == false)
                        {
                            emit: sentLoadChannelSignal();
                            _sent_read_timer.start();
                            _sent_read_pb.value = 0;
                            //root.is_reading = true;
                        }
                        else
                        {
                            _sent_read_timer.stop();
                            _sent_read_pb.value = 0;
                            stopload();
                            root.is_reading = false;
                        }
                    }
                    icon.source: "qrc:/icons/save.svg"
                    Behavior on opacity {NumberAnimation{}}
                }



                Button {
                    id: sent_bt
                    implicitWidth: 80
                    flat: false
                    font.bold: true
                    opacity: enabled ? 1 : 0.9
                    icon.color: palette.buttonText
                    Layout.leftMargin: 5
                    //checked: Cpp_Serial_Manager.connected
                    enabled: (Cpp_Serial_Manager.connected && (root.is_reading == false))

                    palette.buttonText: enabled ? "#2eed5c" : "#d72d60"
                    text:  qsTr("SEND")
                    //icon.source: checked ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"
                    onClicked: {                         
                            emit: sentStartSignal(JSON.stringify(tablemodel.rows))
                            _sent_read_timer.start();
                            _sent_read_pb.value = 0;
                            root.is_sending = true;
                    }
                    icon.source: "qrc:/icons/send.svg"
                    Behavior on opacity {NumberAnimation{}}
                }


                ProgressBar {
                    id: _sent_read_pb
                    implicitWidth: 90
                    value: 0
                    Timer {
                        id: _sent_read_timer
                        interval: 200
                        repeat: true
                        running: false

                        onTriggered: {

                            if ( Cpp_Serial_Manager.connected == false)
                            {
                                stop()
                                root.is_sending = false;
                                root.is_reading = false;
                                _sent_read_pb.value = 0;                       
                            }

                            if (_sent_read_pb.value < 1)
                            {

                                if(root.is_reading == true)
                                {
                                    appand_tableModleFromCpp();
                                      _sent_read_pb.value = root.get_ReadCount();
                                }
                                else
                                {
                                     _sent_read_pb.value = root.get_SentCount();
                                }
                            }
                            else
                            {
                                stop();
                                _mesDialog.text = root.is_sending?"Send complete": "Read complete";

                                root.is_sending = false;
                                root.is_reading = false;

                                _mesDialog.open()
                            }

                        }

                     }
                }


                ComboBox {
                                id: _portCombo
                                Layout.minimumWidth: 120
                                Layout.maximumWidth: 160
                                Layout.leftMargin: 5
                                model: Cpp_Serial_Manager.portList
                                currentIndex: Cpp_Serial_Manager.portIndex
                                onCurrentIndexChanged: {
                                    if (currentIndex !== Cpp_Serial_Manager.portIndex)
                                        Cpp_Serial_Manager.portIndex = currentIndex
                                }
                            }
                //
                // Connect/disconnect button
                //
                Button {

                    implicitWidth: 120
                    flat: false
//                    icon.width: 20
//                    icon.height: 20
                    font.bold: true
                    opacity: enabled ? 1 : 0.5

                    icon.color: palette.buttonText
                    Layout.leftMargin: 5
                    checked: Cpp_Serial_Manager.connected
                    enabled: Cpp_Serial_Manager.configurationOk
                    onClicked: Cpp_Serial_Manager.toggleConnection()
                    palette.buttonText: checked ? "#d72d60" : "#2eed5c"
                    text: (checked ? qsTr("Disconnect") : qsTr("Connect")) + " "
                    icon.source: checked ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"

                    Behavior on opacity {NumberAnimation{}}
                }

                Rectangle{
                           id: _device_status
                           anchors.leftMargin: 20
                           color: Cpp_Serial_Manager.connected?"#32CD32":"#BC1717"
                           width: 20
                           height: 20
                           radius: 10
                           MouseArea {
                                  anchors.fill: parent
                                  onClicked:
                                      if(Cpp_Serial_Manager.connected == false )
                                      {
                                              startAutoConnect();
                                             _checkTimer.start();
                                      }

                              }

                       }

             }

           }
//           CellView {
//            id: _tableviewDMR
//            visible: false
//            width: 0.99 * parent.width; height: 0.90 * parent.height
//            anchors.horizontalCenter: parent.horizontalCenter
//            model: tablemodel
//       }
           CellViewBasic {
            id: _tableviewBasic
            visible: true
            width: 0.99 * parent.width; height: 0.92 * parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            model: tablemodel
       }
/*
          TableView {
              id: tableview
              width: 0.85 * parent.width; height: 0.8 * parent.height
              anchors.horizontalCenter: parent.horizontalCenter
              clip: true  //内容剪切到表格尺寸
              boundsBehavior: Flickable.StopAtBounds
              reuseItems: false //强制table 销毁代理
              columnSpacing: 1
              rowSpacing: 2

              //离表头的边距
              leftMargin: verticalHeader.width
              topMargin: horizontalHeader.height

              //ScrollBar
              ScrollBar.horizontal: ScrollBar {
                  //policy: "AlwaysOn"
              }
              ScrollBar.vertical: ScrollBar {
                  //policy: "AlwayOn"
              }
              ScrollIndicator.horizontal: ScrollIndicator { }
              ScrollIndicator.vertical: ScrollIndicator { }


              // width and height provider
                //property var columnWidths: [100, 80, 120, 100, 100]
                columnWidthProvider: function(column){ return  60 }//columnWidths[column] }
                rowHeightProvider: function (column) { return 30 }

              //表头
              Row {
                  id: horizontalHeader
                  y: tableview.contentY
                  z:2
                  Repeater {
                        model: tableview.columns  //数量
                        Label {
                            width: tableview.columnWidthProvider(modelData) + 1 //1 : columnSpacing
                            height: 33
                            text: horizontal_header_data[index]
                            padding: 10
                            verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
                            color: "white"
                            background: Rectangle { color: "#b5b5b5" }
                    }
                 }
              }

              //竖向表头
              Column {
                      id: verticalHeader
                      x: tableview.contentX
                      z: 2
                      Repeater {
                          model: tableview.rows
                          Label {
                              width: 30; height: tableview.rowHeightProvider(modelData) + 2 //2 : rowSpacing
                              text: index
                              padding: 10
                              verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
                              color: "white"
                              background: Rectangle { color: "#b5b5b5" }
                          }
                      }
                  }


              //定义列roles
              model: TableModel {
                  id: tablemodel
                  TableModelColumn{ display: "INDEX"     }
                  TableModelColumn{ display: "CALL_TYPE" }
                  TableModelColumn{ display: "SLOT"      }
                  TableModelColumn{ display: "TX_CC"     }
                  TableModelColumn{ display: "RX_CC"     }
                  TableModelColumn{ display: "CALL_ID"   }
                  TableModelColumn{ display: "OWN_ID"    }
                  TableModelColumn{ display: "CH_TYPE"   }
                  TableModelColumn{ display: "RX_CTCSS"  }
                  TableModelColumn{ display: "TX_CTCSS"  }
                  TableModelColumn{ display: "RX_GAIN"   }
                  TableModelColumn{ display: "SQL"       }
                  TableModelColumn{ display: "ENCRY"     }
                  TableModelColumn{ display: "SEED"      }
              }

              //定义行代理 和 model连接
              delegate: DelegateChooser {

                    DelegateChoice{
                      column: 0
                      delegate: Rectangle {
                          implicitWidth: 60
                          implicitHeight: 25
                          border.width: 0
                          Text {
                              text:  index
                              anchors.centerIn: parent
                          }
                      }
                    }

                    DelegateChoice{  //call_type
                        column: 1
                        delegate: ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                            currentIndex: display
                            model:combox_calltype
                            onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                        }
                    }

                    DelegateChoice {  //
                        column: 2
                        delegate: SpinBox {
                            value: model.display
                            from: 0; to: 2
                            stepSize: 1
                            onValueModified: model.display = this.value
                        }
                    }
                    DelegateChoice { //tx_cc
                        column: 3
                        delegate: SpinBox {
                            value: model.display
                            from: 0; to: 15
                            stepSize: 1
                            onValueModified: model.display = this.value
                        }
                    }

                    DelegateChoice { //rx_cc
                        column: 4
                        delegate: SpinBox {
                            value: model.display
                            from: 0; to: 15
                            stepSize: 1
                            onValueModified: model.display = this.value
                        }
                    }

                    DelegateChoice { //call_id
                        column: 5
                        delegate:  TextField {
                            text: model.display
                            placeholderText: "call_id"
                            selectByMouse: true
                            onTextEdited: model.edit = this.text
                        }
                    }

                    DelegateChoice { //owm_id
                        column: 6
                        delegate:  TextField {
                            text: model.display
                            placeholderText: "own_id"
                            selectByMouse: true
                            onTextEdited: model.edit = this.text
                        }
                    }

                    DelegateChoice {  //ch_type
                        column: 7
                        delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                            currentIndex: display
                            model:combox_chtype
                            onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                        }
                    }
                    DelegateChoice {
                        column: 8
                        delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                            currentIndex: display
                            model:combox_ctcss
                            onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                        }
                    }

                    DelegateChoice {
                        column: 9
                        delegate:  ComboBox { //这里我们需要注意：table model和combobox model之间的冲突
                            currentIndex: display
                            model:combox_ctcss
                            onActivated: display = this.currentIndex // we've only used 'display' keyword, because combobox model doesnt have this as role name
                        }
                    }

                    DelegateChoice { //RX_GAIN
                        column: 10
                        delegate: SpinBox {
                            value: model.display
                            from: 0; to: 15
                            stepSize: 1
                            onValueModified: model.display = this.value
                        }
                    }


                    DelegateChoice { //SQL
                        column: 11
                        delegate: SpinBox {
                            value: model.display
                            from: 0; to: 15
                            stepSize: 1
                            onValueModified: model.display = this.value
                        }
                    }

                    DelegateChoice { //ENCRY
                        column: 12
                        delegate: CheckBox {
                           checkState: model.display
                           onToggled: model.display = this.checkState
                        }
                    }

                    DelegateChoice {
                        column: 13
                        delegate:  TextField {
                            text: model.edit
                            placeholderText: "XXXX"
                            selectByMouse: true
                            onTextEdited: model.edit = this.text
                        }
                    }

              }
        }
*/
     }

}
