import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Home 1.0

Item {
    signal recipeClicked
    property string name: ""
    property string image: ""
    property int servingsNumber: 0
    property int instructionsNumber: 0

    height: column.height

    Rectangle {
        anchors.fill: parent
        color: Theme.highlightBackgroundColor
    }

    MouseArea {
        anchors.fill: parent
        onClicked: recipeClicked()
    }

    Column {
        id: column
        width: parent.width
        spacing: Theme.paddingSmall

        Image {
            width: parent.width
            height: parent.width * 3 / 4
            fillMode: Image.PreserveAspectCrop
            source: image
        }

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 2 * Theme.paddingMedium
            spacing: Theme.paddingMedium

            Label {
                width: parent.width
                bottomPadding: (2 - lineCount) * Theme.fontSizeLarge
                font.family: Theme.fontFamilyHeading
                font.pixelSize: Theme.fontSizeLarge
                font.bold: true
                color: Theme.primaryColor
                text: name
                wrapMode: Text.Wrap
                maximumLineCount: 2
                truncationMode: TruncationMode.Elide
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
                        source: "../icons/servings.svg"
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
                        source: "../icons/steps.svg"
                    }
                }
            }
        }
    }
}
