pragma ComponentBehavior: Bound
import QtQuick

Item {
    id: root

    property var model
    property real cellSize

    property alias columns: cell_grid.columns
    property alias gap: cell_grid.spacing
    property real world_height: (columns * (cellSize + gap) - gap) * scale
    property real world_width: world_height

    // This Rectangle is only for debug
    Grid {
        id: cell_grid
        columns: root.model.columns()
        anchors.centerIn: parent
        anchors.fill: parent
        spacing: 1

        Repeater {
            model: root.model

            Rectangle {
                required property int cell
                required property int index
                width: root.cellSize
                height: root.cellSize
                color: cell == 1 ? "black" : "cyan"
                Text {
                    anchors.centerIn: parent
                    text: parent.index % root.columns
                    font.pointSize: 10
                    color: parent.cell == 1 ? "gray" : "black"
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        console.log("Rectangle " + parent.index + " clicked!");
                        root.model.set_cell(parent.index, parent.cell ? 0 : 1);
                    }
                }
            }
        }
    }
}
