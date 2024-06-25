
#include "lazydog.h"
#include "ui_lazydog.h"

#include <QDebug>


LazyDog::LazyDog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LazyDog)
{
    ui->setupUi(this);

    //初始化系统托盘
    InitSystemTray();
    //初始化音频设备列表
    InitAudioDeviceList();
    //初始化进程窗口
    InitProcessTabview();
    //初始化监控窗口
    InitMonitorTabview();
    //初始化配置（设置）
    InitSettingConfig();

    //链接槽函数
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000); // 设置定时器间隔为1秒
    connect(timer, &QTimer::timeout, this, &LazyDog::auto_change_outaudiodevice);
    timer->start(); // 启动定时器
}

LazyDog::~LazyDog()
{
    delete ui;
}

//初始化系统托盘
void LazyDog::InitSystemTray()
{
    // 创建系统托盘图标
    trayIcon = new QSystemTrayIcon(QIcon(":/LD_64.ico"));
    trayIcon->setToolTip("LazyDogTools");
    trayIcon->show();

    // 创建托盘菜单
    QMenu *trayMenu = new QMenu();
    QAction *mainPageAction = new QAction("主界面");
    modeChooseAction = new QAction("进程模式");
    QAction *checknewAction = new QAction("检查更新");
    QAction *settingsAction = new QAction("设置");
    QAction *exitAction = new QAction("退出");

    // 将菜单项添加到托盘菜单
    trayMenu->addAction(mainPageAction);
    trayMenu->addAction(modeChooseAction);
    trayMenu->addAction(checknewAction);
    trayMenu->addAction(settingsAction);
    trayMenu->addSeparator(); // 添加分隔线
    trayMenu->addAction(exitAction);

    // 将托盘菜单设置为系统托盘图标的菜单
    trayIcon->setContextMenu(trayMenu);

    // 处理菜单项的点击事件
    connect(mainPageAction, &QAction::triggered, this, &LazyDog::tray_mainPage_triggered);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &LazyDog::trayIcon_activated);
    connect(modeChooseAction, &QAction::triggered, this, &LazyDog::tray_modeChoose_triggered);
    connect(checknewAction, &QAction::triggered, this, &LazyDog::tray_checkNew_triggered);
    connect(settingsAction, &QAction::triggered, this, &LazyDog::tray_settings_triggered);
    connect(exitAction, &QAction::triggered, this, &LazyDog::tray_exit_triggered);

    trayIcon->showMessage("程序启动成功", "欢迎使用，您的工具已准备就绪", QSystemTrayIcon::Information, 5000);
}

//初始化进程窗口
void LazyDog::InitProcessTabview()
{
    //设置选中时为整行选中
    ui->tableView_process->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->tableView_process->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //根据内容自动调整列宽、行高
    ui->tableView_process->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_process->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // 隐藏垂直表头，即隐藏行号
    ui->tableView_process->verticalHeader()->setVisible(false);

    // 更新进程任务列表
    taskmonitor = new TaskMonitor();
    RenewProcessTabview();
    // 重新调整第1列宽度
    ui->tableView_process->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
}

//初始化监控窗口
void LazyDog::InitMonitorTabview()
{
    //设置选中时为整行选中
    ui->tableView_monitor->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置表格的单元为只读属性，即不能编辑
    ui->tableView_monitor->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //根据内容自动调整列宽、行高
    ui->tableView_monitor->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_monitor->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // 隐藏垂直表头，即隐藏行号
    ui->tableView_monitor->verticalHeader()->setVisible(false);

    // 读取配置文件
    bindlist = LoadBindListFromXml();
    // 初始化hashmap
    int index = 0;
    BindInfo infobuf;
    for (;index < bindlist.length(); index++)
    {
        infobuf = bindlist.at(index);
        bindmap[infobuf.exepath] = index;
    }
    ShowDebugText(D_Info, "读取绑定信息配置文件完成");

    // 更新进程任务列表
    RenewMonitorTabview();
}

