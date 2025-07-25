#include "scripteditor.h"
#include "ui_scripteditor.h"

ScriptEditor::ScriptEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScriptEditor)
{
    ui->setupUi(this);
}

ScriptEditor::~ScriptEditor()
{
    delete ui;
}
