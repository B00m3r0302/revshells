import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
 width: 800; height: 600
 visible: true
 title: "Reverse Shell Generator"
 Material.theme: Material.Dark
 Material.accent: Material.Teal

 ColumnLayout {
  anchors.fill: parent; anchors.margins: 20; spacing: 16

  ComboBox { id: langBox; Layout.fillWidth: true; model: ["Bash", "Python"] }
  RowLayout {
   TextField { id: ipField; placeholderText: "LHOST"; Layout.fillWidth: true }
   TextField { id: portField; placeholderText: "LPORT"; Layout.fillWidth: true
   }
   ComboBox {
    id: encodingBox
    model: ["None", "URL", "DoubleURL", "Base64"]
    Layout.fillWidth: true
   }

   Button {
    text: "Generate"
    Layout.alignment: Qt.AlignCenter
    onClicked: generator.generate(langBox.currentText, ipField.text, portField.text, encodingBo.currentText)
   }

   TextArea {
    text: generator.payload
    readOnly: true
    Layout.fillWidth: true
    Layout.fillHeight: true
    font.family: "Monospace"
   }

   Button {
    text: "Copy"
    Layout.alignment: Qt.AlignRight
    onClicked: Qt.callLater(() => Qt.application.clipboard.setText(generator.payload))
   }
 }
}
