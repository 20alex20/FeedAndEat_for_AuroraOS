import QtQuick 2.0
import Sailfish.Silica 1.0
import FeadAndEat.Feature.Search 1.0
import "../items"

Page {
    property SearchViewModel viewModel: SearchFeature.getSearchViewModel(this);
    Component.onCompleted: viewModel.bind()

    property SearchViewModelState state: viewModel.state

    Column {
        anchors.fill: parent
        anchors.margins: Theme.horizontalPageMargin
        spacing: 2*Theme.paddingLarge

        Rectangle {
            id: searchQueryCard
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
                //onTextChanged: viewModel.loadBySearchQuery(text)
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
            height: categoryCard.height

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

                /*onCurrentIndexChanged: {
                    if (curruntIndex === 0)
                        viewModel.loadFromAllCategories()
                    else
                        viewModel.loadFromCategory(currentItem.text)
                }*/
            }

            Rectangle {
                id: categoryCard
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
}
