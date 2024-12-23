import QtQuick 2.0
import Sailfish.Silica 1.0

Label {
    property real incompleteHeight: Theme.paddingSmall + 2*contentHeight + 2*Theme.paddingMedium +
                                    (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2
    function getHeight(width) {
        return width*3/4 + incompleteHeight
    }

    opacity: 0.0
    font.pixelSize: Theme.fontSizeLarge
}
