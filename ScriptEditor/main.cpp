#include "scripteditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScriptEditor w;
    w.show();
    return a.exec();
}
