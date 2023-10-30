
#ifndef TASKMONITOR_H
#define TASKMONITOR_H

//win32 api
#include <Windows.h>
#include <Shlwapi.h>
#include <Psapi.h>
#include <Shlobj.h>

#include "custom.h"


class TaskMonitor
{
public:
    TaskMonitor();
    ProcessList GetTaskList();
    QString GetWindow();

private:
    void AddProcessMap(unsigned long, QString, QString, ProcessList*);

};

#endif // TASKMONITOR_H
