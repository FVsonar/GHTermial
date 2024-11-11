import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtGraphicalEffects 1.0
//import "./Haier/Controls" as HaierControls


Rectangle {
    id: root
    color: "#3388EF"
    implicitWidth: 60

    Material.elevation: 4
    radius: shrinked ? 12.5 : 0

    anchors.margins: shrinked ? 5 : 0
    anchors.top: shrinked?undefined:parent.top
    anchors.topMargin: shrinked?0:40


    //layer.enabled: true
    //layer.effect: HaierControls.ShadowEffect {
    //    elevation: root.Material.elevation
    //}

    property int active_page_index: 0
    property  bool shrinked: false

    PropertyAnimation {id: shrink_navi1; target: root; properties: "width"; to: 25; duration: 300; easing.type: Easing.InCubic}
    PropertyAnimation {id: expand_navi1; target: root; properties: "width"; to: 60; duration: 500; easing.type: Easing.OutCubic}
    PropertyAnimation {id: shrink_navi2; target: root; properties: "height"; to: 25; duration: 300; easing.type: Easing.InCubic}

    Rectangle
    {
        id: home_rect
        color: (root.active_page_index == index)?Qt.rgba(0,0,0,0.25):Qt.rgba(0,0,0,0)
        width:  parent.width
        height: 60
        anchors.horizontalCenter:  parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        property int index: 0
        visible:  !root.shrinked

        PropertyAnimation {id: animateColor_home_in; target: home_rect; properties: "color"; to:Qt.rgba(0,0,0,0.12); duration: 200}
        PropertyAnimation {id: animateColor_home_out; target: home_rect; properties: "color"; to: (root.active_page_index == home_rect.index?Qt.rgba(0,0,0,0.25):Qt.rgba(0,0,0,0)); duration: 200}

        Image {
            source: "qrc:/images/navi/home.png"
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                navi_page(home_rect.index)
            }

            onEntered: {
                animateColor_home_in.start()
            }

            onExited: {
                animateColor_home_out.start()
            }
        }

    }

    Rectangle
    {
        id: record_rect
        color: root.active_page_index == index?Qt.rgba(0,0,0,0.25):Qt.rgba(0,0,0,0)
        width:  parent.width
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: home_rect.bottom
        property int index: 1
        visible: !root.shrinked

        PropertyAnimation {id: animateColor_record_in; target: record_rect; properties: "color"; to: Qt.rgba(0,0,0,0.12); duration: 200}
        PropertyAnimation {id: animateColor_record_out; target: record_rect; properties: "color"; to: (root.active_page_index == record_rect.index?Qt.rgba(0,0,0,0.25):Qt.rgba(0,0,0,0)); duration: 200}

        Image{
            source: "qrc:/images/navi/record.png"
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled:true

            onClicked: {
               navi_page(record_rect.index);
            }

            onEntered: {
               animateColor_record_in.start()
            }

            onExited: {
                animateColor_record_out.start()
            }


        }
    }

    function navi_page(index){
       root.active_page_index = index
    }

}
