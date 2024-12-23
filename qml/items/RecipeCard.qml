import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias name: nameLabel.text
    property alias image: cardImage.source
    property alias servingsNumber: servingsNumberLabel.text
    property alias instructionsNumber: instructionsNumberLabel.text
    signal clicked()
    signal pressed()

    height: column.height
    color: Theme.highlightBackgroundColor

    Column {
        id: column
        width: parent.width
        spacing: Theme.paddingSmall

        Image {
            id: cardImage
            width: parent.width
            height: parent.width*3/4

            fillMode: Image.PreserveAspectCrop
            onStatusChanged: {
                if (status === Image.Error)
                    source = "../images/imageLoadingError.png"
            }
        }

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 2*Theme.paddingMedium
            spacing: Theme.paddingMedium

            Label {
                id: nameLabel
                width: parent.width
                font.family: Theme.fontFamilyHeading
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.primaryColor
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
                        id: servingsNumberLabel
                        font.pixelSize: Theme.fontSizeLarge
                        font.bold: true
                        color: Theme.primaryColor
                        opacity: 0.8
                    }
                }

                Row {
                    anchors.right: parent.right
                    spacing: Theme.paddingSmall

                    Label {
                        id: instructionsNumberLabel
                        font.pixelSize: Theme.fontSizeLarge
                        font.bold: true
                        color: Theme.primaryColor
                        opacity: 0.8
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

    MouseArea {
        anchors.fill: parent
        onClicked: {
            parent.clicked()
        }
        onPressed: {
            parent.pressed()
        }

        Rectangle {
            anchors.fill: parent
            visible: parent.pressed
            color: "#40000000"
        }
    }
}
