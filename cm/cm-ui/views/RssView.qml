import QtQuick 2.9
import assets 1.0
import components 1.0
import CM 1.0

Item {
    Rectangle {
        anchors.fill: parent
        color: Style.colourBackground
        Text {
            text:"wait wait wait wait    ..."
            font.pixelSize: Style.pixelSizeDataControls
            color: Style.colourPanelFont
        }
    }

    CommandBar{
        commandList:
            masterController.ui_commandController.ui_rssViewContextCommands
    }
}

