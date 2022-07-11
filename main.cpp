#include "snake.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Snake* w = new Snake();
    w->show();
    return a.exec();
}
