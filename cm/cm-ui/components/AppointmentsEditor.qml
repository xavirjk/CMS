import QtQuick 2.9
import assets 1.0
import CM 1.0

Panel {
    property Client client
    id: appointmentsEditorRoot
    contentComponent:
        Column {
        id :column
        spacing: Style.sizeControlSpacing
        Repeater {
            id: appointmentsView
            model: client.ui_appointments
            delegate:
                AppointmentsDelegate {
                    width: appointmentsEditorRoot.width
                    appointment: modelData
            }
        }
        FormButton {
            iconCharacter: "\uf073"
            description: "Book "
            onFormButtonClicked: {
                client.bookAppointment();
            }
        }
    }
}
