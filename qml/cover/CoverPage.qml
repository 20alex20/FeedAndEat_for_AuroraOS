import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {
    CoverTemplate {
        primaryText: "CookbooK"
        secondaryText: "Recipes for everyone"
        icon {
            source: Qt.resolvedUrl("../images/coverLogo.png")
            sourceSize.width: icon.width
            sourceSize.height: icon.height
        }
    }
}
