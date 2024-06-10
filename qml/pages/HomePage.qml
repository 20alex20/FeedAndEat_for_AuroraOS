import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.HomePage 1.0

Page {
    objectName: "homePage"

    property HomePageViewModel viewModel: HomePageFeature.getHomePageViewModel(this);
    Component.onCompleted: viewModel.bind()
    Connections {
        target: viewModel
        onRecipeOfDayOfYearChanged: {
            result1.text = viewModel.recipeOfDayOfYear
        }
        onRecipesOfBreakfastChanged: {
            result2.text = viewModel.recipesOfBreakfast
        }
        onRecipesOfDrinkChanged: {
            result3.text = viewModel.recipesOfDrink
        }
        onRecipesOfForBigGroupChanged: {
            result4.text = viewModel.recipesOfForBigGroup
        }
        onRecipesOfLowCalorieChanged: {
            result5.text = viewModel.recipesOfLowCalorie
        }


        onRecipeIdsChanged: {
            result6.text = viewModel.recipeIds
        }
        onRecipeChanged: {
            result7.text = viewModel.recipe
        }
    }

    Flickable {
        anchors.fill: parent
        contentHeight: result1.height + result2.height + result3.height + result4.height + result5.height + result6.height + result7.height + 240

        Column {
            id: column
            width: parent.width
            spacing: 40

            Text {
                id: result1
                width: parent.width
                wrapMode: Text.WrapAnywhere
            }
            Text {
                id: result2
                width: parent.width
                wrapMode: Text.WrapAnywhere
            }
            Text {
                id: result3
                width: parent.width
                wrapMode: Text.WrapAnywhere
            }
            Text {
                id: result4
                width: parent.width
                wrapMode: Text.WrapAnywhere
            }
            Text {
                id: result5
                width: parent.width
                wrapMode: Text.WrapAnywhere
            }
            Text {
                id: result6
                width: parent.width
                wrapMode: Text.WrapAnywhere
            }
            Text {
                id: result7
                width: parent.width
                wrapMode: Text.WrapAnywhere
            }
        }
    }
}
