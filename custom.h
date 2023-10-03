
#ifndef CUSTOM_H
#define CUSTOM_H
#include <QList>
#include <QMap>

//进程数据相关
struct ProcessInfo
{
    //pid
    unsigned long pid;
    //文件路径
    QString path;
    //进程名
    QString name;
};
#define ProcessList QList<ProcessInfo>

//音频设备---key:friendname,value:deviceId
#define AudioDeviceList QMap<QString, QString>

//绑定数据相关
struct BindInfo
{
    //任务名
    QString taskname;
    //exe文件路径
    QString exepath;
    //设备友好名字
    QString devicename;
    //设备id
    QString deviceid;
};
//绑定数据的列表,无序列表按添加时间排序
#define BindList QList<BindInfo>
//绑定数据的hashmap,便于快速定位绑定关系---key:exepath,valve:ListIndex
#define BindMap QMap<QString, int>

//debug等级
#define D_Info "INFO"
#define D_Warn "WARN"
#define D_Error "ERROR"

#define bindfile "bindlist.xml"


#endif // CUSTOM_H
