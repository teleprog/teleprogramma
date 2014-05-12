#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
        paths.append(".");
        paths.append("./imageformats");
        paths.append("./platforms");
        paths.append("./sqldrivers");
        QCoreApplication::setLibraryPaths(paths);


    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();

    UnitTest t;
    t.autoTest();


    LoginWindow login;
    login.checkSettings();
    if (login.connection()!=0)
          login.show();

    return a.exec();
}
