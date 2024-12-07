import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Recipe 1.0
import FeadAndEat.Feature.Search 1.0
import "../items"
import "../dataObjects"

Page {
    property SearchViewModel viewModel: SearchFeature.getSearchViewModel(this)
    Component.onCompleted: {
        viewModel.bind()
    }
    Connections {
        target: viewModel
        onStateChanged: {
            if (viewModel.state.status === SearchViewModelState.Loading) {
                if (viewModel.state.recipesNumber == 0 && listView.model.count !== 0)
                    listView.model.clear()
                listView.loading = true
                listView.error = false
            }
            else if (viewModel.state.status === SearchViewModelState.Error) {
                listView.error = true
                listView.loading = false
            }
            else {
                var recipes = viewModel.state.recipes
                for (var i = 0; i < Math.min(2*listView.model.count, recipes.length); i++) {
                    var recipe = recipes[i]
                    var record = listView.model.get((i - i % 2)/2)
                    var isLoading = (i % 2 === 0 ? record.ir0 : record.ir1) === -1
                    if (recipe === null && !isLoading) {
                        if (i % 2 === 0)
                            record.ir0 = -1
                        else
                            record.ir1 = -1
                    }
                    else if (recipe !== null && isLoading) {
                        if (i % 2 === 0) {
                            record.is0 = recipe.isSuccess
                            record.ne0 = recipe.name
                            record.ie0 = recipe.image
                            record.sr0 = recipe.servingsNumber
                            record.ir0 = recipe.instructionsNumber
                        }
                        else {
                            record.is1 = recipe.isSuccess
                            record.ne1 = recipe.name
                            record.ie1 = recipe.image
                            record.sr1 = recipe.servingsNumber
                            record.ir1 = recipe.instructionsNumber
                        }
                    }
                }

                var length = recipes.length - recipes.length % 2
                for (var j = listView.model.count; j < length/2; j++) {
                    var recipe0 = recipes[2*j]
                    var recipe1 = recipes[2*j + 1]
                    listView.model.append({ "is0": recipe0.isSuccess,
                                            "ne0": recipe0.name,
                                            "ie0": recipe0.image,
                                            "sr0": recipe0.servingsNumber,
                                            "ir0": recipe0.instructionsNumber,
                                            "is1": recipe1.isSuccess,
                                            "ne1": recipe1.name,
                                            "ie1": recipe1.image,
                                            "sr1": recipe1.servingsNumber,
                                            "ir1": recipe1.instructionsNumber })
                }
                if (recipes.length - length === 1)
                    listView.model.append({ "is0": recipes[length].isSuccess,
                                            "ne0": recipes[length].name,
                                            "ie0": recipes[length].image,
                                            "sr0": recipes[length].servingsNumber,
                                            "ir0": recipes[length].instructionsNumber,
                                            "is1": true,
                                            "ne1": "",
                                            "ie1": "",
                                            "sr1": 0,
                                            "ir1": 0 })

                listView.loading = false
                listView.error = false
            }
        }
    }

    SearchCategoryCard {
        id: titleCards
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: Theme.horizontalPageMargin
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin

        onSearchQueryChanged: {
            if (searchQuery.length >= 2 || (viewModel.state.searchQuery !== "" && searchQuery.length === 0))
                viewModel.loadBySearchQuery(searchQuery)
        }
        onCategoryChanged: {
            if (!isCategorySelected)
                viewModel.loadFromAllCategories()
            else
                viewModel.loadFromCategory(category)
        }
    }

    ListView {
        id: listView
        anchors.top: titleCards.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 2*Theme.paddingLarge
        anchors.bottomMargin: Theme.horizontalPageMargin
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin

        property bool loading: true
        property bool error: false
        property real rowHeight: recipeCardHeight.getHeight((width - Theme.paddingLarge)/2)
        RecipeCardHeight { id: recipeCardHeight }

        model: ListModel { }
        clip: true
        spacing: Theme.paddingLarge
        delegate: Item {
            width: listView.width
            height: listView.rowHeight

            RecipeCard {
                width: (parent.width - Theme.paddingLarge)/2
                visible: ir0 !== -1
                isSuccess: is0
                name: ne0
                image: ie0
                servingsNumber: sr0
                instructionsNumber: ir0
                onClicked: {
                    if (!isSuccess)
                        viewModel.loadRecipe(2*index)
                    else
                        pageStack.push(Qt.resolvedUrl("RecipePage.qml"), { "recipe": viewModel.state.getRecipe(2*index) })
                }
            }
            BusyIndicator {
                width: (parent.width - Theme.paddingLarge)/2
                height: parent.height

                visible: ir0 === -1
                size: Theme.itemSizeHuge
                running: visible
            }
            RecipeCard {
                anchors.right: parent.right
                width: (parent.width - Theme.paddingLarge)/2

                visible: ir1 !== -1 && ne1 !== ""
                isSuccess: is1
                name: ne1
                image: ie1
                servingsNumber: sr1
                instructionsNumber: ir1
                onClicked: {
                    if (!isSuccess)
                        viewModel.loadRecipe(2*index + 1)
                    else
                        pageStack.push(Qt.resolvedUrl("RecipePage.qml"), { "recipe": viewModel.state.getRecipe(2*index + 1) })
                }
            }
            BusyIndicator {
                anchors.right: parent.right
                width: (parent.width - Theme.paddingLarge)/2
                height: parent.height

                visible: ir0 === -1
                size: Theme.itemSizeHuge
                running: visible
            }
        }
        footer: Item {
            width: listView.width
            height: listView.loading || listView.error ? (listView.model.count === 0 ? listView.height : 2*Theme.itemSizeHuge) : 0

            BusyIndicator {
                width: parent.width
                height: parent.height

                visible: listView.loading
                size: Theme.itemSizeHuge
                running: visible
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                visible: listView.error

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.family: Theme.fontFamilyHeading
                    font.pixelSize: Theme.fontSizeLarge
                    color: Theme.primaryColor
                    text: "Loading error"
                }
                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Retry"
                    onClicked: {
                        viewModel.loadAdditionalRecipes()
                    }
                }
            }
        }
        onAtYEndChanged: {
            if (atYEnd && !listView.loading && !parent.viewModel.state.isEnd)
                viewModel.loadAdditionalRecipes()
        }
        onMovementStarted: {
            titleCards.removeSearchCardFocus()
        }
    }
}
