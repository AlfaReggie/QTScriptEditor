#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QMainWindow>

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

private:
    Ui::ScriptEditor *ui;
};
#endif // SCRIPTEDITOR_H
