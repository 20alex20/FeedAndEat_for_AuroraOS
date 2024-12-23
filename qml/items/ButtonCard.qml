import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias text: label.text
    signal clicked()

    height: label.height
    border.width: Theme.paddingSmall
    border.color: Theme.highlightColor
    color: Theme.highlightBackgroundColor

    Label {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width

        topPadding: Theme.paddingMedium
        bottomPadding: Theme.paddingMedium
        leftPadding: Theme.paddingSmall
        rightPadding: Theme.paddingSmall
        font.pixelSize: Theme.fontSizeLarge
        font.bold: true
        color: Theme.primaryColor
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
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
