import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    GridLayout{
        anchors.fill: parent
        anchors.centerIn: parent

        CellGrid{
            Layout.fillHeight: true
            Layout.fillWidth: true

            message: "Hello"
            model: universe
        }
        Button{
            text: "Next Step"
            onClicked:{
                console.log("tick")
                universe.tick()
            }
        }
    }
}
