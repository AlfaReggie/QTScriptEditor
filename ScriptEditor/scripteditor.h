#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QCloseEvent>
#include <QObject>

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

#endif // SCRIPTEDITOR_H
