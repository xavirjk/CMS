import QtQuick 2.9
import assets 1.0
import CM 1.0
Item {
    property RssItem rssItem
    implicitHeight: background.height
    implicitWidth: parent.width
    Rectangle {
        id: background
        width: parent.width
        height: textpubdate.implicitHeight + textTitle.implicitHeight + borderBottom.height + (Style.sizeScreenMargin * 3)
        color: Style.colourPanelBackground

        Text {
            id: textpubdate
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                margins: Style.sizeItemMargin
            }
            text: Qt.formatDateTime(rssItem.ui_pubDate, "ddd, d MMM YYYY @ h: mm ap")
            font {
                pixelSize: Style.pixelSizeDataControls
                italic: true
                weight: Font.Light
            }
            color: Style.colourItemTitleFont
        }
        Text {
            id: textTitle
            anchors {
                left: parent.left
                right: parent.right
                top: textpubdate.bottom
                margins: Style.sizeItemMargin
            }
            text: rssItem.ui_title
            font {
                pixelSize: Style.pixelSizeDataControls
            }
            color: Style.colourItemTitleFont
            wrapMode: Text.Wrap
        }
        Rectangle {
            id: borderBottom
            anchors {
                top: textTitle.bottom
                right: parent.right
                left: parent.left
                topMargin: Style.sizeItemMargin
            }
            height: 1
            color: Style.colourItemBorder
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state =""
            onClicked: if(rssItem.ui_link !== ""){
                           Qt.openUrlExternally(rssItem.ui_link)
                       }
        }
        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: Style.colourItemBackgroundHover
                }
            }

        ]
    }
}
