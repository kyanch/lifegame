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
                    required property int cell
                    required property int index
                    width: 40
                    height: 40
                    color: cell == 1 ? "black" : "cyan"
                    Text {
                        text: parent.cell
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Rectangle " + parent.index + " clicked!");
                            root.model.set_cell(parent.index, parent.cell ? 0 : 1);
                        }
                    }
                }
            }
        }
    }
}
