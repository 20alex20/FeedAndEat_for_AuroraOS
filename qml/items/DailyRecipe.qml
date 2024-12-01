import QtQuick 2.0
import Sailfish.Silica 1.0
import "../dataObjects"

Column {
    function setLoading() {
        dailyRecipeLoading.visible = true
        dailyRecipe.visible = false
    }
    function setRecipe(recipe) {
        dailyRecipe.isSuccess = recipe.isSuccess
        dailyRecipe.name = recipe.name
        dailyRecipe.image = recipe.image
        dailyRecipe.servingsNumber = recipe.servingsNumber
        dailyRecipe.instructionsNumber = recipe.instructionsNumber
        dailyRecipeLoading.visible = false
        dailyRecipe.visible = true
    }
    signal recipeClicked()
    signal reloadRecipe()

    spacing: Theme.paddingLarge

    Label {
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: Theme.fontFamilyHeading
        font.pixelSize: Theme.fontSizeHuge
        font.bold: true
        color: Theme.highlightColor
        text: "Daily recipe"
    }
    BusyIndicator {
        id: dailyRecipeLoading
        width: parent.width
        height: recipeCardHeight.getHeight(parent.width*2/3)
        RecipeCardHeight { id: recipeCardHeight }

        visible: true
        size: Theme.itemSizeHuge
        running: visible
    }
    RecipeCard {
        id: dailyRecipe
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*2/3

        visible: false
        onClicked: {
            if (name == "Loading error")
                reloadRecipe()
            else
                recipeClicked()
        }
    }
}
