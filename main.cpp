#include "principal.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Principal w;

    QFontDatabase::addApplicationFont("/fonts/DejaVuSans.ttf");

    QFont font = QFont("DejaVuSans",10);

    a.setFont(font);

    w.show();

    return a.exec();
}