// 初始化配置（设置）
void LazyDog::InitSettingConfig()
{
    QFile file(configfile);
    bool readfileOK = true;
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in >> lazyconfig;
        file.close();
    }
    else
        readfileOK = false;

    if (lazyconfig.isEmpty() || !readfileOK)
    {
        ShowDebugText(D_Error, "读取配置文件失败，正在初始化设置");
        lazyconfig[Config.Autostart] = "false";
        lazyconfig[Config.Adminstart] = "false";
        lazyconfig[Config.Autochecknew] = "true";
        lazyconfig[Config.Autohidden] = "true";
        lazyconfig[Config.Changemsg] = "true";
        lazyconfig[Config.Defaultdevide] = "false";
        lazyconfig[Config.Defaultdevideid] = "";
        lazyconfig[Config.Defaultdevidename] = "";
        lazyconfig[Config.Mode] = "process";
        lazyconfig[Config.Keystart] = "";
        lazyconfig[Config.Keychangemode] = "";
        lazyconfig[Config.Keychangup] = "";
        lazyconfig[Config.Keychangdown] = "";
        SaveSettingConfig();
    }
    else
        ShowDebugText(D_Info, "读取配置文件成功，成功导入设置选项");

    // 输出从文件中加载的数据
    QMap<QString, QString>::const_iterator it;
    for (it = lazyconfig.constBegin(); it != lazyconfig.constEnd(); ++it) {
        qDebug() << it.key() << ": " << it.value();
    }

    if (lazyconfig.value(Config.Autostart) == "true")
        ui->checkBox_autostart->setChecked(true);

    if (lazyconfig.value(Config.Adminstart) == "true")
        ui->checkBox_adminstart->setChecked(true);

    if (lazyconfig.value(Config.Autochecknew) == "true")
    {
        ui->checkBox_autochecknew->setChecked(true);
        on_pushButton_checknew_clicked();
    }

    if (lazyconfig.value(Config.Autohidden) == "true")
        ui->checkBox_autohidden->setChecked(true);
    else
        autoHidden = false;

    if (lazyconfig.value(Config.Changemsg) == "true")
        ui->checkBox_changemsg->setChecked(true);

    if (lazyconfig.value(Config.Defaultdevide) == "true")
        ui->checkBox_defaultdevice->setChecked(true);
    else
        ui->comboBox_defaultdevice->setEnabled(false);

    if (lazyconfig.value(Config.Defaultdevidename) != ""
        && outaudiodevicelist.value(Config.Defaultdevidename) != "" )
        ui->comboBox_defaultdevice->setCurrentText(Config.Defaultdevidename);

    if (lazyconfig.value(Config.Mode) == "process")
        ui->radioButton_process->setChecked(true);
    else
    {
        ui->radioButton_window->setChecked(true);
        modeChooseAction->setText("窗口模式");
    }

    m_enableHandling = true;
}

//初始化音频设备列表
void LazyDog::InitAudioDeviceList()
{
    // 获取音频输出列表
    audiomanager = new AudioManager();
    outaudiodevicelist = audiomanager->GetOutAudioDeviceList();
    currentbindinfo.deviceid = audiomanager->GetDefaultAudioDevice();

    // 使用迭代器遍历QMap
    AudioDeviceList::const_iterator outputiter;
    for (outputiter = outaudiodevicelist.constBegin(); outputiter != outaudiodevicelist.constEnd(); ++outputiter) {
        // 设置关联选项
        ui->comboBox_add->addItem(outputiter.key());
        ui->comboBox_change->addItem(outputiter.key());
        ui->comboBox_defaultdevice->addItem(outputiter.key());
    }
}

//更新进程任务列表视图
void LazyDog::RenewProcessTabview()
{
    // 清除原来的数据
    processlist.clear();
    processlist = taskmonitor->GetTaskList();

    // 创建数据模型
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHorizontalHeaderItem(0, new QStandardItem("PID"));
    model->setHorizontalHeaderItem(1, new QStandardItem("进程"));
    int row;
    ProcessList::const_iterator iter;
    for(iter = processlist.constBegin(), row = 0; iter != processlist.constEnd(); ++iter, ++row)
    {
        qDebug() << iter->pid << "|" << iter->name << "|" << iter->path;

        // 添加数据
        QList<QStandardItem*> Item;
        Item.append(new QStandardItem(QString::number(iter->pid)));
        Item.append(new QStandardItem(iter->name));
        model->appendRow(Item);

        // 设置图标
        SHFILEINFO shfi;
        memset(&shfi, 0, sizeof(SHFILEINFO));
        // 使用SHGetFileInfo函数获取EXE文件的图标
        if (SHGetFileInfo(reinterpret_cast<const wchar_t*>(iter->path.utf16()), 0, &shfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON))
        {
            QIcon exeFileIcon = QIcon(QPixmap::fromImage(QImage::fromHICON(shfi.hIcon)));
            model->setData(model->index(row, 1), exeFileIcon, Qt::DecorationRole);
        }

    }

    // 将数据模型设置到QTableView中
    ui->tableView_process->setModel(model);
    ui->tableView_process->update();
//    ui->debugBrowser->append("更新进程列表完成，进程总数：" + QString::number(processlist.length()));
    ShowDebugText(D_Info, "更新进程列表完成，进程总数：" + QString::number(processlist.length()));
}

