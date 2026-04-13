import QtQuick
import QtQuick.Controls
import Weeklyft

Rectangle {
    width: 350
    height: 740

    // =================================
    // PLANNINGS
    //=================================
    Text {
        x: 152
        y: 12
        text: qsTr("Plannings")
        font.pixelSize: 12
    }

    ListView {
        id: listView
        x: 0
        y: 72
        width: parent.width
        height: 300

        model: databaseVM.planningModel

        delegate: Rectangle {
            width: ListView.view.width
            height: 50

            Text {
                anchors.centerIn: parent
                text: name
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    databaseVM.selectPlanning(id)
                    stackView.push("PlanningDaysPage.qml")
                }
            }
        }
    }

    Button {
        text: "Add Planning"

        onClicked: planningDialog.open()
    }

    Dialog {
        id: planningDialog
        modal: true
        title: "Nouveau planning"

        standardButtons: Dialog.Ok | Dialog.Cancel

        Column {
            spacing: 10
            padding: 10

            TextField {
                id: planningNameField
                placeholderText: "Nom du planning"
                width: 200
            }
        }

        onAccepted: {
            if (planningNameField.text.length === 0)
                return

            let id = databaseVM.createPlanning(planningNameField.text)
            databaseVM.selectPlanning(id)
            planningNameField.text = ""
            stackView.push("PlanningDaysPage.qml")
        }
    }



    // =================================
    // EXERCICES
    //=================================
    Text {
        x: 153
        y: 395
        text: qsTr("Exercises")
        font.pixelSize: 12
    }

    ListView {
        id: listViewExercises
        x: 0
        y: 422
        width: parent.width
        height: 300

        model: databaseVM.exerciseModel

        delegate: Rectangle {
            width: ListView.view.width
            height: 50

            Text {
                anchors.centerIn: parent
                text: name
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    databaseVM.selectExercise(id)
                    // TODO
                }
            }
        }
    }

    Button {
        x: 1
        y: 383
        text: "Add Exercise"

        onClicked: exerciseDialog.open()
    }

    Dialog {
        id: exerciseDialog
        modal: true
        title: "Nouvel exercice"

        standardButtons: Dialog.Ok | Dialog.Cancel

        Column {
            spacing: 10
            padding: 10

            TextField {
                id: exerciseNameField
                placeholderText: "Nom de l'exercice"
                width: 200
            }
        }

        onAccepted: {
            if (exerciseNameField.text.length === 0)
                return

            let id = databaseVM.createExercise(exerciseNameField.text)
            exerciseNameField.text = ""
        }
    }
}
