////"Username forgotten" Layer
////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//import QtQuick 2.3
//import Material.ListItems 0.1 as ListItem
//import "../DictyQMLComponents" as Dicty

//Item {
//    id: userLVItem
//    //opacity: userLVItem.opened ? 1.0 : 0.0
//    //enabled: userLVItem.opened ? true : false
//    visible: true
//    property bool autoFlick: true
//    property bool opened: true
//    property real mainFontSize: 17
//    property string mainFont: "Roboto"
//    anchors {
//        fill: parent
//        //centerIn: parent
//        //horizontalCenter: parent.horizontalCenter
//        leftMargin: userLVItem.opened ? 0 : loginWindow.width

//        Behavior on leftMargin {
//            NumberAnimation { duration: changeStateDuratin;/* easing.type: userLVItem.opened ? Easing.OutCubic : Easing.InCubic*/ }
//        }
//    }
//    Behavior on opacity {
//        NumberAnimation { duration: changeStateDuratin; /*easing.type: userLVItem.opened ? Easing.OutCubic : Easing.InCubic*/}
//    }
//    function open() {
//        //userName.text = ""
//        if(opened === true) return
//        opened = true;

//    }
//    function close() {
//            userLVItem.destroy()

//    }
//    Rectangle {
//        id: registeredUsers
//        width: loginWindow.width
//        height: buttonSignIn.height
//        color: color_main
//        //            x: parent.x+windowFrame.border.width
//        //            y: parent.y+windowFrame.border.width
//        z: userLVItem.opened ? 5 : -5
//        Text{
//            anchors.fill: parent
//            horizontalAlignment: Text.AlignHCenter
//            verticalAlignment: Text.AlignVCenter
//            font.pixelSize: mainFontSize
//            //wrapMode: Text.WordWrap

//            //font.weight: light
//            font.family: mainFont
//            text: qsTr("Registered Users")
//            color: "white"
//        }
//        MouseArea{
//            anchors.fill: parent
//            property var clickPos: "1,1"
//            onPressed: {clickPos = Qt.point(mouse.x, mouse.y)}
//            onPositionChanged:{
//                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
//                loginWindow.x += delta.x
//                loginWindow.y += delta.y
//            }

//        }
//    }

//    //        MouseArea{
//    //            anchors.fill: parent
//    //            property var clickPos: "1,1"
//    //            onPressed: {clickPos = Qt.point(mouse.x, mouse.y)}
//    //            onPositionChanged:{
//    //                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
//    //                loginWindow.x += delta.x
//    //                loginWindow.y += delta.y
//    //            }
//    //        }

//    Flickable {
//        id: flickable
//        //interactive: true
//        anchors {
//            //horizontalCenter: parent.horizontalCenter
//            right: parent.right
//            left: parent.left
//            top: registeredUsers.bottom
//            bottom: parent.bottom
//            rightMargin: 16
//            leftMargin: 16
//            topMargin: 16
//            bottomMargin: 16
//        }
//        //            width: parent.width
//        //            height: parent.height-registeredUsers.height
//        //            opacity: parent.opened ? 1 : 0
//        //            Behavior on opacity {
//        //                NumberAnimation { duration: changeStateDuratin; easing.type: Easing.InCubic }
//        //            }
//        //clip: true

//        contentHeight: Math.max(userList.implicitHeight, height)

//        Column{
//            id: userList
//            anchors.fill: parent

//            Repeater{
//                model: userListModel
//                delegate:  ListItem.Standard{
//                    text: modelData
//                    onClicked: {
//                        userName.text = modelData
//                        userLVItem.close()
//                    }
//                }
//            }
//        }
//    }

//    Dicty.Scrollbar {
//        id: scrollArea
//        flickableItem: flickable
//        //fillColor: color_main

//    }
//}
