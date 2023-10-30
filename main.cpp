
#include "lazydog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LazyDog w;
    w.show();

    if (w.autoHidden) // 自动隐藏
        w.hide();
    return a.exec();
}
