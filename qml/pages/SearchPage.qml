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

        TextField {
            id: searchQuery
            width: parent.width
            color: Theme.primaryColor
            placeholderText: "Search"
            validator: RegExpValidator { regExp: /^[A-Za-z0-9 ]*$/ }
            strictValidation: true
            //onTextChanged: viewModel.loadBySearchQuery(text)
        }

        ComboBox {
            id: connection
            width: pageContainer.width
            label: "Category:"
            //minimumContentHeight: 200
            //labelMargin: 0
            //leftMargin: 0
            //rightMargin: 0
            _descriptionLabel: null
            menu: ContextMenu {
                Repeater {
                    model: categoriesList.categories

                    MenuItem {
                        font.pixelSize: Theme.fontSizeLarge
                        text: modelData
                    }
                }
            }
            CategoriesList {
                id: categoriesList
            }

            /*onCurrentIndexChanged: {
                if (curruntIndex === 0)
                    viewModel.loadFromAllCategories()
                else
                    viewModel.loadFromCategory(currentItem.text)
            }*/
        }
    }
}
