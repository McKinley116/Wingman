#include "wingman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wingman w;
    w.show();
    return a.exec();
}
