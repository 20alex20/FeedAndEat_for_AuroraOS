import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    function setLoading() {
        dailyRecipeLoading.visible = true
        dailyRecipe.visible = false
    }
    function setRecipe(recipe) {
        dailyRecipe.name = recipe.getName()
        dailyRecipe.image = recipe.getImage()
        dailyRecipe.servingsNumber = recipe.getServingsNumber()
        dailyRecipe.instructionsNumber = recipe.getInstructionsNumber()
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
        height: parent.width/2 + Theme.paddingSmall + 2*textMetrics.contentHeight +
                2*Theme.paddingMedium + (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2

        size: Theme.itemSizeHuge
        running: visible

        Label {
            id: textMetrics
            font.pixelSize: Theme.fontSizeLarge
        }
    }
    RecipeCard {
        id: dailyRecipe
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*2/3

        onClicked: {
            if (name == "Loading error")
                reloadRecipe()
            else
                recipeClicked()
        }
    }
}
