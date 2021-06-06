import QtQuick 2.9
import CM 1.0
import assets 1.0

Item {
    property Contact contact
    implicitHeight: flow.implicitHeight
    implicitWidth: flow.implicitHeight + borderBottom.implicitHeight + Style.sizeItemMargin
    height: width > selectorType.width + textAddress.width + Style.sizeScreenMargin ? selectorType.height + textAddress.height + Style.sizeScreenMargin :
                                                                                      selectorType.height + textAddress.height + borderBottom.height + Style.sizeScreenMargin
    Flow {
        id:flow
        width: parent.width
        spacing: Style.sizeScreenMargin

        EnumeratorSelector {
            id: selectorType
            width: Style.widthDataControls
            dropdown: contact.ui_contactTypeDropDown
            enumeratorDecorator: contact.ui_contactType
        }
        StringEditorSingleLine {
            id: textAddress
            width: Style.widthDataControls
            stringDecorator: contact.ui_address
        }

    }
    Rectangle {
        id: borderBottom
        anchors {
            top: flow.bottom
            left: parent.left
            right: parent.right
            rightMargin: Style.sizeItemMargin
        }
        color: Style.colourItemBorder
        height: 1
    }
}
