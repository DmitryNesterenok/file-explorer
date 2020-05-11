import QtQuick 2.12

ListView {
    id: fileView
    clip: true
    currentIndex: -1

    headerPositioning: ListView.PullBackHeader
    header: Rectangle {
        implicitWidth: fileView.width
        implicitHeight: 50
        color: "#AAAAAA"

        Row {
            anchors.leftMargin: 30
            anchors.rightMargin: 30
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: nameTitle
                width: parent.width - modifiedDateTitle.width - sizeTitle.width
                font.pointSize: 14
                elide: Text.ElideRight
                text: qsTr("Name")
            }

            Text {
                id: modifiedDateTitle
                width: 200
                font.pointSize: 11
                text: qsTr("Modified Date")
            }

            Text {
                id: sizeTitle
                width: 100
                font.pointSize: 11
                text: qsTr("Size")
                horizontalAlignment: Text.AlignRight
            }
        }
    }

    delegate: Rectangle {
        implicitWidth: fileView.width
        implicitHeight: 50
        border.width: 1
        color: fileView.currentIndex === index ? "#98FB98" : "white"

        MouseArea {
            id: mouseArea

            function enterToDirectory() {
                fileView.currentIndex = -1
                if (isDir)
                    worker.enterToDirectory(name)
            }

            anchors.fill: parent
            onDoubleClicked: enterToDirectory()
            onClicked: {
                if (fileView.currentIndex === index)
                    enterToDirectory()
                else
                    fileView.currentIndex = index
            }
        }

        Row {
            anchors.leftMargin: 30
            anchors.rightMargin: 30
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            Text {
                id: nameText
                width: parent.width - modifiedDateText.width - sizeText.width
                font.pointSize: 14
                font.bold: isDir
                elide: Text.ElideRight
                text: name
            }

            Text {
                id: modifiedDateText
                width: 200
                font.pointSize: 11
                text: modifiedDate
            }

            Text {
                id: sizeText

                function getSizeText() {
                    var limit = Math.pow(1000, 3)
                    if (size >= limit)
                        return qsTr("%1 GB").arg(Math.ceil(size / limit))

                    limit = limit / 1000
                    if (size >= limit)
                        return qsTr("%1 MB").arg(Math.ceil(size / limit))

                    limit = limit / 1000
                    if (size >= limit)
                        return qsTr("%1 kB").arg(Math.ceil(size / limit))

                    return qsTr("%1 B").arg(size)
                }

                width: 100
                font.pointSize: 11
                text: isDir ? "" : getSizeText()
                horizontalAlignment: Text.AlignRight
            }
        }
    }
}
