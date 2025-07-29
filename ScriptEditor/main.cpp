#include "scripteditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ScriptEditor editor;
    editor.show();
    return app.exec();
}
