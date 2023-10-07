
#ifndef LAZYDOG_H
#define LAZYDOG_H

#include <QMainWindow>
#include "taskmonitor.h"
#include "audiomanager.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QIcon>
#include <QScrollBar>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QAction>


QT_BEGIN_NAMESPACE
namespace Ui { class LazyDog; }
QT_END_NAMESPACE

class LazyDog : public QMainWindow

{
    Q_OBJECT

public:
    LazyDog(QWidget *parent = nullptr);
    ~LazyDog();

private slots:
    // UI自动生成
    void on_pushButton_renew_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_change_clicked();
    void on_pushButton_delete_clicked();
    // 手动连接
    void auto_change_outaudiodevice();
    void trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
    void tray_mainPage_triggered();
    void tray_modeChoose_triggered();
    void tray_settings_triggered();
    void tray_exit_triggered();

private:
    Ui::LazyDog *ui;
    TaskMonitor* taskmonitor;
    AudioManager* audiomanager;
    QSystemTrayIcon *trayIcon;
    QAction *modeChooseAction;

    AudioDeviceList outaudiodevicelist;
    ProcessList processlist;
    BindInfo currentbindinfo;
    BindList bindlist;
    BindMap bindmap;

private:
    void InitSystemTray();
    void InitProcessTabview();
    void InitMonitorTabview();
    void InitAudioDeviceList();
    void RenewProcessTabview();
    void RenewMonitorTabview();
    void ShowDebugText(QString level, QString text);
    void SaveBindListToXml();
    BindList LoadBindListFromXml();

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // LAZYDOG_H
