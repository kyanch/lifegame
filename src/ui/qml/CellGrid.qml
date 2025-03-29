pragma ComponentBehavior: Bound
import QtQuick

Item {
    id: root

    property string message: "example text"

    Repeater{
        model: 1000
        Text{
            anchors.centerIn: parent
            text: root.message
            color: 'cyan'
        }

    }
}