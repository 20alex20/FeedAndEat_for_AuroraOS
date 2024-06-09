import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.HomePage 1.0

Page {
    objectName: "homePage"
    property HomePageViewModel viewModel: HomePageFeature.getHomePageViewModel(this);

    Component.onCompleted: {
        viewModel.bind()
    }

    Connections {
        target: viewModel
        onRecipeOfDayOfYearChanged: {
            result.text = viewModel.recipeOfDayOfYear
        }
    }

    Text {
        id: result
        anchors.fill: parent
    }
}
