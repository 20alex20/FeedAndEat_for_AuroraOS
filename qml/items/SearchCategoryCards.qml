import QtQuick 2.0
import Sailfish.Silica 1.0
import "../dataObjects"

Column {
    signal searchQueryChanged(string searchQuery)
    signal categoryChanged(bool isCategorySelected, string category)
    function removeSearchCardFocus() {
        searchQuery.focus = false
    }

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
            validator: RegExpValidator { regExp: /^([A-Za-z0-9][A-Za-z0-9 ]{0,15})?$/ }
            strictValidation: true
            onTextChanged: {
                searchQueryChanged(text)
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
            source: Qt.resolvedUrl("../icons/search.svg")
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
                categoryChanged(currentIndex !== 0, currentItem.text)
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
