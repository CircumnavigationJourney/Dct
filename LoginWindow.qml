

import QtQuick 2.3
import Material 0.1
import Material.ListItems 0.1 as ListItem

//import Material.Button as Button
//import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import Material.Extras 0.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.3
import QtQuick.Controls 1.3 as Controls
Window {
    id: loginWindow
    property double goldenRatio: 1.618
    property double passwordOpacity: 1.0
    // property color color_main: Palette.colors["indigo"]["500"]
    property color color_error: "#F38630"
    property var basicComponents: [
        "Bottom Sheet", "Dialog", "Forms", "List Items", "Page Stack", "Time Picker", "Date Picker","Bottom Sheet", "Dialog", "Forms", "List Items", "Page Stack", "Time Picker", "Date Picker","Bottom Sheet", "Dialog", "Forms", "List Items", "Page Stack", "Time Picker", "Date Picker","Bottom Sheet", "Dialog", "Forms", "List Items", "Page Stack", "Time Picker", "Date Picker"
    ]
    //property color color_error: "#FA6900"
    //property color color_error: Palette.colors["red"]["500"]
    //theme colors :
    //    theme {
    //        primaryColor: Palette.colors["blue"]["500"]
    //        primaryDarkColor: Palette.colors["blue"]["700"]
    //        accentColor: Palette.colors["teal"]["500"]
    //        tabHighlightColor: "white"
    //    }
    //    property color color_background: Theme.backgroundColor
    //    property color color_nearBackground: Palette.colors["blue"]["500"]
    //    property color color_main: Palette.colors["blue"]["500"]
    //    property color color_highlight: Palette.colors["blue"]["500"]
    property color color_background: "#E0E4CC"
    property color color_nearBackground: "#A7DBD8"
    property color color_main: "#69D2E7"
    property color color_highlight: "#F38630"
    //    //    property color color_main: Palette.colors["indigo"]["500"]
    //    //    property color color_border: Palette.colors["grey"]["700"]
    //    //    property color color_error: Palette.colors["red"]["500"]
    property string mainFont: "Roboto"/*"Noto Sans Historic"*/
    property real mainFontSize: loginWindow.width/13 /*Units.dp(32)*/
    // property int itemsWidth: 280
    property int currentForm: 1

    function getErrorMessage(text){
        windowFrame.border.color = color_error
        snackbar.backgroundColor = color_error
        snackbarErrorAnimation.start()
        snackbar.open(text);
    }

    signal checkUser(string userName, string password, int windowForm)
    signal canceled()
    //проблема хардкожености, при уменьшении ширины окна вся красота разрушается
    width: 350
    height: width * goldenRatio
    //    FontLoader { id: hindi
    //        source: "/fonts/Suwannaphum.ttf";
    //    }
    Rectangle{
        id: windowFrame
        color: color_background
        z: -1
        anchors.fill: parent
        border.color: color_main
        border.width: 2
    }
    MouseArea{
        id: track
        anchors.fill: parent
        property var onClick: "1,1"
        onPressed: {
            onClick = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - onClick.x, mouse.y - onClick.y)
            loginWindow.x += delta.x
            loginWindow.y += delta.y
        }
    }
    Button{
        id: buttonSignIn
        //1 is registration 0 is login
        x: parent.x+windowFrame.border.width
        y: parent.y+windowFrame.border.width
        backgroundColor: color_main
        height: loginWindow.height/6
        width: loginWindow.width - (windowFrame.border.width*2)
        //Стиль просто был скопирован из MaterialStyle.ButtonStyle т.к. необходимо было изменить радиус данной кнопки
        style:    ButtonStyle {
            id: styleB

            padding {
                left: 0
                right: 0
                top: 0
                bottom: 0
            }

            property bool darkBackground: control.hasOwnProperty("darkBackground")
                                          ? control.darkBackground : Theme.isDarkColor(controlBackground)

            property int controlElevation: control.hasOwnProperty("elevation") ? control.elevation : 1

            property color controlBackground: control.hasOwnProperty("backgroundColor")
                                              ? control.backgroundColor : controlElevation == 0 ? "transparent" : "white"

            property string context: control.hasOwnProperty("context") ? control.context : "default"

            background: View {
                id: background

                implicitHeight: Units.dp(36)

                //                radius: Units.dp(2)

                backgroundColor: control.enabled || controlElevation === 0
                                 ? controlBackground
                                 : darkBackground ? Qt.rgba(1, 1, 1, 0.12)
                                                  : Qt.rgba(0, 0, 0, 0.12)

                elevation: {
                    var elevation = controlElevation

                    if (elevation > 0 && (control.focus || mouseArea.currentCircle))
                        elevation++;

                    if(!control.enabled)
                        elevation = 0;

                    return elevation;
                }

                tintColor: mouseArea.currentCircle || control.focus || control.hovered
                           ? Qt.rgba(0,0,0, mouseArea.currentCircle ? 0.1
                                                                    : elevation > 0 ? 0.03
                                                                                    : 0.05)
                           : "transparent"

                Ink {
                    id: mouseArea

                    anchors.fill: parent
                    focused: control.focus && background.context !== "dialog"
                             && background.context !== "snackbar"
                    focusWidth: parent.width - Units.dp(30)
                    focusColor: Qt.darker(background.backgroundColor, 1.05)

                    Connections {
                        target: control.__behavior
                        onPressed: mouseArea.onPressed(mouse)
                        onCanceled: mouseArea.onCanceled()
                        onReleased: mouseArea.onReleased(mouse)
                    }
                }
            }
            label: Item {
                implicitHeight: Math.max(Units.dp(36), label.height + Units.dp(16))
                implicitWidth: context == "dialog"
                               ? Math.max(Units.dp(64), label.width + Units.dp(16))
                               : context == "snackbar" ? label.width + Units.dp(16)
                                                       : Math.max(Units.dp(88), label.width + Units.dp(32))

                Label {
                    id: label
                    anchors.centerIn: parent
                    text: control.text
                    style: "button"
                    color: control.enabled ? control.hasOwnProperty("textColor")
                                             ? control.textColor : darkBackground ? Theme.dark.textColor
                                                                                  : Theme.light.textColor
                    : control.darkBackground ? Qt.rgba(1, 1, 1, 0.30)
                    : Qt.rgba(0, 0, 0, 0.26)
                }
            }
        }
        Text{
            id: buttonSignInText
            anchors.centerIn: buttonSignIn
            font.pixelSize: mainFontSize + 2
            //font.weight: light
            font.family:mainFont
            text: qsTr("Sign in")
            color: Theme.lightDark(parent.backgroundColor,
                                   Theme.light.textColor,
                                   Theme.dark.textColor)
        }

        onClicked: {
            if(changeWindowStateAnimation.running === false)
                if(currentForm === 1){
                    currentForm = 0;
                    buttonSignInText.text = qsTr("Sign up");
                    passwordOpacity = 0.0
                    password_2.z = -1;
                    changeWindowStateAnimation.start()
                }
                else if (currentForm === 0){
                    currentForm = 1;
                    buttonSignInText.text = qsTr("Sign in");
                    passwordOpacity = 1.0
                    password_2.z = 1;
                    changeWindowStateAnimation.start()
                }
        }

    }
    //    ColumnLayout {
    //        id: column

    //        width: loginWindow.width - (windowFrame.border * 2)
    //        anchors.top: buttonSignIn.bottom
    //        anchors.bottom: okButton.top
    //        anchors.topMargin: 32
    //        anchors.horizontalCenter: parent.horizontalCenter

    TextField {
        id: userName
        width: parent.width * 0.75
        //        height: font.pixelSize *
        placeholderText:/* qsTr("ឈ្មោះអ្នកប្រើ")*/qsTr("User Name")
        floatingLabel: true
        font.pixelSize: mainFontSize
        //font.weight: light
        font.family: mainFont
        anchors {
            top: buttonSignIn.bottom
            topMargin: 32
            horizontalCenter: parent.horizontalCenter
        }
        color: color_highlight
        focus: true
    }

    TextField {
        id: password_1
        width: parent.width * 0.75
        placeholderText: qsTr("Password")
        floatingLabel: true
        echoMode: TextInput.Password
        font.pixelSize: mainFontSize
        //font.weight: light
        font.family: mainFont
        anchors {
            top: userName.bottom
            topMargin: userName.font.pixelSize
            horizontalCenter: parent.horizontalCenter
        }
        color: color_highlight
    }
    TextField {
        id:password_2
        width: parent.width * 0.75
        placeholderText: qsTr("Confirm Password")
        floatingLabel: true
        echoMode: TextInput.Password
        font.pixelSize: mainFontSize
        //font.weight: light
        font.family: mainFont
        anchors {
            top: password_1.bottom
            topMargin: userName.font.pixelSize
            horizontalCenter: parent.horizontalCenter
        }
        color: color_highlight
    }

    //через кнопку внутри сообщения об ошибке можно добавить функции доступа к базе пользователей и возможность изменить пароль
    View {
        id: snackbar

        property string buttonText
        property color buttonColor: color_error
        property string text
        property bool opened: false
        property int duration: 5000
        property bool fullWidth: Device.type === Device.phone || Device.type === Device.phablet

        signal clicked

        function open(text) {
            snackbar.text = text
            opened = true;
            timer.restart();
        }

        anchors {
            horizontalCenter: parent.horizontalCenter
            //left: parent.left
            //right: fullWidth ? parent.right : undefined
            topMargin: userName.font.pixelSize
            top: password_2.bottom
            bottom: okButton.top
            //leftMargin: 0/*fullWidth ? 0 : Units.dp(16)*/
            bottomMargin: snackbar.opened ?  0 :  (okButton.y - (password_2.y + password_2.height)) * -1

            Behavior on bottomMargin {
                NumberAnimation { duration: 300 }
            }
        }
        radius: /*fullWidth ?*/ 0/* : Units.dp(2)*/
        backgroundColor: color_main
        //height: okButton.y - (password_2.y + password_2.height)
        width: loginWindow.width - (windowFrame.border.width*2)
        opacity: opened ? 1 : 0
        //                        implicitWidth: buttonText == "" ? snackText.paintedWidth + Units.dp(48)
        //                                                        : snackText.paintedWidth + Units.dp(72) + snackButton.width

        onClicked: {
            if(snackButton.opacity !== 0){
                userName.text = "SNACKBAR CLICKED!"
            }
        }
        Timer {
            id: timer

            interval: snackbar.duration

            onTriggered: {
                if (!running) {
                    snackbar.opened = false;
                }
            }
        }

        Text {
            id: snackText
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: mainFontSize * 0.75
            //font.weight: light
            font.family: mainFont
            anchors {
                right: snackbar.buttonText == "" ? parent.right : snackButton.left
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                leftMargin: Units.dp(24)
                topMargin: Units.dp(16)
                rightMargin: Units.dp(24)

            }
            color: Theme.lightDark(snackbar.backgroundColor,
                                   Theme.light.textColor,
                                   Theme.dark.textColor)
            text: snackbar.text
        }

        Button {
            id: snackButton
            opacity: snackbar.buttonText == "" ? 0 : 1
            textColor: snackbar.buttonColor
            text: snackbar.buttonText
            context: "snackbar"
            onClicked: snackbar.clicked()
            anchors {
                right: parent.right
                //left: snackText.right
                top: parent.top
                bottom: parent.bottom

                // Recommended button touch target is 36dp
                topMargin: Units.dp(6)
                bottomMargin: Units.dp(6)

                // Normal margin is 24dp, but button itself uses 8dp margins
                rightMargin: snackbar.buttonText == "" ? 0 : Units.dp(16)
            }
        }

        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }
    }
    // }

    Button {
        id: okButton
        property int buttMargin: (loginWindow.width - userName.width)/2
        width: loginWindow.width/2 - windowFrame.border.width /*(userName.width/2) - (buttMargin/2)*/
        height: buttonSignIn.height /*userName.height*/
        style: buttonSignIn.style
        //anchors.top: column.bottom
        // anchors.topMargin: snackbar.height-column.spacing
        // x: parent.x+(loginWindow.width - userName.width)/2
        y: parent.height - okButton.height - windowFrame.border.width
        x: parent.x + windowFrame.border.width
        backgroundColor: color_nearBackground
        //anchors.horizontalCenter: parent.horizontalCenter
        Text{
            anchors.centerIn: okButton
            font.pixelSize: mainFontSize/ goldenRatio
            //font.weight: light
            font.family: mainFont
            font.capitalization: Font.AllUppercase
            text: qsTr("Ok")
            color: Theme.lightDark(parent.backgroundColor,
                                   Theme.light.textColor,
                                   Theme.dark.textColor)
        }
        onClicked: {
            if(userName.text === "") {
                if(userName.focus !== true) userName.focus = true
                userName.color = color_error
                nameErrorAnimation.start()
                getErrorMessage(qsTr("At least one character needed"))
                return;
            }
            if(password_1.text === ""){
                if(password_1.focus !== true) password_1.focus = true
                password_1.color = color_error
                password_2.color = color_error
                passwordErrorAnimation.start()
                getErrorMessage(qsTr("At least one character needed"))
                return;
            }
            if(currentForm == 1){
                if(password_1.text === password_2.text)
                    checkUser(userName.text, password_1.text, currentForm);
                else {
                    password_1.color = color_error
                    password_2.color = color_error
                    passwordErrorAnimation.start()
                    getErrorMessage(qsTr("Password mismatch"))
                    return;
                }
            }
            else {
                checkUser(userName.text, password_1.text, currentForm);
            }
        }


    }
    Button{
        id: cancelButton
        backgroundColor: color_nearBackground
        width: okButton.width
        height: okButton.height
        // anchors.top: column.bottom
        // anchors.topMargin: snackbar.height-column.spacing
        anchors.left: okButton.right
        y: okButton.y
        // anchors.leftMargin: okButton.buttMargin
        style: okButton.style
        //x: parent.x+(loginWindow.width - userName.width)/2
        Text{
            anchors.centerIn: cancelButton
            font.pixelSize: mainFontSize/ goldenRatio
            //font.weight: light
            font.family: mainFont
            font.capitalization: Font.AllUppercase
            text: qsTr("Cancel")
            color: Theme.lightDark(parent.backgroundColor,
                                   Theme.light.textColor,
                                   Theme.dark.textColor)
        }
        onClicked: {
            if(usersLoginsView.opened)
                usersLoginsView.close();
            else usersLoginsView.open();

            //            onCloseAnimation.start()
            //            canceled()

            // snackbar.open("sjlfjfkljd skldjflksd j skljd skdj lskdj skldj lksdj sdk jsdklj !!! lkdjfldkj kl!!! テキストを折り返します")
        }

    }

    SequentialAnimation {
        id: changeWindowStateAnimation
        running: false
        NumberAnimation { target: password_2; property: "opacity"; to: passwordOpacity; duration: 1000}
    }

    SequentialAnimation {
        id: onCloseAnimation
        running: false
        NumberAnimation { target: loginWindow; property: "opacity"; to: 0;  easing.type: Easing.Bezier; duration: 1000}
    }
    SequentialAnimation {
        id: nameErrorAnimation
        running: false
        ColorAnimation { target: userName; easing.type: Easing.InCubic; property: "color"; from: color_error; to: color_highlight; duration: snackbar.duration/2}
    }
    SequentialAnimation {
        id: snackbarErrorAnimation
        running: false
        //ColorAnimation { target: loginWindow; property: "color_main"; from: color_error; to: color_main; duration: 2000}
        ColorAnimation {
            target: snackbar;
            easing.type: Easing.InCubic
            property: "backgroundColor";
            from: color_error; to: color_main; duration: snackbar.duration/2
        }
        ColorAnimation { target: windowFrame; easing.type: Easing.InCubic; property: "border.color"; from: color_error; to: color_main; duration: snackbar.duration/4}

    }
    SequentialAnimation {
        id: passwordErrorAnimation
        running: false
        ColorAnimation { target: password_1; easing.type: Easing.InCubic; property: "color"; from: color_error; to: color_highlight; duration: snackbar.duration/2}
        ColorAnimation { target: password_2; easing.type: Easing.InCubic; property: "color"; from: color_error; to: color_highlight; duration: snackbar.duration/2}
    }

    Rectangle {
        id: usersLoginsView
        property bool autoFlick: true
        property bool opened: false
        function open() {
            userName.text = ""
            if(opened === true) return
            opened = true;

        }
        function close() {
            if(opened === false) return
            opened = false;

        }
        z: opened ? 2 : -2
        opacity: opened ? 1 : 0
        width: loginWindow.width - (windowFrame.border.width*2)
        height: loginWindow.height - (windowFrame.border.width*2)
        //anchors.fill: parent
        anchors {
            horizontalCenter: parent.horizontalCenter
            leftMargin: usersLoginsView.opened ? 0 : -usersLoginsView.width

            Behavior on leftMargin {
                NumberAnimation { duration: 300 }
            }
        }
        color: color_background
        Rectangle {
            id: registeredUsers
            width: loginWindow.width
            height: buttonSignIn.height
            color: color_main
            z: usersLoginsView.opened ? 5 : -5
            Text{
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: mainFontSize
                width: parent.width
                wrapMode: Text.WordWrap

                //font.weight: light
                font.family: mainFont
                text: qsTr("Registered Users")
                color: Theme.lightDark(parent.color,
                                       Theme.light.textColor,
                                       Theme.dark.textColor)
            }
            MouseArea{
                //z: usersLoginsView.opened ? 0 : -2
                anchors.fill: parent
                property var clickPos: "1,1"
                onPressed: {clickPos = Qt.point(mouse.x, mouse.y)}
                onPositionChanged:{
                    var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
                    loginWindow.x += delta.x
                    loginWindow.y += delta.y
                }

            }
        }
        Flickable {
            id: flickable
            width: parent.width
            height: usersLoginsView.opened ? parent.height-registeredUsers.height : 0
            anchors {
                top: registeredUsers.bottom
                bottom: parent.bottom
                topMargin: Units.dp(16)
                bottomMargin: Units.dp(16)
            }
            contentHeight: Math.max(userList.implicitHeight, height)

            Column{
                id: userList
                //width: usersLoginsView.width
                anchors.fill: parent
                Repeater{
                    //TODO GETUSERNAMES
                    model: basicComponents
                    delegate:  ListItem.Standard{
                        text: modelData
                        onClicked: {
                            userName.text = modelData
                            usersLoginsView.close()
                        }
                    }
                }
            }
        }
        Scrollbar {
            flickableItem: flickable
        }

        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }


    }
}