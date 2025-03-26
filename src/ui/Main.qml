import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ScrollView {
        width: parent.width
        height: parent.height
        Grid {
            id: grid
            columns: universe.columns()

            spacing: 0.5
            property int cell_size: 20

            Repeater {
                model: universe

                Rectangle {
                    width: grid.cell_size
                    height: grid.cell_size
                    border.color: 'red'
                    color: modelData == 1 ? 'black' : 'cyan'

                    MouseArea{
                        anchors.fill : parent
                        onClicked:{
                            parent.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1)
                            console.log(parent.index+"@"+parent.modelData)
                            universe.setData(parent.index,modelData==1?0:1)
                            console.log(modelData)
                        }

                    }

                }
            }
        }
    }
}
