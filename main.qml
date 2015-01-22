import QtQuick 2.4
import QtQuick.Window 2.2
import Asteroids 1.0

Window {
    visible: true

    AsteroidField {
        anchors.fill: parent
    }

//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            Qt.quit();
//        }
//    }
}
