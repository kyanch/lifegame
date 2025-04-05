import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

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
    // Support File read&save.
    FileDialog {
        id: saveDialog
        title: "保存到"
        nameFilters: ["文本文件 (*.txt)", "所有文件 (*)"]
        fileMode: FileDialog.SaveFile
        onAccepted: {
            console.log("选中文件: " + selectedFile);
            universe.save_to_file(selectedFile);
        }
    }
    FileDialog {
        id: readDialog
        title: "从文件中读取"
        nameFilters: ["文本文件 (*.txt)", "所有文件 (*)"]
        fileMode: FileDialog.OpenFile
        onAccepted: {
            console.log("选中文件: " + selectedFile);
            universe.read_from_file(selectedFile);
        }
    }
    DropArea {
        anchors.fill: parent
        onDropped: function (drop) {
            if (drop.hasUrls) {
                let file_url = drop.urls[0];
                universe.read_from_file(file_url);
            }
        }
    }
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action {
                text: qsTr("Open")
                onTriggered: {
                    readDialog.open();
                }
            }
            Action {
                text: qsTr("Save")
                onTriggered: {
                    saveDialog.open();
                }
            }
        }
    }
}
