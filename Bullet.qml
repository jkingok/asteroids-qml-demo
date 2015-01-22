import QtQuick 2.0

Rectangle {
    id: rect
    width: 6
    height: 6
    color: "white"
    border.width: 1
    border.color: "black"

    property var field

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
        field.bulletCreated(rect);
    }

    function collided() {
        // delete this bullet
        field.bulletDestroyed(rect);
        rect.destroy()
        // create explosion
    }
}

