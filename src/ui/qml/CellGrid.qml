pragma ComponentBehavior: Bound
import QtQuick

Item {
    id: root

    property string message: "example text"
    property var model

    // This Rectangle is only for debug
    Rectangle {
        anchors.centerIn: parent
        anchors.fill: parent
        color: "red"

        Grid {
            columns: root.model.columns()
            anchors.centerIn: parent
            anchors.fill: parent
            padding: 1

            Repeater {
                model: root.model

                Rectangle {
                    id: cell
                    required property int modelData
                    required property int index
                    width: 40
                    height: 40
                    color: modelData === 1 ? "black" : "cyan"
                    Text {
                        text: cell.index
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Rectangle " + cell.index + " clicked!");
                            cell.modelData = !cell.modelData;
                        }
                    }
                }
            }
        }
    }
}
