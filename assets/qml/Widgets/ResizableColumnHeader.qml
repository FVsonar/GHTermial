import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../delegate"
ListView {
    id:root
    property var len : [200,200]
    property var count : root.model.length
    property real defaultWidth : 70
    property real minimalWidth : 70
    signal  columnWidthChanged
    property int need_reset: 0
    orientation: ListView.Horizontal
    clip: true
    delegate: HeaderDelegate {
        id: header
//        width:  root.len[index] ?? defaultWidth // only Qt>= 5.15
        width:  root.len[index] ? root.len[index]: defaultWidth
        height:  root.height
        color:"#eec"
        text: model.headerText
        // 修复更改宽度再切换语言时内部的header宽度未复位导致的问题
        //方式1：
        // 缺点，耦合性高 内部新建一个控件 监控几个会重置listview的情况
        Connections {
            target: switch_language_combox

          function  onActivated(){
               header.width = defaultWidth;
            }
        }


        Rectangle {
            id: resizeHandle
            color: Qt.darker(parent.color, 1.05)
            height: parent.height
            width: 3
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter


            MouseArea {
                id: mouseHandle
                anchors.fill: parent
                drag{ target: parent; axis: Drag.XAxis }
                hoverEnabled: true
                cursorShape: Qt.SizeHorCursor
                onMouseXChanged: {
                    if (drag.active) {
                        var newWidth = header.width + mouseX
                        if (newWidth >= minimalWidth) {
                            header.width = newWidth
                            root.len[index] = newWidth
                            root.columnWidthChanged()
                        }
                    }
                }
            }
        }
    }
    onCountChanged:        modelCountChanged()
//    Component.onCompleted: resetColumns()
    function columnWidthProvider(column) {  
        if(len[column])
        {
           // console.log(len[column])
        }
        else
        {
            len[column] = defaultWidth;
        }
        return len[column]
    }
    function resetColumns() {
        len=[]
        for (var i=0; i<count; i++) len.push(defaultWidth)
    }
    function modelCountChanged() {
        resetColumns()
        root.columnWidthChanged()
    }
}
