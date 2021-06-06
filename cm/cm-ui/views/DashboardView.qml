import QtQuick 2.9
import assets 1.0

Item {
    Rectangle {
        anchors.fill: parent
        color: Style.colourDashboardBackground
        Image {
            id: logo
            source: "qrc:/assets/star"
            anchors.centerIn: parent
            width: Style.sizeDashboardLogo
            height: Style.sizeDashboardLogo
        }
        Text {
            anchors {
                top: logo.bottom
                topMargin: 150
                horizontalCenter: logo.horizontalCenter

            }
            text: "Client Management System"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }
    }
}
