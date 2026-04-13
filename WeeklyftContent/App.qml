import QtQuick
import QtQuick.Controls
import Weeklyft
import QtQuick.Layouts

Window {
    id: root
    width: 350
    height: 800

    visible: true

    TabBar {
        id: tabBar
        x: 0
        y: 740
        width: parent.width
        height: 60

        TabButton { text: "Database"; onClicked: stackView.replace("DatabasePage.qml") }
    }

    StackView {
        id: stackView
        x: 0
        y: 0
        width: 350
        height: 567
    }
}

