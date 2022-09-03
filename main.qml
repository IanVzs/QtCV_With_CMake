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
    MenuBar {
        id: "menubar"
        Menu {
            title: "文件"
            MenuItem {
                text: "打开图像..."
                onTriggered: {
                    file_dialog.open()
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
            MenuItem {
                text: "保存图像"
                onTriggered: {
                    // 使用save作为保存标识 => 实现并不优雅，但还是挺有用
                    img111.source = "image://previewprovider/save/" + file_dialog.fileUrl
                }
            }
        }
        Menu {
            title: "特效"
            MenuItem {
                text: "转为灰度图"
                onTriggered: {
                    img111.source = ""
                    img111.source = "image://previewprovider/" + file_dialog.fileUrl
                }
            }
        }
    }
    Label {
        id: label_file_path
        text: ""
        color: "#ffffff"
        height: 25
        anchors.top: menubar.bottom
        anchors.leftMargin: 10
    }
    Image {
        z: -1
        id: img111
        cache: true
        anchors.top: menubar.bottom
        source: ""
        anchors.fill: parent
        sourceSize.width: parent.width
        sourceSize.height: parent.height
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
