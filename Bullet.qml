import QtQuick 2.0

Rectangle {
    id: rect
    width: 6
    height: 6
    color: "white"
    border.width: 1
    border.color: "black"
    NumberAnimation on opacity {
        to: 0
        duration: 2000
        onRunningChanged: {
            if (!running) {
                rect.destroy();
            }
        }
    }
    NumberAnimation on x {
        to: 1000
        duration: 2000
    }

    Component.onCompleted: {
        // Let Josh know about this bullet
    }

    function onHitAsteroid(x, y) {
        // delete this bullet
        rect.destroy()
        // create explosion
    }
}

