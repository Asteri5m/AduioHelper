
#include "lazydog.h"
#include "UAC.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LazyDog w;

    // 以管理员权限启动一个新实例
    if (w.adminStart)
    {
        if (UAC::runAsAdmin())
        {
            return 0; // 启动成功，当前程序退出
        } // 未启动，当前程序继续
    }

    w.show();

    if (w.autoHidden) // 自动隐藏
        w.hide();
    return a.exec();
}
