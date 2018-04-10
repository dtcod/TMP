import QtQuick 2.10
import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Controls 2.2
import TMPCore 1.0 as TM
ApplicationWindow{
    visible:  true
    width: 1080
    height: 700
    title: "TMP 1.0"
    TM.Viewer{
        id: tm
        anchors.fill: parent
        MouseArea{
            id: tmMouse
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

        }

    }
    Connections{
        target: tmMouse
        property point ppos: Qt.point(0,0)
        onPressed: {
            ppos = Qt.point(mouse.x, mouse.y)
        }
        onDoubleClicked:{
            tm.doubleClick(mouse.x, mouse.y)
        }

        onPositionChanged: {
            if(mouse.buttons & Qt.LeftButton)
                tm.rotate(mouse.x-ppos.x, mouse.y - ppos.y)
            else if(mouse.buttons & Qt.RightButton){
                tm.move(mouse.x-ppos.x, mouse.y - ppos.y)
            }
            ppos = Qt.point(mouse.x, mouse.y)
        }

    }
}
