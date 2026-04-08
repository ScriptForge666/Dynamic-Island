// Copyright 2026 Scriptforge
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Window {
    id: mainWin
    property int capsuleStateWidth: 50
    property int capsuleStateHeight: 20
    property int expandStateWidth: 200
    property int expandStateHeight: 80
    property int expendedradiusSize: 8
    property bool isExpanded: false
    property color windowBgColor: "white"

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool
    visible: true
    width: capsuleStateWidth
    height: capsuleStateHeight
    title: "Dynamic Island"
    color: "#00000000"
    

    // 宽高平滑动画
    Behavior on width { NumberAnimation { duration: 300; easing.type: Easing.OutQuad } }
    Behavior on height { NumberAnimation { duration: 300; easing.type: Easing.OutQuad } }

    function centerWindow() {
        var xPos = (Screen.width - width) / 2
        var yPos = 10
        setX(xPos)
        setY(yPos)
    }

    Component.onCompleted: centerWindow()
    onWidthChanged: centerWindow()
    onHeightChanged: centerWindow()

    ColumnLayout{
        anchors.fill: parent
        spacing:0

        Timer {
            id: expandTimer
            interval: 500
            running: false
            repeat: false
            onTriggered: {
                isExpanded = true
                mainWin.width = expandStateWidth
                mainWin.height = expandStateHeight
            }
        }

        Rectangle {
            id: mainRect
            color: windowBgColor
            Layout.fillWidth: true
            Layout.fillHeight: true

            // ✅ 核心：Windows11 风格圆角切换
            //radius: isExpanded ? 8 : height / 2

            // 圆角平滑过渡
            Behavior on radius {
                NumberAnimation { duration: 300 }
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: expandTimer.restart()
                onExited: {
                    if(isExpanded){
                        expandTimer.stop()
                        isExpanded = false
                        mainWin.width = capsuleStateWidth
                        mainWin.height = capsuleStateHeight
                    }
                }
            }
        }
    }
}