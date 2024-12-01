import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property bool isSuccess: true
    property string name: ""
    property string image: ""
    property int servingsNumber: 0
    property int instructionsNumber: 0
    signal clicked()
    signal pressed()

    height: column.height

    Rectangle {
        anchors.fill: parent
        color: Theme.highlightBackgroundColor
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            parent.clicked()
        }
        onPressed: {
            parent.pressed()
        }
    }

    Column {
        id: column
        width: parent.width
        spacing: Theme.paddingSmall

        Image {
            width: parent.width
            height: parent.width*3/4

            fillMode: Image.PreserveAspectCrop
            source: image
        }

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 2*Theme.paddingMedium
            spacing: Theme.paddingMedium

            Label {
                width: parent.width
                font.family: Theme.fontFamilyHeading
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.primaryColor
                text: name
                wrapMode: Text.Wrap
                maximumLineCount: 2
                truncationMode: TruncationMode.Elide
                lineHeight: 3 - lineCount
            }

            Item {
                width: parent.width
                height: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2 + Theme.paddingMedium

                Row {
                    spacing: Theme.paddingSmall

                    Icon {
                        width: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2
                        height: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2

                        color: Theme.primaryColor
                        opacity: 0.8
                        source: Qt.resolvedUrl("../icons/servings.svg")
                    }
                    Label {
                        font.pixelSize: Theme.fontSizeLarge
                        font.bold: true
                        color: Theme.primaryColor
                        opacity: 0.8
                        text: servingsNumber
                    }
                }

                Row {
                    anchors.right: parent.right
                    spacing: Theme.paddingSmall

                    Label {
                        font.pixelSize: Theme.fontSizeLarge
                        font.bold: true
                        color: Theme.primaryColor
                        opacity: 0.8
                        text: instructionsNumber
                    }
                    Icon {
                        width: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2
                        height: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2

                        color: Theme.primaryColor
                        opacity: 0.8
                        source: Qt.resolvedUrl("../icons/steps.svg")
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        visible: mouseArea.pressed
        color: "#40000000"
    }
}
