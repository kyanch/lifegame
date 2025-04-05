import QtQuick

/*
* Add Zoom and scale function for CellGrid.
*/

Flickable {
    id: root

    property real scale: 1
    property real minScale: 0.1
    property real maxScale: 5.0

    signal mouseMoved(x: real, y: real)

    contentHeight: cell_grid.world_height
    contentWidth: cell_grid.world_width

    clip: true
    CellGrid {
        id: cell_grid
        anchors.fill: parent

        model: universe
        cellSize: 20
    }
    WheelHandler {}
    PinchArea {
        enabled: false
        anchors.fill: parent
        pinch.target: cell_grid
        pinch.maximumScale: root.maxScale
        pinch.minimumScale: root.minScale
        onPinchStarted: function (event) {
            console.log("Pinch Start");
        }
        onPinchUpdated: function (event) {
            console.log("Pinch Update" + event.scale + "\t" + root.contentX, ",", root.contentY);
        }
        onPinchFinished: function (event) {
            console.log("Pinch Finished");
        }
    }

    MouseArea {
        enabled: true
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        preventStealing: true
        onPositionChanged: function (event) {
            // pass this event through
            event.accepted = false;
            root.mouseMoved(event.x, event.y);
        }
    }
}
