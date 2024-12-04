import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    signal clicked

    height: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2 + 2*Theme.paddingLarge
    color: Theme.highlightBackgroundColor

    Label {
        id: searchQuery
        anchors.left: parent.left
        anchors.right: searchIcon.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge

        font.pixelSize: Theme.fontSizeLarge
        color: Theme.secondaryColor
        text: "Search"
    }
    Icon {
        id: searchIcon
        anchors.right: parent.right
        anchors.rightMargin: Theme.paddingLarge
        anchors.verticalCenter: parent.verticalCenter
        width: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2
        height: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2

        color: Theme.primaryColor
        source: "../icons/search.svg"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
           parent.clicked()
        }

        Rectangle {
            anchors.fill: parent
            visible: parent.pressed
            color: "#40000000"
        }
    }
}
