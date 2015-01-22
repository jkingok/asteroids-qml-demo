import QtQuick 2.0

AnimatedImage {
    source: "explosion.gif"
    onCurrentFrameChanged: {
        if (currentFrame == frameCount - 1)
            destroy();
    }
}
