import QtQuick 2.0
import Sailfish.Silica 1.0
import "../dataObjects"

Column {
    property bool isEmpty: row.model.count === 0
    property alias title: titleLabel.text
    signal recipeClicked(int index)
    signal reloadCollection()
    function setLoading() {
        rowLoading.visible = true
        rowError.visible = false
        row.visible = false
    }
    function setError() {
        rowLoading.visible = false
        rowError.visible = true
        row.visible = false
    }
    function setSuccess(recipes) {
        row.model.clear()
        for (var i = 0; i < recipes.length; i++)
            row.model.append({ "ne": recipes[i].name,
                               "ie": recipes[i].image,
                               "sr": recipes[i].servingsNumber,
                               "ir": recipes[i].instructionsNumber })
        rowLoading.visible = false
        rowError.visible = false
        row.visible = true
    }

    spacing: Theme.paddingLarge
    property real recipeHeight: recipeCardHeight.getHeight((row.width - 3*Theme.paddingLarge)/2)

    Label {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: Theme.fontFamilyHeading
        font.pixelSize: Theme.fontSizeHuge
        font.bold: true
        color: Theme.highlightColor

        RecipeCardHeight { id: recipeCardHeight }
    }

    BusyIndicator {
        id: rowLoading
        width: parent.width
        height: recipeHeight

        visible: true
        size: Theme.itemSizeHuge
        running: visible
    }

    Item {
        id: rowError
        width: parent.width
        height: recipeHeight
        visible: false

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
            onClicked: {
                reloadCollection()
            }
        }
    }

    ListView {
        id: row
        width: parent.width
        height: recipeHeight

        visible: false
        model: ListModel { }
        orientation: ListView.Horizontal
        spacing: Theme.paddingLarge
        delegate: RecipeCard {
            width: (row.width - 3*Theme.paddingLarge)/2
            name: ne
            image: ie
            servingsNumber: sr
            instructionsNumber: ir
            onClicked: {
                recipeClicked(index)
            }
        }
    }
}
