import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    function setLoading() {
        row.model.clear()
        rowLoading.visible = true
        rowError.visible = false
        row.visible = false
    }
    function setError() {
        row.model.clear()
        rowLoading.visible = false
        rowError.visible = true
        row.visible = false
    }
    function setSuccess(recipes) {
        row.model.clear()
        for (var i = 0; i < recipes.length; i++)
            row.model.append({ "ne": recipes[i].getName(),
                               "ie": recipes[i].getImage(),
                               "sr": recipes[i].getServingsNumber(),
                               "ir": recipes[i].getInstructionsNumber() })
        rowLoading.visible = false
        rowError.visible = false
        row.visible = true
    }
    property bool isEmpty: row.model.count === 0
    property string title: ""
    signal recipeClicked(int index)
    signal reloadCollection()

    spacing: Theme.paddingLarge
    property real recipeHeight: 3*(parent.width - 3*Theme.paddingLarge)/8 + Theme.paddingSmall + 2*textMetrics.contentHeight +
                                2*Theme.paddingMedium + (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2
    Label { id: textMetrics; font.pixelSize: Theme.fontSizeLarge }

    Label {
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: Theme.fontFamilyHeading
        font.pixelSize: Theme.fontSizeHuge
        font.bold: true
        color: Theme.highlightColor
        text: title
    }
    BusyIndicator {
        id: rowLoading
        width: parent.width
        height: recipeHeight

        size: Theme.itemSizeHuge
        running: visible
    }
    Item {
        id: rowError
        width: parent.width
        height: recipeHeight

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: button.top
            anchors.bottomMargin: Theme.paddingLarge

            font.family: Theme.fontFamilyHeading
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.primaryColor
            text: "Loading error"
        }
        Button {
            id: button
            anchors.centerIn: parent
            text: "Retry"
            onClicked: reloadCollection()
        }
    }
    ListView {
        id: row
        width: parent.width
        height: recipeHeight

        model: ListModel { }
        orientation: ListView.Horizontal
        spacing: Theme.paddingLarge
        delegate: RecipeCard {
            width: (row.width - 3*Theme.paddingLarge)/2
            name: ne
            image: ie
            servingsNumber: sr
            instructionsNumber: ir
            onClicked: recipeClicked(index)
        }
    }
}
