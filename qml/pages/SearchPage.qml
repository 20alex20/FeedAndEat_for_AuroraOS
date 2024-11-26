import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Search 1.0
import "../items"

Page {
    property SearchViewModel viewModel: SearchFeature.getSearchViewModel(this);
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
                        console.log("bad1")
                        if (i % 2 === 0) {
                            record.is0 = recipe.isSuccess()
                            record.ne0 = recipe.getName()
                            record.ie0 = recipe.getImage()
                            record.sr0 = recipe.getServingsNumber()
                            record.ir0 = recipe.getInstructionsNumber()
                        }
                        else {
                            record.is1 = recipe.isSuccess()
                            record.ne1 = recipe.getName()
                            record.ie1 = recipe.getImage()
                            record.sr1 = recipe.getServingsNumber()
                            record.ir1 = recipe.getInstructionsNumber()
                        }
                    }
                }

                var length = (recipes.length - recipes.length % 2)/2
                for (var j = 2*listView.model.count; j < length; j++) {
                    var recipe0 = recipes[2*j]
                    var recipe1 = recipes[2*j + 1]
                    listView.model.append({ "is0": recipe0.isSuccess(),
                                            "ne0": recipe0.getName(),
                                            "ie0": recipe0.getImage(),
                                            "sr0": recipe0.getServingsNumber(),
                                            "ir0": recipe0.getInstructionsNumber(),
                                            "is1": recipe1.isSuccess(),
                                            "ne1": recipe1.getName(),
                                            "ie1": recipe1.getImage(),
                                            "sr1": recipe1.getServingsNumber(),
                                            "ir1": recipe1.getInstructionsNumber() })
                }
                if (recipes.length - length === 1)
                    listView.model.append({ "is0": recipes[length].isSuccess(),
                                            "ne0": recipes[length].getName(),
                                            "ie0": recipes[length].getImage(),
                                            "sr0": recipes[length].getServingsNumber(),
                                            "ir0": recipes[length].getInstructionsNumber(),
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

    Column {
        id: titleCards
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: Theme.horizontalPageMargin
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        spacing: 2*Theme.paddingLarge

        Rectangle {
            width: parent.width
            height: (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2 + 2*Theme.paddingLarge
            color: Theme.highlightBackgroundColor

            TextField {
                id: searchQuery
                anchors.left: parent.left
                anchors.right: searchIcon.left
                anchors.top: parent.top
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingLarge
                anchors.topMargin: Theme.paddingMedium + Theme.paddingSmall

                textMargin: 0
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.primaryColor
                placeholderText: "Search"
                backgroundStyle: TextEditor.NoBackground
                validator: RegExpValidator { regExp: /^[A-Za-z0-9 ]*$/ }
                strictValidation: true
                onTextChanged: {
                    viewModel.loadBySearchQuery(text)
                }
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
        }

        Item {
            width: parent.width
            height: categoryCardDesign.height

            ComboBox {
                id: categories
                width: parent.width
                height: parent.height

                CategoriesList { id: categoriesList }
                menu: ContextMenu {
                    Repeater {
                        model: categoriesList.categories

                        MenuItem {
                            font.pixelSize: Theme.fontSizeLarge
                            text: modelData
                        }
                    }
                }
                onCurrentIndexChanged: {
                    if (currentIndex === 0)
                        viewModel.loadFromAllCategories()
                    else
                        viewModel.loadFromCategory(currentItem.text)
                }
            }

            Rectangle {
                id: categoryCardDesign
                width: parent.width
                height: categoryTitle.height + 2*Theme.paddingLarge
                color: Theme.highlightBackgroundColor

                Label {
                    id: categoryTitle
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: Theme.paddingLarge

                    font.pixelSize: Theme.fontSizeLarge
                    color: Theme.primaryColor
                    text: "Category: "
                }
                Label {
                    anchors.left: categoryTitle.right
                    anchors.verticalCenter: parent.verticalCenter

                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                    color: Theme.primaryColor
                    text: categories.value
                }

                Rectangle {
                    anchors.fill: parent
                    visible: categories.pressed
                    color: "#40000000"
                }
            }
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
        property real rowHeight: (width - Theme.paddingLarge)*3/8 + Theme.paddingSmall + 2*categoryTitle.contentHeight +
                                 2*Theme.paddingMedium + (Theme.iconSizeSmall + Theme.iconSizeSmallPlus)/2
        model: ListModel { }
        clip: true
        spacing: Theme.paddingLarge
        delegate: Item {
            width: listView.width
            height: listView.rowHeight

            RecipeCard {
                anchors.top: parent.top
                anchors.left: parent.left
                width: (parent.width - Theme.paddingLarge)/2

                visible: ir0 !== -1
                isSuccess: is0
                name: ne0
                image: ie0
                servingsNumber: sr0
                instructionsNumber: ir0
                onClicked: {
                    console.log(isSuccess, is0, index)
                    if (!isSuccess)
                        viewModel.loadRecipe(2*index)
                }
                onPressed: {
                    searchQuery.focus = false
                }
            }
            BusyIndicator {
                anchors.top: parent.top
                anchors.left: parent.left
                width: (parent.width - Theme.paddingLarge)/2
                height: parent.height

                visible: ir0 === -1
                size: Theme.itemSizeHuge
                running: visible
            }

            RecipeCard {
                anchors.top: parent.top
                anchors.right: parent.right
                width: (parent.width - Theme.paddingLarge)/2

                visible: ir1 !== -1 && ne1 !== ""
                isSuccess: is1
                name: ne1
                image: ie1
                servingsNumber: sr1
                instructionsNumber: ir1
                onClicked: {
                    console.log(isSuccess, is1, index)
                    if (!isSuccess)
                        viewModel.loadRecipe(2*index + 1)
                }
                onPressed: {
                    searchQuery.focus = false
                }
            }
            BusyIndicator {
                anchors.top: parent.top
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
                    onPressed: {
                        searchQuery.focus = false
                    }
                }
            }
        }
        onAtYEndChanged: {
            if (atYEnd && !listView.loading && !parent.viewModel.state.isEnd)
                viewModel.loadAdditionalRecipes()
        }
    }
}
