import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 350
    height: 740

    Text {
        id: planningText
        x: 24
        y: 23
        text: databaseVM.selectedPlanningName + " (id: " + databaseVM.selectedPlanningId + ")"
        font.pixelSize: 12
    }

    Column {
        x: 75
        y: 66
        spacing: 10

        Repeater {
            model: ["Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"]

            delegate: Button {
                text: modelData
                width: 200

                onClicked: {
                    databaseVM.selectDay(index)
                    stackView.push("DayEditPage.qml")
                }
            }
        }
    }
}
