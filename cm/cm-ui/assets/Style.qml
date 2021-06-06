pragma Singleton
import QtQuick 2.9

Item {
    property alias fontAwesome: fontAwesomeLoader.name

    readonly property color colourBackground: "#efefef"

    readonly property real sizeScreenMargin: tscale(20)
    readonly property real sizeControlSpacing: 10

    readonly property color colourNavigationBarBackground: "#000000"
    readonly property color colourNavigationBarFont: "#ffffff"
    readonly property int pixelSizeNavigationBarIcon: 42
    readonly property int pixelSizeNavigationBarText: 22
    readonly property real widthNavigationBarCollapsed: widthNavigationButtonIcon
    readonly property real heightNavigationBarExpanded: widthNavigationButton

    readonly property real widthNavigationButtonIcon: 80
    readonly property real heightNavigationButtonIcon: widthNavigationButtonIcon
    readonly property real widthNavigationButtonDescription: 160
    readonly property real heightNavigationButtonDescription: heightNavigationButtonIcon
    readonly property real widthNavigationButton: widthNavigationButtonIcon + widthNavigationButtonDescription
    readonly property real heightNavigationButton: Math.max(heightNavigationButtonIcon, heightNavigationButtonDescription)

    property bool isCollapsed: true
    readonly property color colourCommandBarBackground: "#cecece"
    readonly property color colourCommandBarFont: "#131313"
    readonly property color colourCommandBarFontDisabled: "#636363"
    readonly property real heightCommandBar: heightCommandButton
    readonly property int pixelSizeCommandBarIcon: 32
    readonly property int pixelSizeCommandBarText: 12

    readonly property real widthCommandButton: 80
    readonly property real heightCommandButton: widthCommandButton

    readonly property color colourDataControlsBackground: "#ffffff"
    readonly property color colourDataControlsFont: "#131313"
    readonly property int pixelSizeDataControls: 18
    readonly property real widthDataControls: 400
    readonly property real heightDataControls: 40

    readonly property color colourPanelBackground: "#ffffff"
    readonly property color colourPanelBackgroundHover: "#ececec"
    readonly property color colourPanelHeaderBackground: "#131313"
    readonly property color colourPanelHeaderFont: "#ffffff"
    readonly property color colourPanelFont: "#131313"
    readonly property int pixelSizePanelHeader: 18
    readonly property real heightPanelHeader: 40
    readonly property real sizeShadowOffset: 5
    readonly property color colourShadow :"#dedede"

    readonly property color colourItemBackground: "#fefefe"
    readonly property color colourItemBackgroundHover: "#efefef"
    readonly property color colourItemBorder: "#efefef"
    readonly property color colourItemDateFont: "#636363"
    readonly property color colourItemTitleFont: "#131313"
    readonly property real sizeItemMargin: 5

    readonly property real widthWindow: 1920
    readonly property real heightWindow: 1080

    readonly property real widthReferenceWindow: 1920
    readonly property real heightReferenceWindow: 1080

    readonly property color colourDashboardBackground: "#993333"
    readonly property color colourDashboardFont: "#ffffff"
    readonly property int pixelSizeDashboard: tscale(36);
    readonly property real sizeDashboardLogo: tscale(150)


    function hscale(size) {
        return Math.round(size * (widthWindow / widthReferenceWindow))
    }

    function vscale(size) {
        return Math.round(size * (heightWindow / heightReferenceWindow))
    }

    function tscale(size) {
        return Math.round((hscale(size) + vscale(size)) / 2)
    }


    readonly property color colourDataSelectorBackground: "#131313"
    readonly property color colourDataControlsBackgroundSelected: "#f36f24"
    readonly property color colourDataSelectorFont: "#ffffff"
    readonly property int sizeDataControlRadius: tscale(5)

    readonly property real widthFormButton: 240
    readonly property real heightformButton:60
    readonly property color colourFormButtonBackground: "#f36f24"
    readonly property color colourFormButtonFont: "#ffffff"
    readonly property int pixelSizeFormButtonIcon: 32
    readonly property int pixelSizeFormButtonText: 22
    readonly property int sizeFormButtonRadius: 5

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }
}
