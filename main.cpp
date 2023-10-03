
#include "lazydog.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LazyDog w;
    w.show();
    return a.exec();
}
