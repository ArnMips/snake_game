#include "mainwindow.h"
#include "wgt_pages/dialog_property.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  
    MainWindow w(0);

    QFontDatabase::addApplicationFont(":/fonts/Rust.ttf");
    QFontDatabase::addApplicationFont(":/fonts/RustNew.ttf");

    QFile file;
    switch(w.getStyle()){
        case 0:
        file.setFileName(":/BlueStyle/Styles/Blue.css");
        break;
    case 1:
        file.setFileName(":/PurpleStyle/Styles/Purple.css");
        break;
    case 2:
        file.setFileName(":/BeigeStyle/Styles/Biege.css");
        break;
    }
    file.open(QIODevice::ReadOnly);
    a.setStyleSheet(file.readAll());
    file.close();

    return a.exec();
}
