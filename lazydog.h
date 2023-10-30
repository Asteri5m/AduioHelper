
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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QProcess>


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
    // 手动连接
    void auto_change_outaudiodevice();
    void trayIcon_activated(QSystemTrayIcon::ActivationReason reason);
    void tray_mainPage_triggered();
    void tray_modeChoose_triggered();
    void tray_checkNew_triggered();
    void tray_settings_triggered();
    void tray_exit_triggered();

    // UI自动生成
    void on_pushButton_renew_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_change_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_checknew_clicked();
    void on_checkBox_autostart_clicked(bool checked);
    void on_checkBox_adminstart_clicked(bool checked);
    void on_checkBox_autochecknew_clicked(bool checked);
    void on_checkBox_defaultdevice_clicked(bool checked);
    void on_radioButton_window_clicked();
    void on_radioButton_process_clicked();
    void on_comboBox_defaultdevice_currentTextChanged(const QString &devicename);
    void on_keySequenceEdit_start_keySequenceChanged(const QKeySequence &keySequence);
    void on_keySequenceEdit_changemode_keySequenceChanged(const QKeySequence &keySequence);
    void on_keySequenceEdit_changeup_keySequenceChanged(const QKeySequence &keySequence);
    void on_keySequenceEdit_changedown_keySequenceChanged(const QKeySequence &keySequence);

    void on_checkBox_autohidden_clicked(bool checked);

    void on_checkBox_changemsg_clicked(bool checked);

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
    LazyConfig lazyconfig;
    bool m_enableHandling = false;

public:
    bool autoHidden = true;

private:
    void InitSystemTray();
    void InitProcessTabview();
    void InitMonitorTabview();
    void InitSettingConfig();
    void InitAudioDeviceList();
    void RenewProcessTabview();
    void RenewMonitorTabview();
    void ShowDebugText(QString level, QString text);
    void SaveBindListToXml();
    BindList LoadBindListFromXml();
    QMap<QString, QString> JsonToMap(QByteArray data);
    void SaveSettingConfig();

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // LAZYDOG_H
