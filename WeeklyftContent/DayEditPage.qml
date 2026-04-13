import QtQuick
import QtQuick.Controls

Item {
    width: 350
    height: 740

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        Text {
            text: databaseVM.selectedPlanningName + " - " + databaseVM.selectedDayName
            font.pixelSize: 16
        }

        TextField {
            id: sessionNameField
            placeholderText: "Nom de la séance"
        }

        Button {
            text: "Ajouter exercice"
            onClicked: {
                // TODO: ajouter ligne exercice
            }
        }

        ListView {
            id: exerciseList
            height: 300
            width: parent.width

            model: 0 // sera remplacé plus tard

            delegate: Rectangle {
                height: 50
                width: parent.width

                Row {
                    spacing: 10

                    TextField { placeholderText: "Exercice" }
                    TextField { placeholderText: "Séries" }
                    TextField { placeholderText: "Reps" }
                }
            }
        }

        Button {
            text: "Sauvegarder"
            onClicked: {
                // TODO: save via ViewModel
            }
        }
    }
}