//更新监控列表视图
void LazyDog::RenewMonitorTabview()
{
    // 创建数据模型
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHorizontalHeaderItem(0, new QStandardItem("进程"));
    model->setHorizontalHeaderItem(1, new QStandardItem("关联设备"));
    int row;
    BindList::const_iterator iter;
    for(iter = bindlist.constBegin(), row = 0; iter != bindlist.constEnd(); ++iter, ++row)
    {
        // 添加数据
        QList<QStandardItem*> Item;
        Item.append(new QStandardItem(iter->taskname));
        Item.append(new QStandardItem(iter->devicename));
        model->appendRow(Item);

        // 设置图标
        SHFILEINFO shfi;
        memset(&shfi, 0, sizeof(SHFILEINFO));
        // 使用SHGetFileInfo函数获取EXE文件的图标
        if (SHGetFileInfo(reinterpret_cast<const wchar_t*>(iter->exepath.utf16()), 0, &shfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON))
        {
            QIcon exeFileIcon = QIcon(QPixmap::fromImage(QImage::fromHICON(shfi.hIcon)));
            model->setData(model->index(row, 0), exeFileIcon, Qt::DecorationRole);
        }

    }

    // 将数据模型设置到QTableView中
    ui->tableView_monitor->setModel(model);
    ui->tableView_monitor->update();
}

/**
 * @brief LazyDog::ShowDebugText
 * @param level debug等级
 * @param text  debug信息内容
 */
void LazyDog::ShowDebugText(QString level, QString text)
{
    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString timeStr = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    QString buffer = QString("%1 [%2] %3").arg(timeStr).arg(level.at(0)).arg(text);
    ui->debugBrowser->append(buffer);
    // 将滚动条定位到底部 --- 自动刷新
    ui->debugBrowser->verticalScrollBar()->setValue(ui->debugBrowser->verticalScrollBar()->maximum());
}

// 将bindlist保存至xml文件，文件名在custom.h中
void LazyDog::SaveBindListToXml()
{
    QFile file(bindfile);
    if (file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("BindList");

        for (const BindInfo& bindInfo : bindlist) {
            xmlWriter.writeStartElement("BindInfo");
            xmlWriter.writeTextElement("TaskName", bindInfo.taskname);
            xmlWriter.writeTextElement("ExePath", bindInfo.exepath);
            xmlWriter.writeTextElement("DeviceName", bindInfo.devicename);
            xmlWriter.writeTextElement("DeviceId", bindInfo.deviceid);
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}

//从文件中读取bindlist的配置信息
QList<BindInfo> LazyDog::LoadBindListFromXml()
{
    BindList bindList;
    QFile file(bindfile);
    if (file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader xmlReader(&file);

        while (!xmlReader.atEnd()) {
            if (xmlReader.isStartElement() && xmlReader.name().toString() == "BindInfo") {
                BindInfo bindInfo;
                while (!(xmlReader.isEndElement() && xmlReader.name().toString() == "BindInfo")) {
                    xmlReader.readNext();
                    if (xmlReader.isStartElement()) {
                        QString elementName = xmlReader.name().toString();
                        if (elementName == "TaskName") {
                            bindInfo.taskname = xmlReader.readElementText();
                        } else if (elementName == "ExePath") {
                            bindInfo.exepath = xmlReader.readElementText();
                        } else if (elementName == "DeviceName") {
                            bindInfo.devicename = xmlReader.readElementText();
                        } else if (elementName == "DeviceId") {
                            bindInfo.deviceid = xmlReader.readElementText();
                        }
                    }
                }
                bindList.append(bindInfo);
            } else {
                xmlReader.readNext();
            }
        }

        file.close();
    }
    return bindList;
}

//json数据转为QMap
QMap<QString, QString> LazyDog::JsonToMap(QByteArray data)
{
    QMap<QString, QString> mapData;
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        QString buffer = QString("解析配置信息出错");
        ShowDebugText(D_Error, "检查更新失败，" + buffer);
        trayIcon->showMessage("检查更新失败", buffer, QSystemTrayIcon::Critical, 5000);
        return mapData;
    }
    QJsonObject jsonObj = jsonDoc.object();
    mapData.insert("version", jsonObj.value("version").toString());
    mapData.insert("datatime", jsonObj.value("datatime").toString());

    return mapData;
}

//保存设置到配置文件
void LazyDog::SaveSettingConfig()
{
    // 写入QMap数据到文件
    QFile file(configfile);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << lazyconfig;
        file.close();
        ShowDebugText(D_Info, "设置已更改，已成功保存至配置文件中");
        return;
    }
    ShowDebugText(D_Warn, "设置已更改，保存至配置文件失败，仅本次运行生效");
}

