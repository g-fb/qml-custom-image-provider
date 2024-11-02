import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Image {
        anchors.centerIn: parent
        source: "image://provider_name//path/to/image.jpg"
        width: 300
        height: 500
        sourceSize.width: 200
        sourceSize.height: 300
    }
}
