import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Particles 2.0

import Asteroids 1.0

Window {
    id: main
    width: 1022
    height: 412
    visible: true
    Item {
        id: gameWindow
        ShaderEffectSource {
            id: shaderSrc
            sourceItem: Image { id: img; source: "qrc:/cityscape.gif" }
            wrapMode: ShaderEffectSource.Repeat
        }

        anchors.fill: parent
        state: "ready"
        focus: true
        states: [
            State {
                name: "ready"

            },
            State {
                name: "play"
                PropertyChanges {target: startText; visible: false}
                StateChangeScript {
                    name: "startGame"
                    script: {

                        field.startField();
                    }
                }

            },
            State {
                name: "done"
                when: rocket.isAlive==FALSE
                PropertyChanges {target: overText; visible: false}
            }

        ]


        MouseArea {
            anchors.fill: parent
            onMouseXChanged: {
                rocket.x = Math.min(mouseX, 200);
            }
            onMouseYChanged: {
                rocket.y = mouseY;
            }
        }

        property bool moveLeft: false
        property bool moveRight: false
        property bool moveUp: false
        property bool moveDown: false

        Timer {
            id: animationTimer
            interval: 16
            running: true
            repeat: true
            onTriggered: {
                if (parent.state == "play") {
                    //do animation here
                    var step=10
                    if (parent.moveDown) rocket.y = Math.min(main.height-rocket.height, rocket.y + step);
                    if (parent.moveUp) rocket.y = Math.max(0, rocket.y - step);
                    if (parent.moveLeft) rocket.x = Math.max(0, rocket.x - step);
                    if (parent.moveRight) rocket.x = Math.min(200, rocket.x + step);

                    // Collision of ship with asteroid
                    //if () {
                    //    rocket.killMeNow()
                    //}

                    // Collision of bullet with asteroid

                }
            }

        }

        Keys.onPressed: {
            if (event.key == Qt.Key_Down) {
                console.log("DOWN")
                moveDown = true;
            }
            if (event.key == Qt.Key_Up) {
                moveUp =true
            }
            if (event.key == Qt.Key_Left) {
                moveLeft = true
            }
            if (event.key == Qt.Key_Right) {
                moveRight = true
            }
            if (event.key == Qt.Key_Space) {
                var component = Qt.createComponent("Bullet.qml");
                var object = component.createObject(gameWindow, {
                                                        "x":rocket.x + rocket.width, "y":rocket.y + rocket.height/2});

            }
        }

        Keys.onReleased: {
            if (event.key == Qt.Key_Down) {
                console.log("DOWN")
                moveDown = false;
            }
            if (event.key == Qt.Key_Up) {
                moveUp =false
            }
            if (event.key == Qt.Key_Left) {
                moveLeft = false
            }
            if (event.key == Qt.Key_Right) {
                moveRight = false
            }

        }

        AnimatedImage {
            id: rocket
            z: 2
            width: 50
            height: 50
            x: 100
            y: 100
            property bool isAlive

            Behavior on x { NumberAnimation {duration: 200}}
            Behavior on y { NumberAnimation {duration: 200}}

            function killMeNow() {
                isAlive = false
                visible = false
                var component = Qt.createComponent("ShipExplosion.qml");
                var object = component.createObject(gameWindow, {
                                                        "x":rocket.x + rocket.width/2, "y":rocket.y + rocket.height/2});
                gameWindow.state = "done"
            }

            source: "qrc:/spaceship1__flyingA.gif"
            rotation: 90
            visible: gameWindow.state==="play"
        }

        Text {
            id: startText
            z: 1
            anchors.centerIn: parent
            text: "Click to start"
            font.pixelSize: 100
            color: "white"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    gameWindow.state = "play"
                }
            }

        }
        Text {
            id: overText
            anchors.centerIn: parent
            text: "GAME OVER"
            font.pixelSize: 100
            color: "white"
            visible: false
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    gameWindow.state = "ready"
                }
            }

        }



        ParticleSystem {
            id: particleSystem
            anchors.fill: parent
            Emitter {
                group: "stars"
                emitRate: 10
                lifeSpan: 40000
                enabled: true
                startTime: 40000
                size: 20
                sizeVariation: 10
                velocity: PointDirection {y: 20; yVariation: 10}
                width: parent.width
            }

            ImageParticle {
                id: stars
                z: 1
                groups: ["stars"]
                source: "Smoke.png"
                color: "white"
                colorVariation: 0.1
                alpha: 0.5
            }

        }
        ShaderEffect {
            anchors.fill: parent
            property variant src: shaderSrc
            z: 0

            property real time: 0
            NumberAnimation on time{
                running: true
                from: 0
                to: 1
                duration: 10000
                loops: Animation.Infinite

            }

            vertexShader: "
                       uniform highp mat4 qt_Matrix;
                       attribute highp vec4 qt_Vertex;
                       attribute highp vec2 qt_MultiTexCoord0;
                       varying highp vec2 coord;
                       void main() {
                           coord = qt_MultiTexCoord0;
                           gl_Position = qt_Matrix * qt_Vertex;
                       }"
            fragmentShader: "
                        varying highp vec2 coord;
                        uniform sampler2D src;
                        uniform float time;

                        void main()
                        {
                            gl_FragColor = texture2D( src, vec2((coord.x+time), coord.y) );
                        }"
        }
    }

    AsteroidField {
        id: field

        anchors.fill: parent
    }
}
