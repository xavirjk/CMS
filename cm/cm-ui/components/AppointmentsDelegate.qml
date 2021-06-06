import QtQuick 2.9
import assets 1.0
import CM 1.0

Panel {
    headerText: "Appointment"
    property Appointment appointment
    contentComponent:
        Column {
        id: column
        spacing: Style.sizeControlSpacing
        DateTimeEditorSingleLine {
            dateTimeDecorator: appointment.ui_startAt
            anchors {
                left: parent.left
                right: parent.right
            }
        }
        DateTimeEditorSingleLine {
            dateTimeDecorator: appointment.ui_endAt
            anchors {
                left: parent.left
                right: parent.right
            }
        }
        StringEditorSingleLine {
            stringDecorator: appointment.ui_notes
            anchors {
                left: parent.left
                right: parent.right
            }
        }
    }
}
