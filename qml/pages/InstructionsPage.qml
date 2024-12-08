import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Instructions 1.0
import "../items"

Page {
    property var instructions
    property int currentIndex: 0
    property var checks: []
    property InstructionsViewModel viewModel: InstructionsFeature.getInstructionsViewModel(this)
    Component.onCompleted: {
        viewModel.bind(instructions.length)
    }
    Connections {
        target: viewModel
        onStateChanged: {
            checks = viewModel.state.checks
        }
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
        color: Theme.highlightBackgroundColor

        Flickable {
            id: flickable
            anchors.fill: parent
            anchors.margins: Theme.paddingMedium

            clip: true
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
            height: check.height

            ButtonCard {
                width: (parent.width - 2*Theme.paddingLarge)/3
                height: check.height

                visible: currentIndex > 0
                text: "To previous"
                onClicked: {
                    if (currentIndex > 0)
                        currentIndex -= 1
                }
            }
            ButtonCard {
                id: check
                anchors.horizontalCenter: parent.horizontalCenter
                width: (parent.width - 2*Theme.paddingLarge)/3

                color: checks[currentIndex] ? Theme.highlightDimmerColor : Theme.highlightBackgroundColor
                text: checks[currentIndex] ? "Marked as completed" : "Mark as completed"
                onClicked: {
                    viewModel.changeCheck(currentIndex)
                }
            }
            ButtonCard {
                anchors.right: parent.right
                width: (parent.width - 2*Theme.paddingLarge)/3
                height: check.height

                visible: currentIndex < instructions.length - 1
                text: "To next"
                onClicked: {
                    if (currentIndex < instructions.length - 1)
                        currentIndex += 1
                }
            }
        }

        ButtonCard {
            property bool leavePage: false

            id: leaveInstructions
            width: parent.width

            text: "Leave the instructions"
            onClicked: {
                for (var i = 0; i < checks.length; i++)
                    if (!checks[i]) {
                        pageStack.push(dialog).accepted.connect(function() {
                            leaveInstructions.leavePage = true
                        })
                        return
                    }
                pageStack.pop()
            }

            Connections {
                target: pageStack
                onBusyChanged: {
                    if (leaveInstructions.leavePage && !busy) {
                        leaveInstructions.leavePage = false
                        pageStack.pop()
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
                        color: Theme.primaryColor
                        text: "You have not marked all steps as completed"
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }
    }
}
