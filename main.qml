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

        ship: ship

        onShipDestroyed: {
            ship.visible = false;
        }
    }

    Rectangle {
        id: b1
        x: 100
        y: 100
        width: 50
        height: 50
        color: "blue"

        Component.onCompleted: {
            field.bulletCreated(b1);
        }
    }

    Rectangle {
        id: ship
        anchors.centerIn: parent
        width: 100
        height: 100
        visible: true
        color: "red"
    }

//    Image {
//        source: "qrc:/meteor.png"
//        anchors.fill: parent
//    }

//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            Qt.quit();
//        }
//    }
}
