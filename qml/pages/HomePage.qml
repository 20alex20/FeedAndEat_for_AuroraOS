import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Recipe 1.0
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

            if (viewModel.state.getCollectionStatus(HomeViewModelState.Breakfast) === HomeViewModelState.Loading)
                row1.setLoading()
            else if (viewModel.state.getCollectionStatus(HomeViewModelState.Breakfast) === HomeViewModelState.Error)
                row1.setError()
            else if (row1.isEmpty)
                row1.setSuccess(viewModel.state.getCollectionRecipes(HomeViewModelState.Breakfast))

            if (viewModel.state.getCollectionStatus(HomeViewModelState.Drink) === HomeViewModelState.Loading)
                row2.setLoading()
            else if (viewModel.state.getCollectionStatus(HomeViewModelState.Drink) === HomeViewModelState.Error)
                row2.setError()
            else if (row2.isEmpty)
                row2.setSuccess(viewModel.state.getCollectionRecipes(HomeViewModelState.Drink))

            if (viewModel.state.getCollectionStatus(HomeViewModelState.ForBigGroup) === HomeViewModelState.Loading)
                row3.setLoading()
            else if (viewModel.state.getCollectionStatus(HomeViewModelState.ForBigGroup) === HomeViewModelState.Error)
                row3.setError()
            else if (row3.isEmpty)
                row3.setSuccess(viewModel.state.getCollectionRecipes(HomeViewModelState.ForBigGroup))

            if (viewModel.state.getCollectionStatus(HomeViewModelState.LowCalorie) === HomeViewModelState.Loading)
                row4.setLoading()
            else if (viewModel.state.getCollectionStatus(HomeViewModelState.LowCalorie) === HomeViewModelState.Error)
                row4.setError()
            else if (row4.isEmpty)
                row4.setSuccess(viewModel.state.getCollectionRecipes(HomeViewModelState.LowCalorie))
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

            SearchButtonCard {
                width: parent.width
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("SearchPage.qml"), { }, PageStackAction.Immediate)
                }
            }

            DailyRecipe {
                id: dailyRecipe
                width: parent.width
                onReloadRecipe: {
                    viewModel.reloadDailyRecipe()
                }
                onRecipeClicked: {
                    pageStack.push(Qt.resolvedUrl("RecipePage.qml"), { "recipe": viewModel.state.dailyRecipe })
                }
            }

            RecipesCollection {
                id: row1
                width: parent.width
                title: "For your breakfast"
                onReloadCollection: {
                    viewModel.reloadBreakfastRecipes()
                }
                onRecipeClicked: {
                    pageStack.push(Qt.resolvedUrl("RecipePage.qml"),
                                   { "recipe": viewModel.state.getRecipe(HomeViewModelState.Breakfast, index) })
                }
            }

            RecipesCollection {
                id: row2
                width: parent.width
                title: "Let's have a drink"
                onReloadCollection: {
                    viewModel.reloadDrinkRecipes()
                }
                onRecipeClicked: {
                    pageStack.push(Qt.resolvedUrl("RecipePage.qml"),
                                   { "recipe": viewModel.state.getRecipe(HomeViewModelState.Drink, index) })
                }
            }

            RecipesCollection {
                id: row3
                width: parent.width
                title: "For you and your friends"
                onReloadCollection: {
                    viewModel.reloadRecipesForBigGroup()
                }
                onRecipeClicked: {
                    pageStack.push(Qt.resolvedUrl("RecipePage.qml"),
                                   { "recipe": viewModel.state.getRecipe(HomeViewModelState.ForBigGroup, index) })
                }
            }

            RecipesCollection {
                id: row4
                width: parent.width
                title: "Low calorie"
                onReloadCollection: {
                    viewModel.reloadLowCalorieRecipes()
                }
                onRecipeClicked: {
                    pageStack.push(Qt.resolvedUrl("RecipePage.qml"),
                                   { "recipe": viewModel.state.getRecipe(HomeViewModelState.LowCalorie, index) })
                }
            }
        }
    }
}
