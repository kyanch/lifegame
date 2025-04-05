import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    footer: ToolBar {
        ColumnLayout {
            Text {
                id: tooltip_text
            }
        }
    }

    GridLayout {
        anchors.fill: parent
        anchors.centerIn: parent

        ZoomFlick {
            id: zoom
            Layout.fillHeight: true
            Layout.fillWidth: true

            onMouseMoved: function (x, y) {
                tooltip_text.text = Math.round(x, 2) + "," + Math.round(y, 2);
            }
        }

        Column {
            spacing: 10

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

            Button {
                text: "debug info"
                onClicked: {
                    console.log("");
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
