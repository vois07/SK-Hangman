#include "widget.h"
#include <QApplication>
#include <QMainWindow>
#include<QtWidgets>
#include<QtNetwork>
#include <QPlainTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
