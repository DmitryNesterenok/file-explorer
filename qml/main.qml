import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Window {
    visible: true
    width: 1000
    height: 660
    title: qsTr("File explorer")

    ColumnLayout {
        spacing: 10
        anchors.margins: 10
        anchors.fill: parent

        RowLayout {
            id: controls
            spacing: 10
            Layout.fillWidth: true

            Button {
                id: renameButton
                enabled: fileView.currentIndex !== -1
                text: qsTr("Rename")
                onClicked: renameDialog.show(fileView.model.nameAt(fileView.currentIndex))
            }

            RoundButton {
                id: upButton
                text: "\u2191"
                font.pointSize: 20
                Layout.minimumWidth: height
                onClicked: {
                    fileView.currentIndex = -1
                    worker.upDirectory()
                }
            }

            Text {
                id: dirTextEdit
                Layout.fillWidth: true
                font.pointSize: 14
                elide: Text.ElideMiddle
                text: worker.currentPath
            }
        }

        FileView {
            id: fileView
            model: worker.filesModel
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            id: filesCountText

            Layout.fillWidth: true
            text: qsTr("Elements: %1").arg(fileView.count)
            font.pointSize: 16
        }
    }


    Dialog {
        id: renameDialog

        property string oldName

        function show(name) {
            visible = true
            renameDialog.oldName = name
            renameTextEdit.text = name
        }

        title: qsTr("Rename")
        width:  700
        height: 120

        TextField {
            id: renameTextEdit
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 30
            font.pointSize: 14
        }

        onAccepted: {
            fileView.currentIndex = -1
            worker.rename(oldName, renameTextEdit.text)
        }
    }
}
