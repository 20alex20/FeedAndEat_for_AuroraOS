import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Recipe 1.0

Page {
    property Recipe recipe
    property int currentIndex: 0
    property var instructions
    property var checks: []
    property bool currentCheck: false
    property bool leavePage: false
    Component.onCompleted: {
        instructions = recipe.instructions
        for (var i = 0; i < recipe.instructionsNumber; i++)
            checks.push(false)
    }
    onCurrentIndexChanged: {
        currentCheck = checks[currentIndex]
    }

    id: page
    backNavigation: false

    Rectangle {
        id: top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        anchors.topMargin: Theme.horizontalPageMargin
        height: title.height
        color: Theme.highlightBackgroundColor

        Label {
            id: title
            width: parent.width

            padding: Theme.paddingMedium
            font.family: Theme.fontFamilyHeading
            font.pixelSize: (Theme.fontSizeHuge + Theme.fontSizeLarge)/2
            font.bold: true
            color: Theme.primaryColor
            text: "Step: " + (currentIndex + 1)
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: top.bottom
        anchors.bottom: bottom.top
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        anchors.topMargin: 2*Theme.paddingLarge
        anchors.bottomMargin: 2*Theme.paddingLarge
        height: instruction.height
        color: Theme.highlightBackgroundColor

        Flickable {
            id: flickable
            anchors.fill: parent
            anchors.margins: Theme.paddingMedium

            flickableDirection: Flickable.VerticalFlick
            contentWidth: instruction.width
            contentHeight: instruction.height

            Label {
                id: instruction
                width: flickable.width

                font.pixelSize: Theme.fontSizeLarge
                color: Theme.primaryColor
                text: instructions[currentIndex]
                wrapMode: Text.WordWrap
            }
        }
    }

    Column {
        id: bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        anchors.bottomMargin: Theme.horizontalPageMargin
        spacing: 2*Theme.paddingLarge

        Item {
            width: parent.width
            height: mark.height

            Rectangle {
                width: (parent.width - 2*Theme.paddingLarge)/3
                height: mark.height

                visible: currentIndex > 0
                color: Theme.highlightBackgroundColor

                Label {
                    anchors.centerIn: parent
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.primaryColor
                    text: "To previous"
                    horizontalAlignment: Text.AlignHCenter
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (currentIndex > 0)
                            currentIndex -= 1
                    }

                    Rectangle {
                        anchors.fill: parent
                        visible: parent.pressed
                        color: "#40000000"
                    }
                }
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: (parent.width - 2*Theme.paddingLarge)/3
                height: mark.height
                color: currentCheck ? Theme.highlightDimmerColor : Theme.highlightBackgroundColor

                Label {
                    id: mark
                    width: parent.width

                    padding: Theme.paddingMedium
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.primaryColor
                    text: currentCheck ? "Marked as completed" : "Mark as completed"
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                       checks[currentIndex] = !checks[currentIndex]
                       currentCheck = checks[currentIndex]
                    }

                    Rectangle {
                        anchors.fill: parent
                        visible: parent.pressed
                        color: "#40000000"
                    }
                }
            }

            Rectangle {
                anchors.right: parent.right
                width: (parent.width - 2*Theme.paddingLarge)/3
                height: mark.height

                visible: currentIndex < recipe.instructionsNumber - 1
                color: Theme.highlightBackgroundColor

                Label {
                    anchors.centerIn: parent
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.primaryColor
                    text: "To next"
                    horizontalAlignment: Text.AlignHCenter
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (currentIndex < recipe.instructionsNumber - 1)
                            currentIndex += 1
                    }

                    Rectangle {
                        anchors.fill: parent
                        visible: parent.pressed
                        color: "#40000000"
                    }
                }
            }
        }

        Rectangle {
            width: parent.width
            height: confirm.height
            color: Theme.highlightBackgroundColor

            Label {
                id: confirm
                width: parent.width

                padding: Theme.paddingMedium
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.primaryColor
                text: "Leave the instructions"
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    for (var i = 0; i < checks.length; i++)
                        if (!checks[i]) {
                            var dl = pageStack.push(dialog)
                            dl.accepted.connect(function() {
                                leavePage = true
                            })
                            return
                        }
                    backNavigation = true
                    pageStack.pop()
                }

                Rectangle {
                    anchors.fill: parent
                    visible: parent.pressed
                    color: "#40000000"
                }
            }

            Connections {
                target: pageStack
                onBusyChanged: {
                    if (leavePage && !busy) {
                        leavePage = false
                        pageStack.pop(pageStack.previousPage(pageStack.currentPage), PageStackAction.Immediate)
                    }
                }
            }

            Component {
                id: dialog

                Dialog {
                    DialogHeader {
                        id: header
                        title: "Are you sure you want to leave the instructions?"
                    }
                    Label {
                        anchors.top: header.bottom
                        leftPadding: Theme.horizontalPageMargin
                        rightPadding: Theme.horizontalPageMargin
                        font.pixelSize: Theme.fontSizeLarge
                        color: Theme.highlightColor
                        text: "You have not marked all steps as completed"
                    }
                }
            }
        }
    }
}
