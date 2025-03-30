import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    GridLayout {
        anchors.fill: parent
        anchors.centerIn: parent

        CellGrid {
            Layout.fillHeight: true
            Layout.fillWidth: true

            message: "Hello"
            model: universe
        }
        Column {
            spacing: 20

            Button {
                text: universe_tick.running ? "Stop" : "Run"
                onClicked: {
                    if (universe_tick.running) {
                        universe_tick.stop();
                    } else {
                        universe_tick.start();
                    }
                }
            }

            Button {
                text: "Next Step"
                onClicked: {
                    console.log("tick");
                    universe.tick();
                }
            }
        }
    }
    Timer {
        id: universe_tick
        interval: 100
        repeat: true
        running: false
        onTriggered: {
            universe.tick();
        }
    }
}
