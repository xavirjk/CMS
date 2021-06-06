import QtQuick 2.9
import CM 1.0
import assets 1.0
import QtQuick.Controls 2.2

Item {
    property DropDown dropdown
    property EnumeratorDecorator enumeratorDecorator
    id: enumeratorSelectorRoot
    height: width >textLabel.width + textAnswer.width ? Style.heightDataControls : Style.heightDataControls * 2
    Flow {
        anchors.fill: parent
        Rectangle {
            height: Style.heightDataControls
            width: Style.widthDataControls
            Text {
                id: textLabel
                anchors {
                    fill: parent
                    margins: Style.sizeScreenMargin / 4
                }
                text: enumeratorDecorator.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }

        }
        Rectangle {
            id: bottomAnswer
            width: Style.widthDataControls
            height: Style.heightDataControls
            radius: Style.sizeDataControlRadius
            enabled: dropdown ? dropdown.ui_values.length > 0: false
            color: Style.colourDataSelectorBackground
            Text {
                id: textAnswer
                anchors {
                    fill: parent
                    margins: Style.sizeScreenMargin
                }
                text: dropdown.findDescriptionForDropdownValue(enumeratorDecorator.ui_value)
                color: Style.colourDataSelectorFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter

            }
            MouseArea {
                anchors.fill: parent
                onClicked:
                    contentFrame.push("qrc:/components/EnumeratorSelectorView.qml",{dropdown: enumeratorSelectorRoot.dropdown, enumeratorDecorator: enumeratorSelectorRoot.enumeratorDecorator})
            }
        }
    }

}
