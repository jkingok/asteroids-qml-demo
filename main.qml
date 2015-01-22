import QtQuick 2.4
import QtQuick.Window 2.2
import Asteroids 1.0

Window {
    visible: true
    width: 360
    height: 360

    AsteroidField {
        id: field
        anchors.fill: parent

        Component.onCompleted: {
            field.startField();
        }
    }

//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            Qt.quit();
//        }
//    }
}
