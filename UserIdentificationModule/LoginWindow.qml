import QtQuick 2.3
import Material 0.1
import Material.ListItems 0.1 as ListItem
import "DictyQMLComponents" as Dicty
//import QtGraphicalEffects 1.0
//modification to OverlayLayer z: paramerter (modification in qml-material is a hack)
//TODO userName lenght
Dicty.Window {
    clientSideDecorations: true
    id: loginWindow
    visible: true
    width:  350//Units.dp(350)
    height: 550//Units.dp(550)
    Component.onCompleted: Units.multiplier = 2.3

//    flags: Qt.WA_TranslucentBackground |
//           Qt.WA_DeleteOnClose |
//           Qt.FramelessWindowHint |
//           Qt.WindowStaysOnTopHint |
//           Qt.WA_OpaquePaintEvent |
//           Qt.WA_NoSystemBackground |
//           Qt.WindowSystemMenuHint  |
//           Qt.WindowMinMaxButtonsHint
    property int currentForm
    //    FontLoader { id: hindi
    //        source: "/fonts/Suwannaphum.ttf";
    //    }
    //    property double goldenRatio: 1.618
    // property double passwordOpacity: 1.0
    property int changeStateDuratin: 500
    //theme colors :
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    property color color_background: Theme.backgroundColor
    property color color_nearBackground: Palette.colors["blue"]["400"]
    property color color_main: Palette.colors["blue"]["500"]
    property color color_highlight: Palette.colors["blue"]["500"]
    property color color_error: Palette.colors["red"]["500"]

//    PageStack {
//        id: __pageStack
//        anchors.fill: parent

////        onPushed: __toolbar.push(page)
////        onPopped: __toolbar.pop(page)
////        onReplaced: __toolbar.replace(page)
//    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //    property color color_background: "#E0E4CC"
    //    property color color_nearBackground: "#A7DBD8"
    //    property color color_main: "#69D2E7"
    //    property color color_highlight: "#F38630"
    //    property color color_error: "#F38630"
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    property string mainFont: "Arial"/*"Noto Sans Historic"*/
    property real mainFontSize: 17 /*loginWindow.width/13*/ /*Units.dp(27)*/
    property real largeFontSize: 27
    property real spacing: 27
    property int windowBorderWidth: 2
    //Messages : for better performance
    property var errorMessage:[
        qsTr("At least one character needed"),
        qsTr("The name is already registered. Try another one or Sign up..."),
        qsTr("Password is needed"),
        qsTr("Wrong password! try another one..."), //это точная фраза из С++ по которой идет сравнение в snackbar TODO : переписать на более гибкий и эффективный лад
        qsTr("User is not Found...") //это точная фраза из С++ по которой идет сравнение в snackbar TODO : переписать на более гибкий и эффективный лад
    ]

    property var changeWindowFormButtonText: [
        qsTr("Sign In"),
        qsTr("Sign Up"),
        qsTr("Password Changing")
    ]
    //    property string atLeastOneCharN: qsTr("At least one character needed")
    //    property string userNameIsAlreadyR: qsTr("The name is already registered. Try another one or Sign up...")
    //    property string passwordIsNeeded: qsTr("Password is needed")
    //for tests ++++++++++
    property int theme: 0
    //++++++++++++++++++++
    function changeThemme(){
        if(theme === 0){
            color_background = "#E0E4CC"
            color_nearBackground = "#A7DBD8"
            color_main = "#69D2E7"
            color_highlight = "#F38630"
            color_error = "#F36630"
            theme = 1;
        }
        else if (theme === 1){
            color_background = Theme.backgroundColor
            color_nearBackground = Palette.colors["blue"]["400"]
            color_main = Palette.colors["blue"]["500"]
            color_highlight =  Palette.colors["blue"]["500"]
            color_error =  Palette.colors["red"]["500"]
            theme = 0;
        }

    }
    //param needed to initialize window with concrete form
    //for example window can have Login form (param = 0), Registration form (param = 1), Change Password form (param = 2)
    function getInitParameter(param, name){
        currentForm = param;
        userName.text = name;
        console.log("current form: " + param + "; user name:" + name);
        if(currentForm === 0)
            setSignInState();
        else if (currentForm === 1){
            setSignUpState();
        }
        else if (currentForm === 2){
            if(userName.text === "") {
                console.log("user name is empty but changing password started!!!error")
                setSignInState();
            }
            else
                setPasswordChangingState()
        }
    }
    //showing error message with animation
    function getErrorMessage(text){
        windowFrame.border.color = color_error
        snackbar.backgroundColor = color_error
        snackbarErrorAnimation.start()
        snackbar.open(text);
    }

    //window form changing
    function changeCurrentState(){
        //if window form is PasswrdChanging or SignUp make it SignIn
        if(currentForm === 1 || currentForm === 2){
            setSignInState();
        }
        else if (currentForm === 0) {
            setSignUpState();
        }
    }

    function setSignInState(){
        currentForm = 0; // 0 - Sign in; 1 - Sign up; 2 - Password Change
        snackbar.opened = false;
        userName.hasError = 0
        userName.enabled = true
        buttonChangeWindowForm.text = changeWindowFormButtonText[1]; // 0 - Sign in; 1 - Sign up; 2 - Password Change
        password_2.opacity = 0.0
        password_2.enabled = false;
    }
    function setSignUpState(){
        currentForm = 1; // 0 - Sign in; 1 - Sign up; 2 - Password Change
        snackbar.opened = false;
        userName.enabled = true
        checkForAlreadyRegistered();
        buttonChangeWindowForm.text = changeWindowFormButtonText[0]; // 0 - Sign in; 1 - Sign up; 2 - Password Change
        password_2.opacity = 1.0
        password_2.enabled = true;
    }

    function setPasswordChangingState(){
        if(userName.text === "") {
            snackbar.open(errorMessage[0]);
            setSignInState();
            return;
        }
        currentForm = 2; // 0 - Sign in; 1 - Sign up; 2 - Password Change
        userName.enabled = false;
        password_2.opacity = 1.0
        password_2.enabled = true;
        buttonChangeWindowForm.text = changeWindowFormButtonText[2]; // 0 - Sign in; 1 - Sign up; 2 - Password Change
    }
    function  checkForAlreadyRegistered(){
        userName.wasRegistered = UImodule.isRegistered(userName.text)
        userName.hasError = (currentForm === 1) ? userName.wasRegistered : 0
        if(userName.hasError) getErrorMessage(errorMessage[1])
        else if(snackbar.opened) snackbar.opened = false;
    }

    function closeWindow(){
        onCloseAnimation.start()
    }

    signal checkUser(string userName, string password, int currentForm)


    onOpacityChanged: {

        if(loginWindow.opacity === 0) {
            loginWindow.close();
        }
    }
    //part of princeple of creating Overlayer (for example to block any events from underlayers when Dialog called)
initialPage: Page{

    anchors.fill: parent
    Rectangle{
        id: windowFrame
        color: color_background
        z: -1
        anchors.fill: parent
        border.color: color_main
        border.width: windowBorderWidth
    }
    Action {
        shortcut: "Ctrl+T"
        onTriggered: changeThemme()
    }
    Action {
        shortcut: "Alt+F4"
        onTriggered: closeWindow()
    }

    //    Action {
    //     shortcut: "Alt + F4"
    //     onTriggered: onCloseAnimation.start()
    //    }

    //Sign up/in Layer
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Item{
        id: log_reg_View
        opacity: usersLoginsView.opened ? 0.0 : 1.0
        enabled: usersLoginsView.opened ? false : true
        anchors {
            fill: parent
            //centerIn: parent
            //horizontalCenter: parent.horizontalCenter
            //rightMargin: usersLoginsView.opened ? width : 0

            Behavior on leftMargin {
                NumberAnimation { duration: changeStateDuratin; /*easing.type: usersLoginsView.opened ? Easing.InCubic : Easing.OutCubic*/ }
            }
        }
        Behavior on opacity {
            NumberAnimation { duration: changeStateDuratin; /*easing.type: usersLoginsView.opened ? Easing.InCubic : Easing.OutCubic*/ }
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
        //------------------------------------------------
        //1 is Registration, 0 is Login
        Dicty.Button {
            id: buttonChangeWindowForm
            elevation: 1
            text: (currentForm === 1) ? changeWindowFormButtonText[0] :
                                        (currentForm === 0) ? changeWindowFormButtonText[1] :
                                                              changeWindowFormButtonText[2]
            backgroundColor: color_main
            height: 100 /*Units.dp(100)*/
            width: loginWindow.width - windowBorderWidth*2
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
                topMargin: windowBorderWidth
            }

            dct_radius: 0
            dct_fontFamily: mainFont
            dct_fontPixelSize: mainFontSize
            onClicked: changeCurrentState()

        }

        //------------------------------------------------

        TextField {
            id: userName
            property bool wasRegistered;
            width: parent.width * 0.75
            //        height: font.pixelSize *
            placeholderText:/* qsTr("ឈ្មោះអ្នកប្រើ")*/qsTr("User Name")
            floatingLabel: true
            font.pixelSize: largeFontSize
            //font.weight: light
            font.family: mainFont
            anchors {
                top: buttonChangeWindowForm.bottom
                topMargin: 32
                horizontalCenter: parent.horizontalCenter
            }
            color: color_highlight
            errorColor: color_error
            focus: true
            onTextChanged: {
                checkForAlreadyRegistered();
            }

        }

        TextField {
            id: password_1
            width: parent.width * 0.75
            placeholderText: qsTr("Password")
            floatingLabel: true
            echoMode: TextInput.Password
            font.pixelSize: largeFontSize
            //font.weight: light
            errorColor: color_error
            font.family: mainFont
            anchors {
                top: userName.bottom
                topMargin: spacing
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
            font.pixelSize: largeFontSize
            //font.weight: light
            font.family: mainFont
            anchors {
                top: password_1.bottom
                topMargin: spacing
                horizontalCenter: parent.horizontalCenter
            }
            enabled: currentForm ? true : false
            opacity: currentForm ? 1.0 : 0.0
            color: color_highlight

            Behavior on opacity { NumberAnimation {duration: 1000} }
        }

        View {
            id: snackbar
            enabled: opened ? true : false
            radius: /*fullWidth ?*/ 0/* : Units.dp(2)*/
            backgroundColor: color_main
            //height: okButton.y - (password_2.y + password_2.height)
            width: loginWindow.width - (windowBorderWidth*2)

            anchors {
                horizontalCenter: parent.horizontalCenter
                leftMargin: windowBorderWidth
                top: password_2.bottom
                bottom: okButton.top
                //leftMargin: 0/*fullWidth ? 0 : Units.dp(16)*/
                topMargin: snackbar.opened ? spacing :  (okButton.y - (password_2.y + password_2.height))

                Behavior on topMargin {
                    NumberAnimation { duration: 300 }
                }
            }
            opacity: opened ? 1 : 0
            property int buttonState
            property string buttonText/*: "Resolve"*/
            property color buttonColor
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
            //TODO it's fast hack. good architercture design needed (control point is errorMessage text... bad idea)
            onTextChanged: {
                if(text === errorMessage[3]){
                    buttonText = "Change Password"
                    buttonState = 0
                }
                else if(text === errorMessage[4]){
                    buttonText = qsTr("Resolve")
                    buttonState = 1
                }
                else {
                    buttonText = ""
                }
            }
            //            onClicked: {
            //                if(snackButton.opacity !== 0){
            //                    userName.text = "SNACKBAR CLICKED!"
            //                }
            //            }
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
                font.pixelSize: mainFontSize
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

            Dicty.Button {
                id: snackButton
                opacity: snackbar.buttonText == "" ? 0 : 1
                enabled: snackButton.opacity ? true : false
                backgroundColor: color_background
                dct_fontPixelSize: mainFontSize
                dct_fontFamily: mainFont
                text: snackbar.buttonText
                context: "snackbar"
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
                onClicked: {
                    if(snackbar.buttonState === 1){
                        if(usersLoginsView.opened)
                            usersLoginsView.close();
                        else usersLoginsView.open();
                    }
                    else if (snackbar.buttonState === 0){
                        setPasswordChangingState()
                    }
                }
            }

            Behavior on opacity {
                NumberAnimation { duration: 300 }
            }
        }
        // }

        Dicty.Button {
            id: okButton
            text: qsTr("Ok")
            width: loginWindow.width/2 - windowBorderWidth /*(userName.width/2) - (buttMargin/2)*/
            height: buttonChangeWindowForm.height /*userName.height*/
            backgroundColor: color_nearBackground
            dct_radius: 0
            dct_fontPixelSize: mainFontSize
            dct_fontFamily: mainFont
            anchors{
                bottom: parent.bottom
                left: parent.left
                bottomMargin: windowBorderWidth
                leftMargin: windowBorderWidth
            }

            onClicked: {
                if(snackbar.opened) snackbar.opened = false

                if(userName.text === "") {
                    if(userName.focus !== true) userName.focus = true
                    userName.color = color_error
                    nameErrorAnimation.start()
                    getErrorMessage(errorMessage[0])
                    return;
                } else
                    if(userName.hasError) {
                        getErrorMessage(errorMessage[1])
                        return;
                    } else
                        if((!userName.wasRegistered) && (currentForm === 0)){
                            getErrorMessage(errorMessage[4])
                            return;
                        } else
                            if(password_1.text === ""){
                                if(password_1.focus !== true) password_1.focus = true
                                password_1.color = color_error
                                password_2.color = color_error
                                passwordErrorAnimation.start()
                                getErrorMessage(errorMessage[2])
                                return;
                            }
                if(currentForm === 1 || currentForm === 2){
                    if(password_1.text === password_2.text){
                        if(currentForm === 2) {passwordChangedConfirmDialog.show(); return;}
                        checkUser(userName.text, password_1.text, currentForm);
                        return;
                    }
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
                //passwordChangedConfirmDialog.show()
            }


        }

        Dicty.Button{
            id: cancelButton
            backgroundColor: color_nearBackground
            width: okButton.width
            height: okButton.height
            anchors.left: okButton.right
            anchors.top: okButton.top
            dct_radius: 0
            dct_fontPixelSize: mainFontSize
            dct_fontFamily: mainFont
            text: qsTr("Cancel")

            onClicked: {
                //passwordChangedConfirmDialog.close()
                //                if(currentForm === 2) {changeCurrentState(); return;}
                //                else
                loginWindow.closeWindow();
                //loginWindow.close()
                //canceled()
                // snackbar.open("sjlfjfkljd skldjflksd j skljd skdj lskdj skldj lksdj sdk jsdklj !!! lkdjfldkj kl!!! テキストを折り返します")
            }

        }

        //===================================
        //        SequentialAnimation {
        //            id: changeWindowStateAnimation
        //            running: false
        //            NumberAnimation { target: password_2; property: "opacity"; to: password_2.opacity; duration: 1000}
        //        }

        SequentialAnimation {
            id: onCloseAnimation
            running: false
            NumberAnimation { target: loginWindow; property: "opacity"; to: 0;  easing.type: Easing.Bezier; duration: 700}
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
            //            ColorAnimation {
            //                target: snackbar;
            //                easing.type: Easing.InCubic
            //                property: "backgroundColor";
            //                from: color_error; to: color_main; duration: snackbar.duration/2
            //            }
            ColorAnimation { target: windowFrame; easing.type: Easing.InCubic; property: "border.color"; from: color_error; to: color_main; duration: snackbar.duration/2}

        }
        SequentialAnimation {
            id: passwordErrorAnimation
            running: false
            ColorAnimation { target: password_1; easing.type: Easing.InCubic; property: "color"; from: color_error; to: color_highlight; duration: snackbar.duration/2}
            ColorAnimation { target: password_2; easing.type: Easing.InCubic; property: "color"; from: color_error; to: color_highlight; duration: snackbar.duration/2}
        }
    }

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //+++++++++++++++++++ USER LOGIN LIST +++++++++++++++++++++++++++++++++++++++++++++
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Item {
        id: usersLoginsView

        property bool autoFlick: true
        property bool opened: false

        opacity: usersLoginsView.opened ? 1.0 : 0.0
        enabled: usersLoginsView.opened ? true : false
        anchors {
            fill: parent
            //centerIn: parent
            //horizontalCenter: parent.horizontalCenter
            leftMargin: usersLoginsView.opened ? 0 : loginWindow.width

            Behavior on leftMargin {
                NumberAnimation { duration: changeStateDuratin;/* easing.type: userLVItem.opened ? Easing.OutCubic : Easing.InCubic*/ }
            }
        }
        Behavior on opacity {
            NumberAnimation { duration: changeStateDuratin; /*easing.type: userLVItem.opened ? Easing.OutCubic : Easing.InCubic*/}
        }
        function open() {
            //userName.text = ""
            if(opened === true) return
            opened = true;

        }
        function close() {
            if(opened === false) return
            opened = false;

        }
        Rectangle {
            id: registeredUsers
            width: loginWindow.width
            height: buttonChangeWindowForm.height
            color: buttonChangeWindowForm.backgroundColor
            //            x: parent.x+windowFrame.border.width
            //            y: parent.y+windowFrame.border.width
            z: usersLoginsView.opened ? 5 : -5
            ActionButton {
                id: backToSL
                backgroundColor: color_background
                iconColor: color_main
                isMiniSize: true
                elevation: 0
                z: parent.z + 1
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: 12
                }

                action: Action {
                    id: addContent
                    text: qsTr("&Back")
                    //                    shortcut: ""
                    onTriggered: usersLoginsView.close()
                }
                iconName: "navigation/arrow_back"
            }
            Text{
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: mainFontSize
                //wrapMode: Text.WordWrap

                //font.weight: light
                font.family: mainFont
                text: qsTr("Registered Users")
                color: buttonChangeWindowForm.textColor
            }
            MouseArea{
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

        Flickable {
            id: flickable
            //interactive: true
            anchors {
                //horizontalCenter: parent.horizontalCenter
                right: parent.right
                left: parent.left
                top: registeredUsers.bottom
                bottom: parent.bottom
                rightMargin: 16
                leftMargin: 16
                topMargin: 16
                bottomMargin: 16
            }
            //            width: parent.width
            //            height: parent.height-registeredUsers.height
            //            opacity: parent.opened ? 1 : 0
            //            Behavior on opacity {
            //                NumberAnimation { duration: changeStateDuratin; easing.type: Easing.InCubic }
            //            }
            //clip: true

            contentHeight: Math.max(userList.implicitHeight, height)

            Column{
                id: userList
                anchors.fill: parent

                Repeater{
                    model: userListModel
                    delegate:  ListItem.Standard{
                        text: modelData
                        onClicked: {
                            if(currentForm === 1)changeCurrentState()
                            usersLoginsView.close()
                            userName.text = modelData
                            snackbar.opened = false
                        }
                    }
                }
            }
        }

        Dicty.Scrollbar {
            id: scrollArea
            flickableItem: flickable
            //fillColor: color_main
        }
    }
}
    //PopupBase {

    //    id: passwordChangedConfirmDialog
    //}
    Dialog {
        id: passwordChangedConfirmDialog
        property string message: qsTr("Password for ") + userName.text + qsTr(" will Changed") //TODO check translation
        title: qsTr("Password Changing Status")
        text: passwordChangedConfirmDialog.message
        //hasActions: true
        onAccepted: {
            checkUser(userName.text, password_1.text, currentForm);
        }
        //        onShowingChanged: {
        //         log_reg_View.enabled = passwordChangedConfirmDialog.showing ? false : true
        //        }
    }
}

//    Loader {
//        id: usersLoginsView
//        property bool opened: false
//        anchors.fill: parent
//        //asynchronous: true
//        asynchronous: false
//        visible: opened ? status == Loader.Ready : false
//        // selectedComponent will always be valid, as it defaults to the first component
//        source: {
//            Qt.resolvedUrl("DictyQMLComponents/UserNameList.qml")
//            }
//    function open() {
//        //userName.text = ""
//        if(opened === true) return
//        opened = true;

//    }
//    function close() {
//        if(opened === false) return
//        opened = false;

//    }
//        }


//    ProgressCircle {
//        anchors.centerIn: parent
//        color: Theme.lightDark(color_background,
//                              Theme.light.textColor,
//                              Theme.dark.textColor)
//        visible: usersLoginsView.opened ? usersLoginsView.status == Loader.Loading : false
//    }
