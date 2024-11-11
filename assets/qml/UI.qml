/*
 * Copyright (c) 2020-2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import QtQuick 2.12
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "Windows" as Windows
import "Widgets" as Widgets

Page {
    id: root

    //
    // Toolbar with buttons
    //
    Component.onCompleted:
    {
      app.is_DebugMode =  Cpp_DataProc.getDebugMode();
    }
    header: ToolBar {
        id: _toolBarRec
        height: 48

        //
        // Background gradient
        //
        Rectangle {
            border.width: 1
            border.color: palette.midlight

            gradient: Gradient {
                GradientStop { position: 0; color: "#21373f" }
                GradientStop { position: 1; color: "#11272f" }
            }

            anchors {
                fill: parent
                topMargin: -border.width
                bottomMargin: -border.width
                leftMargin: -border.width * 10
                rightMargin: -border.width * 10

            }
        }

        //
        // Toolbar controls
        //
        RowLayout {
            spacing: app.spacing
            anchors.fill: parent
            anchors.margins: app.spacing

            //
            // Horizontal spacing
            //
//            Item {
//                Layout.fillWidth: true
//            }

            // 调试用
            Button {
                id: qiehuan
                implicitWidth: 160
                Layout.alignment: Qt.AlignRight
               // anchors.right: switch_language_combox.left
                visible: app.is_DebugMode  //调试用
                flat: false
                font.bold: true
                opacity: enabled ? 1 : 0.5
                //Layout.leftMargin: 5
                onClicked:
                {
                    if ( _terminal.visible)
                    {
                        _terminal.visible = false;
                        _FreqWriteUI.visible = true;
                    }
                    else
                    {
                        _terminal.visible = true;
                        _FreqWriteUI.visible = false;
                    }

                }
                text: (checked ? "写频" : "显示") + " "
            }

            ComboBox {
                id: switch_language_combox
                Layout.alignment: Qt.AlignRight
                model:['English','简体中文']
                //首先设置ComboBox显示当前系统语言
               currentIndex: qmlLanguage.getLocalLanguage()
               onActivated: {
                   //用户使用ComboBox后根据index调用cpp中的方法
                   qmlLanguage.setLanguage(index)
                   //设置ComboBox的显示语言
                    currentIndex = index
                }
            }


        }
    }




/*
    Rectangle {
        id: _verBarRec
        width: 170
        height: parent.height
        anchors.bottom: parent.bottom
        anchors.right:  parent.right

        color: "#333333"

        //
        // serial controls
        //
        ColumnLayout {

            spacing: 5

            //
            // Serial port selector
            //
            Label {
                text: qsTr("SerialPort") + ":"
                font.family: "微软雅黑"
                font.weight: Font.Thin
                font.pixelSize: 12
                Layout.leftMargin: 5
                Layout.topMargin: 5

            } ComboBox {
                id: _portCombo
                Layout.minimumWidth: 160
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
            // Baud rate selector
            //
            Label {
                text: qsTr("BaudRate") + ":"
                font.family: "微软雅黑"
                font.weight: Font.Light
                font.pixelSize: 12
                Layout.leftMargin: 5
            } ComboBox {
                id: _baudCombo
                Layout.minimumWidth: 160
                Layout.maximumWidth: 160
                 Layout.leftMargin: 5
                model: Cpp_Serial_Manager.baudRateList
                currentIndex: Cpp_Serial_Manager.baudRateIndex
                onCurrentIndexChanged: {
                    if (currentIndex !== Cpp_Serial_Manager.baudRateIndex)
                        Cpp_Serial_Manager.baudRateIndex = currentIndex
                }
            }


            //
            // Connect/disconnect button
            //
            Button {

                implicitWidth: 160
                flat: false
                icon.width: 24
                icon.height: 24
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

            // 调试用
            Button {
                id: qiehuan
                implicitWidth: 160
                visible:  app.is_DebugMode  //调试用
                flat: false
                icon.width: 24
                icon.height: 24
                font.bold: true
                opacity: enabled ? 1 : 0.5
                icon.color: palette.buttonText
                Layout.leftMargin: 5
//                checked: Cpp_Serial_Manager.connected
//                enabled: Cpp_Serial_Manager.configurationOk
                onClicked:
                {
                    if ( _terminal.visible)
                    {
                        _terminal.visible = false;
                        _FreqWriteUI.visible = true;
                    }
                    else
                    {
                        _terminal.visible = true;
                        _FreqWriteUI.visible = false;
                    }

                }
                palette.buttonText: checked ? "#d72d60" : "#2eed5c"
                text: (checked ? "写频" : "显示") + " "
                icon.source: checked ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"

              //  Behavior on opacity {NumberAnimation{}}
            }
        }
    }
*/
    //
    // Background color
    //
    background: Rectangle {
        color: app.windowBackgroundColor
    }


        //
        // Terminal widget 终端
        //
        Widgets.Terminal {
             id: _terminal

             anchors {
                 fill: parent

              //   rightMargin: _verBarRec.width

             }


             onTransmissionClicked: _fileTransmission.showNormal()
         }




    //
    //  串口设置
    //
//    Windows.SerialSetup {
//        id: _serialSetup
//    }


        Windows.FreqWriteUI {
            id: _FreqWriteUI
            anchors {
                  fill: parent

                // rightMargin: _verBarRec.width
            }

        }



    //
    // File transmission dialog
    //
    Windows.FileTransmission {
        id: _fileTransmission
    }
}
