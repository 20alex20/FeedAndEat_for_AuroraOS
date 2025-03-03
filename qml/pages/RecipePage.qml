import QtQuick 2.0
import Sailfish.Silica 1.0
import FeedAndEat.Recipe 1.0
import "../items"

Page {
    property Recipe recipe

    Flickable {
        id: flickable
        anchors.fill: parent
        anchors.margins: Theme.horizontalPageMargin

        flickableDirection: Flickable.VerticalFlick
        contentWidth: column.width
        contentHeight: column.height

        Column {
            id: column
            width: flickable.width
            spacing: 2*Theme.paddingLarge

            Image {
                width: parent.width
                height: parent.width*3/4

                fillMode: Image.PreserveAspectCrop
                source: recipe.image
                onStatusChanged: {
                    if (status === Image.Error)
                        visible = false
                }
            }

            Rectangle {
                width: parent.width
                height: info.height + 2*Theme.paddingMedium
                color: Theme.highlightBackgroundColor

                Column {
                    id: info
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.topMargin: Theme.paddingMedium
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.rightMargin: Theme.paddingMedium
                    spacing: Theme.paddingMedium

                    Label {
                        width: parent.width
                        font.family: Theme.fontFamilyHeading
                        font.pixelSize: (Theme.fontSizeHuge + Theme.fontSizeLarge)/2
                        font.bold: true
                        color: Theme.primaryColor
                        text: recipe.name
                        wrapMode: Text.WordWrap
                    }

                    Item {
                        width: parent.width
                        height: servingsNumber.height

                        Row {
                            id: servingsNumber

                            Label {
                                font.pixelSize: Theme.fontSizeLarge
                                color: Theme.primaryColor
                                text: "Servings: "
                            }
                            Label {
                                font.pixelSize: Theme.fontSizeLarge
                                font.bold: true
                                color: Theme.primaryColor
                                text: recipe.servingsNumber
                            }
                        }

                        Row {
                            anchors.right: parent.right

                            Label {
                                font.pixelSize: Theme.fontSizeLarge
                                color: Theme.primaryColor
                                text: "Steps: "
                            }
                            Label {
                                font.pixelSize: Theme.fontSizeLarge
                                font.bold: true
                                color: Theme.primaryColor
                                text: recipe.instructionsNumber
                            }
                        }
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: categories.height + 2*Theme.paddingMedium

                visible: categoriesRepeater.count > 0
                color: Theme.highlightBackgroundColor

                Column {
                    id: categories
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.topMargin: Theme.paddingMedium
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.rightMargin: Theme.paddingMedium
                    spacing: Theme.paddingMedium

                    Label {
                        width: parent.width
                        font.family: Theme.fontFamilyHeading
                        font.pixelSize: Theme.fontSizeLarge
                        font.bold: true
                        color: Theme.primaryColor
                        text: "Categories"
                        horizontalAlignment: Text.AlignHCenter
                    }
                    Flow {
                        width: parent.width
                        spacing: Theme.paddingMedium

                        Repeater {
                            id: categoriesRepeater
                            model: recipe.categories

                            Label {
                                font.pixelSize: Theme.fontSizeLarge
                                color: Theme.primaryColor
                                text: modelData
                            }
                        }
                    }
                }
            }

            ButtonCard {
                width: parent.width
                visible: recipe.instructionsNumber > 0
                text: "Open step-by-step instructions"
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("InstructionsPage.qml"), { "instructions": recipe.instructions })
                }
            }

            Rectangle {
                width: parent.width
                height: instructions.height + 2*Theme.paddingMedium

                visible: instructionsRepeater.count > 0
                color: Theme.highlightBackgroundColor

                Column {
                    id: instructions
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.topMargin: Theme.paddingMedium
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.rightMargin: Theme.paddingMedium
                    spacing: Theme.paddingMedium

                    Label {
                        width: parent.width
                        font.family: Theme.fontFamilyHeading
                        font.pixelSize: Theme.fontSizeLarge
                        font.bold: true
                        color: Theme.primaryColor
                        text: "Instructions"
                        horizontalAlignment: Text.AlignHCenter
                    }
                    Column {
                        width: parent.width
                        spacing: Theme.paddingMedium

                        Repeater {
                            id: instructionsRepeater
                            model: recipe.instructions

                            Label {
                                width: parent.width
                                leftPadding: Theme.iconSizeExtraSmall + Theme.paddingMedium
                                font.pixelSize: Theme.fontSizeLarge
                                color: Theme.primaryColor
                                text: modelData
                                wrapMode: Text.WordWrap

                                Rectangle {
                                    anchors.top: parent.top
                                    anchors.topMargin: (servingsNumber.height - Theme.iconSizeExtraSmall)/2
                                    width: Theme.iconSizeExtraSmall
                                    height: Theme.iconSizeExtraSmall

                                    radius: Theme.iconSizeExtraSmall/2
                                    color: Theme.highlightColor
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