//设置开机自启动
bool LazyDog::SetAutostartAtPoweron(bool setFlag)
{
    QString regPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    QString key = "LazyDogTools";
    bool result = false;
    if(setFlag){
        QString myPath = QString("\"%1\"").arg(QCoreApplication::applicationFilePath());
        qDebug() << "exe path:" << myPath;
        result = AddRegedit(regPath, key, myPath);
    }else {
        result = DelRegedit(regPath, key);
    }

    QString text = result ? "修改开机启动项成功": "修改开机启动项失败";
    ShowDebugText(D_Info, text);
    return result;
}

//添加注册表
bool LazyDog::AddRegedit(QString regpath, QString key, QString value)
{
    // 将 QString 转换为 const wchar_t*，因为 Windows API 使用的是 wchar_t*
    LPCWSTR subkey = reinterpret_cast<LPCWSTR>(regpath.utf16());
    LPCWSTR entry = reinterpret_cast<LPCWSTR>(key.utf16());
    LPCWSTR data = reinterpret_cast<LPCWSTR>(value.utf16());

    // 打开注册表项
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        qDebug() << "Error opening registry key:" << result;
        ShowDebugText(D_Error, "打开注册表失败，错误代码：" + QString::number(result));
        return false;
    }

    // 设置注册表值
    result = RegSetValueEx(hKey, entry, 0, REG_SZ, reinterpret_cast<const BYTE*>(data), (wcslen(data) + 1) * sizeof(wchar_t));
    if (result != ERROR_SUCCESS) {
        qDebug() << "Error setting registry value:" << result;
        RegCloseKey(hKey);
        ShowDebugText(D_Error, "设置注册表失败，错误代码：" + QString::number(result));
        return false;
    }

    // 关闭注册表项
    RegCloseKey(hKey);
    ShowDebugText(D_Info, "修改注册表成功");
    return true;
}

//删除注册表
bool LazyDog::DelRegedit(QString regpath, QString key)
{
    // 将 QString 转换为 const wchar_t*，因为 Windows API 使用的是 wchar_t*
    LPCWSTR subkey = reinterpret_cast<LPCWSTR>(regpath.utf16());
    LPCWSTR entry = reinterpret_cast<LPCWSTR>(key.utf16());

    // 打开注册表项
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS) {
        qDebug() << "Error opening registry key:" << result;
        ShowDebugText(D_Error, "打开注册表失败，错误代码：" + QString::number(result));
        return false;
    }

    // 删除注册表值
    result = RegDeleteValue(hKey, entry);
    if (result != ERROR_SUCCESS) {
        qDebug() << "Error deleting registry value:" << result;
        RegCloseKey(hKey);
        ShowDebugText(D_Error, "设置注册表失败，错误代码：" + QString::number(result));
        return false;
    }

    // 关闭注册表项
    RegCloseKey(hKey);
    ShowDebugText(D_Info, "修改注册表成功");
    return true;
}

//重写关闭信号
void LazyDog::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}

//槽函数：刷新任务列表
void LazyDog::on_pushButton_renew_clicked()
{
    // 更新进程任务列表
    RenewProcessTabview();
}

