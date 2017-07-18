import QtQuick 2.3
import QtQuick.Window 2.2
import QtGStreamer 1.0

Rectangle {
    id: window
    width: 720
    height: 610

    Column {
        VideoItem {
            id: video

            width: window.width
            height: window.height
            surface: videoSurface1 // initialized from main()
        }
    }
}
