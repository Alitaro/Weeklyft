import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 350
    height: 740

    property int expandedDayIndex: -1

    Text {
        id: planningText
        x: 24; y: 14
        text: databaseVM.selectedPlanningName
        font.pixelSize: 14
        font.bold: true
    }

    ListView {
        x: 12
        y: 44
        width: parent.width - 24
        height: parent.height - 44
        spacing: 4
        clip: true

        // Le modèle est la QVariantList des 7 jours
        model: databaseVM.daySessions

        delegate: Column {
            width: ListView.view.width
            spacing: 0

            required property int   index
            required property var   modelData

            // ── Ligne principale ──────────────────────────────
            Rectangle {
                width: parent.width
                height: 48
                radius: 6
                color: "#f5f5f5"

                Row {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 8
                    spacing: 8

                    // Cliquable : jour + nom de séance
                    MouseArea {
                        width: parent.width - editBtn.width - 8
                        height: parent.height

                        onClicked: {
                            root.expandedDayIndex =
                                (root.expandedDayIndex === index) ? -1 : index
                        }

                        Row {
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 8

                            Text {
                                text: modelData.dayName
                                font.pixelSize: 13
                                font.bold: true
                                color: "#333"
                            }

                            Text {
                                text: modelData.sessionName
                                font.pixelSize: 12
                                color: "#666"
                                visible: modelData.sessionId > 0
                            }
                        }
                    }

                    // Bouton édition
                    Button {
                        id: editBtn
                        text: modelData.sessionId > 0 ? "✏️" : "+"
                        width: 36
                        height: 36
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            databaseVM.selectDay(index)
                            stackView.push("DayEditPage.qml")
                        }
                    }
                }
            }

            // ── Détail exercices (expandable) ─────────────────
            Rectangle {
                width: parent.width
                height: visible ? exerciseCol.implicitHeight + 16 : 0
                visible: root.expandedDayIndex === index && modelData.sessionId > 0
                clip: true
                color: "#ececec"
                radius: 6

                Column {
                    id: exerciseCol
                    x: 16; y: 8
                    spacing: 4

                    Repeater {
                        model: modelData.exercises

                        delegate: Row {
                            spacing: 8
                            required property var modelData

                            Text {
                                text: modelData.exerciseName
                                font.pixelSize: 12
                                width: 140
                            }
                            Text {
                                text: modelData.series + " × " + modelData.reps
                                font.pixelSize: 12
                                color: "#555"
                            }
                        }
                    }
                }
            }
        }
    }
}