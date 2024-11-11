import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    property alias text: label.text
    property alias textColor: label.color
    property alias horizentalAlignment: label.horizontalAlignment

    color: "#eec"

    Text {
        id: label
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        rightPadding: 5
        leftPadding: 5
        font.bold: true
    }
}
