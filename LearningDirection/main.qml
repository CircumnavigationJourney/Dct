////для рисования деревьев нужно искать fractal tree
//import QtQuick 2.4
//import QtQuick.Controls 1.3
//import QtQuick.Layouts 1.1
//import Material 0.1
import QtQuick 2.3
import Material 0.1
import Material.ListItems 0.1 as ListItem
ApplicationWindow {

    width: 800
    height: 700
    id: mainWindow
    title: qsTr("Словарь")
    Component.onCompleted: Units.multiplier = 2.5
    theme {
        primaryColor: Palette.colors["blue"]["500"]
        primaryDarkColor: Palette.colors["blue"]["700"]
        accentColor: Palette.colors["teal"]["500"]
        tabHighlightColor: "white"
    }

    property var vocabulary: [
        "word"
    ]

    property var tests: [

    ]

    property var statistics: [

    ]

    property var sections: [ vocabulary, tests, statistics ]

    property var sectionTitles: [ qsTr("Vocabularies"), qsTr("Tests"), qsTr("Statistics") ]
    property string learningDirectionName
    property string selectedComponent: vocabulary[0]
    initialPage: TabbedPage {
        id: page
        title: learningDirectionName
        tabs: navDrawer.enabled ? [] : sectionTitles
        //actionBar.maxActionCount: 1
        actions: [

            //            Action {
            //                iconName: "image/color_lens"
            //                name: "Colors"
            ////                onTriggered: colorPicker.show()
            //            },

            Action {
                iconName: "action/settings"
                name: "Settings"
                hoverAnimation: true
            },


            Action {
                iconName: "action/language"
                name: "Language"
                enabled: true
                hoverAnimation: true
            },

            Action {
                iconName: "action/account_circle"
                name: "Accounts"
            }
        ]
        backAction: navDrawer.action

        NavigationDrawer {
            id: navDrawer
            enabled: page.width < Units.dp(800)

            Flickable {
                anchors.fill: parent

                contentHeight: Math.max(content.implicitHeight, height)

                Column {
                    id: content
                    anchors.fill: parent

                    Repeater {
                        model: sections

                        delegate: Column {
                            width: parent.width

                            ListItem.Subheader {
                                text: sectionTitles[index]
                            }

                            Repeater {
                                model: modelData
                                delegate: ListItem.Standard {
                                    text: modelData
                                    selected: modelData == mainWindow.selectedComponent
                                    onClicked: {
                                        mainWindow.selectedComponent = modelData
                                        navDrawer.close()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Repeater {
            model: !navDrawer.enabled ? sections : 0

            delegate: Tab {
                title: sectionTitles[index]

                //property string selectedComponent: modelData[0]
                property var section: modelData

                sourceComponent: tabDelegate
            }
        }
        Loader {
            anchors.fill: parent
            sourceComponent: tabDelegate

            property var section: []
            visible: navDrawer.enabled
        }
    }
    Component {
        id: tabDelegate

        Item {
            Sidebar {
                id: sidebar

                expanded: !navDrawer.enabled

                Column {
                    width: parent.width

                    Repeater {
                        model: section
                        delegate: ListItem.Standard {
                            text: modelData
                            selected: modelData == selectedComponent
                            onClicked: selectedComponent = modelData
                        }
                    }
                }
            }
            Flickable {
                id: flickable
                anchors {
                    left: sidebar.right
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                clip: true
                contentHeight: Math.max(example.implicitHeight + 40, height)
                Loader {
                    id: example
                    anchors.fill: parent
                    asynchronous: false
                    visible: status == Loader.Ready
                    // selectedComponent will always be valid, as it defaults to the first component
                    source: Qt.resolvedUrl("wordTable.qml")


                }
                //                Loader {
                //                    id: example
                //                    anchors.fill: parent
                //                    //asynchronous: true
                //                    asynchronous: false
                //                    visible: status == Loader.Ready
                //                    // selectedComponent will always be valid, as it defaults to the first component
                //                    source: {
                //                        if (navDrawer.enabled) {
                //                            return Qt.resolvedUrl("%1Demo.qml").arg(demo.selectedComponent.replace(" ", ""))
                //                        } else {
                //                            return Qt.resolvedUrl("%1Demo.qml").arg(selectedComponent.replace(" ", ""))
                //                        }
                //                    }
                //                }

                ProgressCircle {
                    anchors.centerIn: parent
                    visible: example.status == Loader.Loading
                }
            }
            Scrollbar {
                flickableItem: flickable
            }
        }
    }
    //        TabView {
    //            id: tabView
    //            anchors.fill: parent
    //            currentIndex: page.selectedTab
    //            model: sections

    //            delegate: Item {
    //                width: tabView.width
    //                height: tabView.height
    //                clip: true

    //                property string selectedComponent: modelData[0]

    //                Sidebar {
    //                    id: sidebar

    //                    expanded: !navDrawer.enabled

    //                    Column {
    //                        width: parent.width

    //                        Repeater {
    //                            model: modelData
    //                            delegate: ListItem.Standard {
    //                                text: modelData
    //                                selected: modelData == selectedComponent
    //                                onClicked: selectedComponent = modelData
    //                            }
    //                        }
    //                    }
    //                }
    //                Flickable {
    //                    id: flickable
    //                    anchors {
    //                        left: sidebar.right
    //                        right: parent.right
    //                        top: parent.top
    //                        bottom: parent.bottom
    //                    }
    //                    clip: true
    //                    contentHeight: Math.max(example.implicitHeight + 40, height)
    //                    Loader {
    //                        id: example
    //                        anchors.fill: parent
    //                        asynchronous: false
    //                        visible: status == Loader.Ready
    //                        // selectedComponent will always be valid, as it defaults to the first component
    //                        source: Qt.resolvedUrl("wordTable.qml")


    //                    }

    //                    ProgressCircle {
    //                        anchors.centerIn: parent
    //                        visible: example.status == Loader.Loading
    //                    }
    //                }
    //                Scrollbar {
    //                    flickableItem: flickable
    //                }
    //            }
    //        }


}
