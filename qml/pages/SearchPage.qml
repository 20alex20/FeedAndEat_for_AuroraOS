import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Search 1.0
import "../items"

Page {
    property SearchViewModel viewModel: SearchFeature.getSearchViewModel(this);
    Component.onCompleted: viewModel.bind()

    property SearchViewModelState state: viewModel.state
    onStateChanged: {
        if (state.status === SearchViewModelState.Loading) {
            if (state.recipesNumber == 0 && listView.model.count !== 0)
                listView.model.clear()
            listViewLoading.visible = true
            listViewError.visible = false
        }
        else if (state.status === SearchViewModelState.Error) {
            if (state.recipesNumber == 0 && listView.model.count !== 0)
                listView.model.clear()
            listViewLoading.visible = false
            listViewError.visible = true
        }
        else {
            var length = recipes.length - recipes.length % 2
            for (var i = viewModel.model.count; i < length/2; i++)
                listView.model.append({ "ne0": recipes[2*i].getName(),
                                        "ie0": recipes[2*i].getImage(),
                                        "sr0": recipes[2*i].getServingsNumber(),
                                        "ir0": recipes[2*i].getInstructionsNumber(),
                                        "ne1": recipes[2*i + 1].getName(),
                                        "ie1": recipes[2*i + 1].getImage(),
                                        "sr1": recipes[2*i + 1].getServingsNumber(),
                                        "ir1": recipes[2*i + 1].getInstructionsNumber() })
            if (recipes.length - length === 1)
                listView.model.append({ "ne0": recipes[length].getName(),
                                        "ie0": recipes[length].getImage(),
                                        "sr0": recipes[length].getServingsNumber(),
                                        "ir0": recipes[length].getInstructionsNumber(),
                                        "ne1": "",
                                        "ie1": "",
                                        "sr1": 0,
                                        "ir1": 0 })
            listViewLoading.visible = false
            listViewError.visible = false
        }
    }

    Rectangle {
        id: searchQueryCard
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: Theme.horizontalPageMargin
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
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
            onTextChanged: viewModel.loadBySearchQuery(text)
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
        id: categoryCard
        anchors.top: searchQuery.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 2*Theme.paddingLarge
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        height: categoryCardDesign.height

        ComboBox {
            id: categories
            width: parent.width
            height: parent.height

            menu: ContextMenu {
                Repeater {
                    model: categoriesList.categories

                    MenuItem {
                        font.pixelSize: Theme.fontSizeLarge
                        text: modelData
                    }
                }
            }
            CategoriesList { id: categoriesList }

            onCurrentIndexChanged: {
                if (curruntIndex === 0)
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

    ListView {
        id: listView
        anchors.top: categoryCard.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 2*Theme.paddingLarge
        anchors.bottomMargin: Theme.horizontalPageMargin
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin

        model: ListModel { }
        spacing: Theme.paddingLarge
        delegate: Row {
            spacing: Theme.paddingLarge

            RecipeCard {
                width: (parent.width - Theme.paddingLarge)/2
                name: ne1
                image: ie1
                servingsNumber: sr2
                instructionsNumber: ir2
                onClicked: recipeClicked(index)
            }
            RecipeCard {
                width: (parent.width - Theme.paddingLarge)/2
                visible: ne1 !== ""

                name: ne2
                image: ie2
                servingsNumber: sr2
                instructionsNumber: ir2
                onClicked: recipeClicked(index)
            }
        }
        footer: Item {
            width: listView.width
            height: listView.model.count === 0 ? listView.height : 3*Theme.itemSizeHuge
            visible: listViewLoading.visible || listViewError.visible

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: button.top
                anchors.bottomMargin: Theme.paddingLarge
                visible: listViewError.visible

                font.family: Theme.fontFamilyHeading
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.primaryColor
                text: "Loading error"
            }
            Button {
                id: listViewError
                anchors.centerIn: parent

                text: "Retry"
                onClicked: reloadCollection()
            }

            BusyIndicator {
                id: listViewLoading
                width: parent.width
                height: parent.height

                size: Theme.itemSizeHuge
                running: visible
            }
        }
    }
}