//槽函数：添加绑定
void LazyDog::on_pushButton_add_clicked()
{
    // 获取选择内容
    QString audiodevicename = ui->comboBox_add->currentText();
    int tabviewindex = ui->tableView_process->currentIndex().row();

    // 合法性判断
    if (tabviewindex < 0 || tabviewindex >= processlist.length())
    {
        ShowDebugText(D_Error, "未选择任务进程，请选择后再进行绑定");
        return;
    }
    if (bindmap.contains(processlist.at(tabviewindex).path))
    {
        ShowDebugText(D_Error, "该任务已在监控列表中");
        return;
    }

    // 绑定
    BindInfo infobuf;
    infobuf.devicename = audiodevicename;
    infobuf.deviceid = outaudiodevicelist[audiodevicename];
    infobuf.exepath = processlist.at(tabviewindex).path;
    infobuf.taskname = processlist.at(tabviewindex).name;
    bindlist.append(infobuf);
    bindmap[infobuf.exepath] = bindlist.length() - 1;

    RenewMonitorTabview();
    ShowDebugText(D_Info, "绑定成功, 信息如下:");
    ShowDebugText(D_Info, "进程ID: " + QString::number(processlist.at(tabviewindex).pid) + ", 进程名: " + infobuf.taskname);
    ShowDebugText(D_Info, "绑定设备: " + audiodevicename);
    SaveBindListToXml();
}

//槽函数：更改绑定
void LazyDog::on_pushButton_change_clicked()
{
    // 获取选择内容
    QString audiodevicename = ui->comboBox_change->currentText();
    int tabviewindex = ui->tableView_monitor->currentIndex().row();

    // 合法性判断
    if (tabviewindex < 0 || tabviewindex >= processlist.length())
    {
        ShowDebugText(D_Error, "未选择任务进程，请选择后再进行更改");
        return;
    }

    // 更改
    BindInfo infobuf;
    infobuf.devicename = audiodevicename;
    infobuf.deviceid = outaudiodevicelist[audiodevicename];
    infobuf.exepath = bindlist.at(tabviewindex).exepath;
    infobuf.taskname = bindlist.at(tabviewindex).taskname;
    bindlist[tabviewindex] = infobuf;

    RenewMonitorTabview();
    ShowDebugText(D_Info,infobuf.taskname + " 已更改绑定设备：" + infobuf.devicename);
    SaveBindListToXml();
}

//槽函数：取消绑定
void LazyDog::on_pushButton_delete_clicked()
{
    // 获取选择内容
    int tabviewindex = ui->tableView_monitor->currentIndex().row();

    // 合法性判断
    if (tabviewindex < 0 || tabviewindex >= processlist.length())
    {
        ShowDebugText(D_Error, "未选择任务进程，请选择后再进行更改");
        return;
    }

    // 删除list
    QString deltaskname = bindlist.at(tabviewindex).taskname;
    QString delexepath = bindlist.at(tabviewindex).exepath;
    bindlist.removeAt(tabviewindex);

    // 更新hashmap
    bindmap.remove(delexepath);
    int index = tabviewindex;
    BindInfo infobuf;
    for (;index < bindlist.length(); index++)
    {
        infobuf = bindlist.at(index);
        bindmap[infobuf.exepath] = index;
    }

    RenewMonitorTabview();
    ShowDebugText(D_Info,deltaskname + " 已取消绑定设备");
    SaveBindListToXml();
}

