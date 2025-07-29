#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ScriptEditor;
}
QT_END_NAMESPACE

class ScriptEditor : public QMainWindow
{
    Q_OBJECT

public:
    ScriptEditor(QWidget *parent = nullptr);
    ~ScriptEditor();

protected:
    void closeEvent(QCloseEvent *event) override;


private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_connectButton_clicked();
    void on_executeButton_clicked();
    void readResponse();

private:
    Ui::ScriptEditor *ui;
    QUdpSocket *udpSocket;
    QString currentFile;
    bool isConnected;

    void setCurrentFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);
};
#endif // SCRIPTEDITOR_H
