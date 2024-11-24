import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Home 1.0
import "../items"

Page {
    property HomeViewModel viewModel: HomeFeature.getHomeViewModel(this);
    Component.onCompleted: viewModel.bind()

    property HomeViewModelState state: viewModel.state
    onStateChanged: {
        if (state.dailyRecipe === null)
            dailyRecipe.setLoading()
        else
            dailyRecipe.setRecipe(state.dailyRecipe)

        if (state.breakfastRecipesStatus === HomeViewModelState.Loading)
            row1.setLoading()
        else if (state.breakfastRecipesStatus === HomeViewModelState.Error)
            row1.setError()
        else if (row1.isEmpty)
            row1.setSuccess(state.breakfastRecipes)

        if (state.drinkRecipesStatus === HomeViewModelState.Loading)
            row2.setLoading()
        else if (state.drinkRecipesStatus === HomeViewModelState.Error)
            row2.setError()
        else if (row2.isEmpty)
            row2.setSuccess(state.drinkRecipes)

        if (state.recipesForBigGroupStatus === HomeViewModelState.Loading)
            row3.setLoading()
        else if (state.recipesForBigGroupStatus === HomeViewModelState.Error)
            row3.setError()
        else if (row3.isEmpty)
            row3.setSuccess(state.recipesForBigGroup)

        if (state.lowCalorieRecipeStatus === HomeViewModelState.Loading)
            row4.setLoading()
        else if (state.lowCalorieRecipeStatus === HomeViewModelState.Error)
            row4.setError()
        else if (row4.isEmpty)
            row4.setSuccess(state.lowCalorieRecipes)
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
            spacing: Theme.paddingLarge * 2

            DailyRecipe {
                id: dailyRecipe
                width: parent.width
                onReloadRecipe: viewModel.reloadDailyRecipe()
            }
            RecipesCollection {
                id: row1
                width: parent.width
                title: "For your breakfast"
                onReloadCollection: viewModel.reloadBreakfastRecipes()
            }
            RecipesCollection {
                id: row2
                width: parent.width
                title: "Let's have a drink"
                onReloadCollection: viewModel.reloadDrinkRecipes()
            }
            RecipesCollection {
                id: row3
                width: parent.width
                title: "For you and your friends"
                onReloadCollection: viewModel.reloadRecipesForBigGroup()
            }
            RecipesCollection {
                id: row4
                width: parent.width
                title: "Low calorie"
                onReloadCollection: viewModel.reloadLowCalorieRecipes()
            }

            Button {
                text: "search"
                onClicked: {
                    pageStack.push("SearchPage.qml")
                }
            }
        }
    }
}