//槽函数：自动任务
void LazyDog::auto_change_outaudiodevice()
{
    // 模式选择
    if (lazyconfig.value(Config.Mode) == "window")
    {
        QString windowprocessmame = taskmonitor->GetWindow();
        if (bindmap.contains(windowprocessmame))
        {
            int index = bindmap[windowprocessmame];
            BindInfo infobuf = bindlist.at(index);
            // 检查是否需要切换设备,以免音频卡顿
            if (currentbindinfo.deviceid == infobuf.deviceid) return;
            audiomanager->SetOutAudioDevice(infobuf.deviceid); // 切换设备
            qDebug()<< "切换设备" << infobuf.deviceid;
            currentbindinfo = infobuf;
            QString buffer = QString("检测到窗口%1，已切换至设备%2").arg(infobuf.taskname).arg(infobuf.devicename);
            ShowDebugText(D_Info, buffer);
            if (lazyconfig.value(Config.Changemsg) == "true")
                trayIcon->showMessage("切换设备", buffer, QSystemTrayIcon::Information, 3000);
            return;
        }
        return;
    }

    // 获取当前进程状态
    ProcessList processlistbuf = taskmonitor->GetTaskList();
    ProcessList::const_iterator iter;
    // 逆序匹配
    for (iter=--processlistbuf.end(); iter!=processlistbuf.begin(); iter--)
    {
        // 检查是否匹配成功
        if (bindmap.contains(iter->path))
        {
            int index = bindmap[iter->path];
            BindInfo infobuf = bindlist.at(index);
            // 检查是否需要切换设备,以免音频卡顿
            if (currentbindinfo.deviceid == infobuf.deviceid) return;
            audiomanager->SetOutAudioDevice(infobuf.deviceid); // 切换设备
            qDebug()<< "切换设备" << infobuf.deviceid;
            currentbindinfo = infobuf;
            QString buffer = QString("检测到进程%1，已切换至设备%2").arg(infobuf.taskname).arg(infobuf.devicename);
            ShowDebugText(D_Info, buffer);
            if (lazyconfig.value(Config.Changemsg) == "true")
                trayIcon->showMessage("切换设备", buffer, QSystemTrayIcon::Information, 3000);
            return;
        }
    }

    if (lazyconfig.value(Config.Defaultdevide) == "true")
    {
        if (currentbindinfo.deviceid == lazyconfig.value(Config.Defaultdevideid)) return;
        audiomanager->SetOutAudioDevice(lazyconfig.value(Config.Defaultdevideid)); // 切换设备
        currentbindinfo.deviceid = lazyconfig.value(Config.Defaultdevideid);
        currentbindinfo.devicename = lazyconfig.value(Config.Defaultdevidename);
        currentbindinfo.exepath = "";
        currentbindinfo.taskname = "";
        QString buffer = QString("未检测到任何进程，已切回默认设备%1").arg(currentbindinfo.devicename);
        ShowDebugText(D_Info, buffer);
        if (lazyconfig.value(Config.Changemsg) == "true")
            trayIcon->showMessage("切换设备", buffer, QSystemTrayIcon::Information, 5000);
    }
}

//托盘---双击
void LazyDog::trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        // 双击托盘图标时显示主窗口
        if (this->isHidden())
            this->show();
        this->activateWindow();
    }
}

//托盘---主界面
void LazyDog::tray_mainPage_triggered()
{
    if (this->isHidden())
        this->show();
    ui->mainWidget->setCurrentWidget(ui->tab_process);
    this->activateWindow();
}

//托盘---选择模式
void LazyDog::tray_modeChoose_triggered()
{
    QString modeText = modeChooseAction->text()=="进程模式" ? "窗口模式" : "进程模式";
    modeChooseAction->setText(modeText);

    if (modeText == "进程模式")
        ui->radioButton_process->click();
    else
        ui->radioButton_window->click();
}


//托盘---检查更新
void LazyDog::tray_checkNew_triggered()
{
    ui->pushButton_checknew->click();
}

//托盘---设置
void LazyDog::tray_settings_triggered()
{
    ui->mainWidget->setCurrentWidget(ui->tab_seting);
    if (this->isHidden())
        this->show();
}

//托盘---退出
void LazyDog::tray_exit_triggered()
{
    QApplication::quit();
}

//设置---检查更新
void LazyDog::on_pushButton_checknew_clicked()
{
    QString newVersion, oldVersion, newDatatime, oldDatatime;

    QFile file("update/config");
    if (!file.open(QIODevice::ReadOnly))
    {
        oldVersion = QCoreApplication::applicationVersion();
        oldDatatime = 0;
    } else
    {
        QByteArray data = file.readAll();
        QMap<QString, QString> oldmap = JsonToMap(data);
        if (oldmap.isEmpty())
            return;
        oldVersion = oldmap.value("version");
        oldDatatime = oldmap.value("datatime");
    }

    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl("https://lazydog.asteri5m.icu/update/config"));
    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QMap<QString, QString> newmap = JsonToMap(data);
        if (newmap.isEmpty())
            return;
        newVersion = newmap.value("version");
        newDatatime = newmap.value("datatime");
    } else
    {
        QString buffer = QString("获取服务器数据失败");
        ShowDebugText(D_Error, "检查更新失败，" + buffer);
        trayIcon->showMessage("检查更新失败", buffer, QSystemTrayIcon::Critical, 5000);
        return;
    }

    if(newVersion==oldVersion && newDatatime==oldDatatime)
    {
        QString buffer = QString("暂无更新版本");
        ShowDebugText(D_Info, "检查更新完成，" + buffer);
        trayIcon->showMessage("检查更新完成", buffer, QSystemTrayIcon::Information, 5000);

    } else
    {
        bool isHidden = this->isHidden();
        if (isHidden)
            this->show();
        QString buffer = QString("新版本：%1").arg(newVersion);
        ShowDebugText(D_Info, "检查更新完成，" + buffer);
        int choice = QMessageBox::question(nullptr,
                                           "检查到新版本",
                                           QString("是否马上更新？              \n\n当前版本：%1\n新版本：%2").arg(oldVersion).arg(newVersion),
                                           QMessageBox::Yes | QMessageBox::No);

        if (choice == QMessageBox::Yes)
        {
            QProcess process;
            process.startDetached("update");
            process.waitForStarted();
            QApplication::quit();
        }else {
            if (isHidden)
                this->hide();
        }
    }
}

