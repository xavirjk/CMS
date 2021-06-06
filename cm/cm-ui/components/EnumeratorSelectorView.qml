import QtQuick 2.9
import QtQuick.Controls 2.2
import assets 1.0
import CM 1.0
Item {

    id :stringSelectorView
    property DropDown dropdown
    property EnumeratorDecorator enumeratorDecorator
    property int selectedValue

    ScrollView {
        id: scrollView
        visible: true
        anchors.fill: parent
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            margins: Style.sizeScreenMargin
        }
        Flow {
            flow: Grid.TopToBottom
            spacing: Style.sizeControlSpacing
            height: scrollView.height

            Repeater {
                id: repeaterAnswers
                model: dropdown.ui_values
                delegate:
                    Rectangle {
                    property bool isSelected: modelData.ui_key.ui_value === enumeratorDecorator.ui_value
                    width: Style.widthDataControls
                    height: Style.heightDataControls
                    radius: Style.sizeDataControlRadius
                    color: isSelected ? Style.colourDataControlsBackgroundSelected : Style.colourDataControlsBackground

                    Text {
                        anchors {
                            fill: parent
                            margins: Style.heightDataControls / 4
                        }
                        text: modelData.ui_description
                        color: Style.colourDataControlsFont
                        font.pixelSize: Style.pixelSizeDataControls
                        verticalAlignment: Qt.AlignVCenter
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            selectedValue = modelData.ui_key;
                            contentFrame.pop();
                        }
                    }
                }
            }
        }
    }
    Binding {
        target: enumeratorDecorator
        property: "ui_value"
        value: selectedValue
    }
}
