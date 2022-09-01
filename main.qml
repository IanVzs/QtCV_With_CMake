import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

import com.permission.module 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Button {
        id: openBtn
        height: 25
        text: "浏览..."
        onClicked: {
            file_dialog.open();
        }
        Label {
            id: label_file_path
            text: ""
            height: 25
            anchors.left: openBtn.right
            anchors.leftMargin: 10
        }
        FileDialog {
            id: file_dialog
            title: "选择文件"
            folder: shortcuts.desktop
            nameFilters: ["image files (*.png *.jpg *.jpeg *.bmp)"]
            onAccepted: {
                label_file_path.text = file_dialog.fileUrl;
                console.log("You chose: " + file_dialog.fileUrl);
                img111.source = file_dialog.fileUrl;
            }
            onRejected: {
                label_file_path.text = "";
                console.log("Canceled");
                Qt.quit();
            }
        }
    }
//    Button {
//        id: andPermission_msg
//        text: "niubile"
//    }
    Image {
        id: img111
        source: ""
    }
    AndPermission {
        id: andPermission
        onFromCheckPermission: {
            console.log("tick: onFromCheckPermission")
            andPermission_msg.text = msg
        }
        onNameChanged: {
            console.log("fuck?")
        }
    }
}
