import QtQuick 2.4
import QtQuick.Controls 1.2

TableView {
    id: wordView
    //Component.onCompleted: Units.multiplier = 1.9
    anchors.fill: parent
//    frameVisible: true
    model: LearningDirectionModel
backgroundVisible: false
frameVisible: true
    //            Keys.onUpPressed: {
    //                print("(Up - Table) index: (" + wordView.currentRow + "," + wordView.currentColumn+ ")")
    //                if (wordView.currentRow > 0){
    //                    wordView.currentRow--

    //                }
    //            }
    //            Keys.onDownPressed: {
    //                print("(Down - Table) index: (" + wordView.currentRow + "," + wordView.currentColumn+ ")")
    //                if (wordView.currentRow < wordView.rowCount - 1)
    //                    wordView.currentRow++
    //            }
    TableViewColumn {
        id: wordColumn;
        title: qsTr("Word");
        role: "word";
        width: 100;

    }
    TableViewColumn {
        id: transcriptionColumn;
        title: qsTr("Transcription");
        role: "transcription";
        width: 100   }
    TableViewColumn {
        id: translationColumn;
        title: qsTr("Translation");
        role: "translation";
        width: wordView.width-wordColumn.width-transcriptionColumn.width
    }
}
