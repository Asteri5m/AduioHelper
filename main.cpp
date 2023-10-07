
#include "lazydog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LazyDog w;
    w.show();
    //启动隐藏主界面
    Sleep(800);
    w.hide();
    return a.exec();
}
