#include "stock_portal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    stock_portal w;
    w.show();

    return a.exec();
}
