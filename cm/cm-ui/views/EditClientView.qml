import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.1
import CM 1.0
import assets 1.0
import components 1.0

Item {
    property Client selectedClient
    Component.onCompleted:
        masterController.ui_commandController.setSelectedClient(selectedClient)
    Rectangle {
        anchors.fill: parent
        color: Style.colourBackground
    }
    ScrollView {
        id: scrollview
        width: parent.width
        height: parent.height
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: CommandBar.top
            margins: Style.sizeScreenMargin
        }
        clip: true
        Column {
            spacing: Style.sizeScreenMargin
            width: scrollview.width
            Panel {
                headerText: "Client Details"
                contentComponent:
                    Column{
                    spacing:  Style.sizeControlSpacing
                    StringEditorSingleLine {
                        stringDecorator: selectedClient.ui_reference
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                    }
                    StringEditorSingleLine {
                         stringDecorator: selectedClient.ui_name
                         anchors {
                             left: parent.left
                             right: parent.right
                          }
                    }
                }
            }
            AddressEditor {
                address: selectedClient.ui_supplyAddress
                headerText: "Supply Address"
            }
            AddressEditor {
                address: selectedClient.ui_billingAddress
                headerText: "Billing Address"
            }
            ContactsEditor {
                width: scrollview.width
                client: selectedClient
                headerText: "Contact Details"
            }
            AppointmentsEditor {
                width: scrollview.width
                client: selectedClient
                headerText: "Appointment Details"
            }

            Rectangle {
                height: 100
                anchors {
                    left: parent.left
                    right: parent.right
                }
                color: Style.colourPanelBackground
            }
        }
    }
    CommandBar {
        commandList:
            masterController.ui_commandController.ui_editClientViewContextCommands
    }
}
