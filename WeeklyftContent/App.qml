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

        TabButton { text: "Sport"; onClicked: stackView.replace("SportPage.qml") }
        TabButton { text: "Quests"; onClicked: stackView.replace("QuestsPage.qml") }
        TabButton { text: "Database"; onClicked: stackView.replace("DatabasePage.qml") }
        TabButton { text: "History"; onClicked: stackView.replace("HistoryPage.qml") }
        TabButton { text: "Settings"; onClicked: stackView.replace("SettingsPage.qml") }
    }

    StackView {
        id: stackView
        x: 0
        y: 0
        width: 350
        height: 567
    }
}

