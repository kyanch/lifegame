import QtQuick
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    GridLayout{
        anchors.fill: parent

        CellGrid{
            Layout.fillHeight: true
            Layout.fillWidth: true

            message: "Hello"
        }
    }
}
