import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Home 1.0
import "../items"

Page {
    property HomeViewModel viewModel: HomeFeature.getHomeViewModel(this);
    Component.onCompleted: {
        viewModel.bind()
    }
    Connections {
        target: viewModel
        onStateChanged: {
            if (viewModel.state.dailyRecipe === null)
                dailyRecipe.setLoading()
            else
                dailyRecipe.setRecipe(viewModel.state.dailyRecipe)

            if (viewModel.state.breakfastRecipesStatus === HomeViewModelState.Loading)
                row1.setLoading()
            else if (viewModel.state.breakfastRecipesStatus === HomeViewModelState.Error)
                row1.setError()
            else if (row1.isEmpty)
                row1.setSuccess(viewModel.state.breakfastRecipes)

            if (viewModel.state.drinkRecipesStatus === HomeViewModelState.Loading)
                row2.setLoading()
            else if (viewModel.state.drinkRecipesStatus === HomeViewModelState.Error)
                row2.setError()
            else if (row2.isEmpty)
                row2.setSuccess(viewModel.state.drinkRecipes)

            if (viewModel.state.recipesForBigGroupStatus === HomeViewModelState.Loading)
                row3.setLoading()
            else if (viewModel.state.recipesForBigGroupStatus === HomeViewModelState.Error)
                row3.setError()
            else if (row3.isEmpty)
                row3.setSuccess(viewModel.state.recipesForBigGroup)

            if (viewModel.state.lowCalorieRecipeStatus === HomeViewModelState.Loading)
                row4.setLoading()
            else if (viewModel.state.lowCalorieRecipeStatus === HomeViewModelState.Error)
                row4.setError()
            else if (row4.isEmpty)
                row4.setSuccess(viewModel.state.lowCalorieRecipes)
        }
    }

    clip: true

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

            Rectangle {
                width: parent.width
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
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        pageStack.push("SearchPage.qml")
                    }
                }
                Rectangle {
                    anchors.fill: parent
                    visible: mouseArea.pressed
                    color: "#40000000"
                }
            }

            DailyRecipe {
                id: dailyRecipe
                width: parent.width
                onReloadRecipe: {
                    viewModel.reloadDailyRecipe()
                }
            }
            RecipesCollection {
                id: row1
                width: parent.width
                title: "For your breakfast"
                onReloadCollection: {
                    viewModel.reloadBreakfastRecipes()
                }
            }
            RecipesCollection {
                id: row2
                width: parent.width
                title: "Let's have a drink"
                onReloadCollection: {
                    viewModel.reloadDrinkRecipes()
                }
            }
            RecipesCollection {
                id: row3
                width: parent.width
                title: "For you and your friends"
                onReloadCollection: {
                    viewModel.reloadRecipesForBigGroup()
                }
            }
            RecipesCollection {
                id: row4
                width: parent.width
                title: "Low calorie"
                onReloadCollection: {
                    viewModel.reloadLowCalorieRecipes()
                }
            }
        }
    }
}
