import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Home 1.0
import "../items"

Page {
    property HomeViewModel viewModel: HomeFeature.getHomeViewModel(this);
    Component.onCompleted: viewModel.bind()

    property HomeViewModelState state: viewModel.state
    onStateChanged: {
        if (state.dailyRecipe === null) {
            dailyRecipeLoading.visible = true
            dailyRecipe.visible = false
        }
        else {
            dailyRecipe.name = state.dailyRecipe.getName()
            dailyRecipe.image = state.dailyRecipe.getImage()
            dailyRecipe.servingsNumber = state.dailyRecipe.getServingsNumber()
            dailyRecipe.instructionsNumber = state.dailyRecipe.getInstructionsNumber()
            dailyRecipeLoading.visible = false
            dailyRecipe.visible = true
        }
        if (state.breakfastRecipesStatus === HomeViewModelState.Loading) {
            row1.model.clear()
            row1Loading.visible = true
            row1Error.visible = false
            row1.visible = false
        }
        else if (state.breakfastRecipesStatus === HomeViewModelState.Error) {
            row1.model.clear()
            row1Loading.visible = false
            row1Error.visible = true
            row1.visible = false
        }
        else if (row1.model.count === 0) {
            var recipes = state.breakfastRecipes
            console.log(recipes.length)
            for (var i = 0; i < recipes.length; i++)
                row1.model.append({ "ne": recipes[i].getName(),
                                    "ie": recipes[i].getImage(),
                                    "sr": recipes[i].getServingsNumber(),
                                    "ir": recipes[i].getInstructionsNumber() })
            row1Loading.visible = false
            row1Error.visible = false
            row1.visible = true
        }
    }

    Flickable {
        anchors.fill: parent
        anchors.margins: Theme.paddingMedium
        flickableDirection: Flickable.VerticalFlick

        Column {
            property real notCompleteRecipeCardHeight: Theme.paddingSmall + 2*Theme.fontSizeLarge + 2*Theme.paddingMedium +
                                                       (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2
            id: page
            anchors.fill: parent
            spacing: Theme.paddingLarge * 2

            Column {
                width: parent.width
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
                    height: parent.width/2 + page.notCompleteRecipeCardHeight
                    size: Theme.itemSizeHuge
                    running: visible
                }
                RecipeCard {
                    id: dailyRecipe
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width * 2 / 3
                }
            }

            Column {
                width: parent.width
                spacing: Theme.paddingLarge

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: Theme.fontFamilyHeading
                    font.pixelSize: Theme.fontSizeHuge
                    font.bold: true
                    color: Theme.highlightColor
                    text: "For breakfast"
                }
                BusyIndicator {
                    id: row1Loading
                    width: parent.width
                    height: (parent.width - 3 * Theme.paddingLarge) / 2 + page.notCompleteRecipeCardHeight
                    size: Theme.itemSizeHuge
                    running: visible
                }
                Item {
                    id: row1Error
                    width: parent.width
                    height: (parent.width - 3 * Theme.paddingLarge) / 2 + page.notCompleteRecipeCardHeight

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
                        onClicked: viewModel.reloadBreakfastRecipes()
                    }
                }
                ListView {
                    id: row1
                    width: parent.width
                    height: (parent.width - 3 * Theme.paddingLarge) / 2 + page.notCompleteRecipeCardHeight
                    model: ListModel { }
                    orientation: ListView.Horizontal
                    spacing: Theme.paddingLarge
                    delegate: RecipeCard {
                        width: (page.width - 3 * Theme.paddingLarge) / 2
                        name: ne
                        image: ie
                        servingsNumber: sr
                        instructionsNumber: ir
                    }
                }
            }

            /*Column {
                width: parent.width
                spacing: 32

                Label {
                    text: "For breakfast"
                    color: Theme.highlightColor
                    font.family: Theme.fontFamilyHeading
                    font.pixelSize: 40
                    font.bold: true
                }
                Row {
                    spacing: 8

                    ListModel {
                        id: row2Model
                    }
                    Repeater {
                        model: row2Model

                        RecipeCard {
                            width: page.width
                            name: na
                            image: im
                            amountOfServings: as
                            amountOfInstructions: ai
                        }
                    }
                }
            }

            Column {
                width: parent.width
                spacing: 32

                Label {
                    text: "For breakfast"
                    color: Theme.highlightColor
                    font.family: Theme.fontFamilyHeading
                    font.pixelSize: 40
                    font.bold: true
                }
                Row {
                    spacing: 8

                    ListModel {
                        id: row3Model
                    }
                    Repeater {
                        model: row3Model

                        RecipeCard {
                            width: page.width
                            name: na
                            image: im
                            amountOfServings: as
                            amountOfInstructions: ai
                        }
                    }
                }
            }

            Column {
                width: parent.width
                spacing: 32

                Label {
                    text: "For breakfast"
                    color: Theme.highlightColor
                    font.family: Theme.fontFamilyHeading
                    font.pixelSize: 40
                    font.bold: true
                }
                Row {
                    spacing: 8

                    ListModel {
                        id: row4Model
                    }
                    Repeater {
                        model: row4Model

                        RecipeCard {
                            width: page.width
                            name: na
                            image: im
                            amountOfServings: as
                            amountOfInstructions: ai
                        }
                    }
                }
            }*/
        }
    }
}