//设置---开机自启动
void LazyDog::on_checkBox_autostart_clicked(bool checked)
{
    QString boolString = checked ? "true" : "false";
    lazyconfig[Config.Autostart] = boolString;
    if(SetAutostartAtPoweron(checked)){
        SaveSettingConfig();
    }else {
        ui->checkBox_autostart->setChecked(!checked);
    }

}

//设置---管理员模式启动
void LazyDog::on_checkBox_adminstart_clicked(bool checked)
{
    QString boolString = checked ? "true" : "false";
    lazyconfig[Config.Adminstart] = boolString;
    SaveSettingConfig();
}

//设置---自动检测跟新
void LazyDog::on_checkBox_autochecknew_clicked(bool checked)
{
    QString boolString = checked ? "true" : "false";
    lazyconfig[Config.Autochecknew] = boolString;
    SaveSettingConfig();
}

//设置---开启默认设备
void LazyDog::on_checkBox_defaultdevice_clicked(bool checked)
{
    QString boolString = checked ? "true" : "false";
    lazyconfig[Config.Defaultdevide] = boolString;
    lazyconfig[Config.Defaultdevidename] = ui->comboBox_defaultdevice->currentText();
    lazyconfig[Config.Defaultdevideid] = outaudiodevicelist.value(lazyconfig.value(Config.Defaultdevidename));
    ui->comboBox_defaultdevice->setEnabled(checked);
    SaveSettingConfig();
}

//设置---启动自动隐藏
void LazyDog::on_checkBox_autohidden_clicked(bool checked)
{
    QString boolString = checked ? "true" : "false";
    lazyconfig[Config.Autohidden] = boolString;
    SaveSettingConfig();
}

//设置---切换时通知
void LazyDog::on_checkBox_changemsg_clicked(bool checked)
{
    QString boolString = checked ? "true" : "false";
    lazyconfig[Config.Changemsg] = boolString;
    SaveSettingConfig();
}

//设置---切换默认设备
void LazyDog::on_comboBox_defaultdevice_currentTextChanged(const QString &devicename)
{
    // 初始化完成前忽略
    if (!m_enableHandling) return;

    lazyconfig[Config.Defaultdevidename] = devicename;
    lazyconfig[Config.Defaultdevideid] = outaudiodevicelist.value(devicename);
    SaveSettingConfig();
}

//设置---选择模式:进程
void LazyDog::on_radioButton_process_clicked()
{
    lazyconfig[Config.Mode] = "process";
    modeChooseAction->setText("进程模式");
    SaveSettingConfig();
}

//设置---选择模式:窗口
void LazyDog::on_radioButton_window_clicked()
{
    lazyconfig[Config.Mode] = "window";
    modeChooseAction->setText("窗口模式");
    SaveSettingConfig();
}



void LazyDog::on_keySequenceEdit_start_keySequenceChanged(const QKeySequence &keySequence)
{
    QKeySequence seq(QKeySequence::fromString(keySequence.toString().split(", ").first()));
    ui->keySequenceEdit_start->setKeySequence(seq);
}


void LazyDog::on_keySequenceEdit_changemode_keySequenceChanged(const QKeySequence &keySequence)
{
    QKeySequence seq(QKeySequence::fromString(keySequence.toString().split(", ").first()));
    ui->keySequenceEdit_changemode->setKeySequence(seq);
}


void LazyDog::on_keySequenceEdit_changeup_keySequenceChanged(const QKeySequence &keySequence)
{
    QKeySequence seq(QKeySequence::fromString(keySequence.toString().split(", ").first()));
    ui->keySequenceEdit_changeup->setKeySequence(seq);
}


void LazyDog::on_keySequenceEdit_changedown_keySequenceChanged(const QKeySequence &keySequence)
{

    QKeySequence seq(QKeySequence::fromString(keySequence.toString().split(", ").first()));
    ui->keySequenceEdit_changedown->setKeySequence(seq);
}
