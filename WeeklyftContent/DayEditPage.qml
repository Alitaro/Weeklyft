import QtQuick
import QtQuick.Controls

Item {
    width: 350
    height: 740

    // Données existantes injectées à l'ouverture
    property var dayData: databaseVM.daySessions[databaseVM.selectedDayIndex] ?? {}

    ListModel { id: exerciseModel }

    Component.onCompleted: {
        // Pré-remplir le nom de séance
        if (dayData.sessionName)
            sessionNameField.text = dayData.sessionName

        // Pré-remplir les exercices
        const exos = dayData.exercises ?? []
        for (let i = 0; i < exos.length; i++) {
            exerciseModel.append({
                id:     exos[i].exerciseId,
                name:   exos[i].exerciseName,
                series: exos[i].series,
                reps:   exos[i].reps
            })
        }
    }

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
                exerciseModel.append({ id: 0, series: 0, reps: 0, name: "" })
            }
        }

        ListView {
            id: listView
            width: parent.width
            height: 400
            model: exerciseModel

            delegate: Rectangle {
                width: ListView.view.width
                height: 60

                required property int    index
                required property int    id
                required property int    series
                required property int    reps
                required property string name

                // Capture explicite pour éviter l'ambiguïté dans les sous-éléments
                readonly property int delegateIndex: index

                Row {
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter

                    ComboBox {
                        width: 150
                        model: databaseVM.exerciseModel
                        textRole: "name"
                        valueRole: "id"

                        Component.onCompleted: {
                            if (id > 0) currentIndex = indexOfValue(id)
                        }

                        // Paramètre formel au lieu de l'injection implicite
                        onActivated: function(comboIndex) {
                            exerciseModel.setProperty(delegateIndex, "id",   currentValue)
                            exerciseModel.setProperty(delegateIndex, "name", currentText)
                        }
                    }

                    TextField {
                        width: 50
                        text: series
                        onTextChanged: exerciseModel.setProperty(delegateIndex, "series", parseInt(text) || 0)
                    }

                    TextField {
                        width: 50
                        text: reps
                        onTextChanged: exerciseModel.setProperty(delegateIndex, "reps", parseInt(text) || 0)
                    }

                    Button {
                        text: "X"
                        onClicked: exerciseModel.remove(delegateIndex)
                    }
                }
            }
        }

        Button {
            text: "Sauvegarder"
            onClicked: {
                let exercises = []
                for (let i = 0; i < exerciseModel.count; i++) {
                    const e = exerciseModel.get(i)
                    exercises.push({ id: e.id, name: e.name, series: e.series, reps: e.reps })
                }
                databaseVM.saveSession(sessionNameField.text, exercises)
                stackView.pop()
            }
        }
    }
}