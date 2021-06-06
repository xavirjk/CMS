import QtQuick 2.9
import assets 1.0
import CM 1.0

Item {
    property DateTimeDecorator dateTimeDecorator

    height: width > textLabel.width + dateTimeValue.width ? Style.heightDataControls : Style.heightDataControls * 2

    Flow {
        anchors.fill: parent

        Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourPanelBackground
            Text {
                id: textLabel
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: dateTimeDecorator.ui_label
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Rectangle {
            id: background
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourDataControlsBackground
            border {
                width: 1
                color: Style.colourDataControlsFont
            }
            TextInput {
                id: dateTimeValue
                anchors {
                    fill: parent
                    margins: Style.heightDataControls / 4
                }
                text: dateTimeDecorator.ui_value
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }

        }
        Binding {
            target: dateTimeDecorator
            property: "ui_value"
            value: dateTimeValue.text
        }
    }

}
