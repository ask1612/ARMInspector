import QtQuick 2.4
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4

Page 
{
    Rectangle
    {
        anchors.fill: parent
        color: "#222840"
        Column 
        {
            anchors.centerIn: parent
            TextInput {
                id: teLogin
                width: 180
                height: 32
                text: qsTr("Login")
                maximumLength: 10
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                clip: true
                color: "#FFFFFF"
            }
        
            Row
            {
                TextInput {
                    id: tePassword
                    width: 180
                    height: 32
                    maximumLength: 6
                    cursorVisible: false
                    echoMode: TextInput.Password
                    horizontalAlignment: Text.AlignHCenter
                    text: qsTr("Password")
                    font.pixelSize: 24
                    color: "#FFFFFF"
                }
                Button
                {
                    width: 32
                    height: 32
                    contentItem: Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        Image 
                        {
                            id: icon
                            anchors.fill: parent
                            source: "qrc:/Icons/eye.png"
    //                            control.down ? "#FA8072" : "#696969"
                            width: parent.height
                            height: parent.height
                        }
                    }
                }
            }
        }
    }
}
