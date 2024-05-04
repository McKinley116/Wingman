#include "wingman.h"
#include <QPushButton>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wingman w;
    w.show();



    return a.exec();
}
