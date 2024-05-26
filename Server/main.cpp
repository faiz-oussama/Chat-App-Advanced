#include "mainwindow.h"

#include <QApplication>
#include "DatabaseManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initializeDatabase("client_chat.db");
    MainWindow w;
    w.show();
    return a.exec();
}
