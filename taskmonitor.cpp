
#include "taskmonitor.h"
#include <QDebug>

TaskMonitor::TaskMonitor()
{

}

/**
 * @brief TaskMonitor::GetTaskList 获取系统进程列表
 * @return 返回ProcessList(QList<ProcessInfo>)
 */
ProcessList TaskMonitor::GetTaskList()
{
    ProcessList TaskList;
    // 获取系统中所有进程的进程ID
    DWORD processes[1024];
    DWORD needed;
    if (!EnumProcesses(processes, sizeof(processes), &needed))
    {
        qDebug() << "EnumProcesses failed.";
        return TaskList;
    }

    // 计算实际返回的进程数量
    DWORD numProcesses = needed / sizeof(DWORD);

    for (DWORD i = 0; i < numProcesses; ++i)
    {
        DWORD processId = processes[i];

        // 打开进程
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
        if (hProcess != nullptr)
        {
            // 获取进程的启动时间
//            FILETIME ftCreation, ftExit, ftKernel, ftUser;
//            SYSTEMTIME stCreation, lstCreation;
//            if ( !GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftKernel, &ftUser)) {
//                CloseHandle(hProcess);
//                continue;
//            }
//            FileTimeToSystemTime(&ftCreation, &stCreation);
//            SystemTimeToTzSpecificLocalTime(NULL, &stCreation, &lstCreation);
//            // 转化为QString
//            ULONGLONG ull = ((ULONGLONG)ftCreation.dwHighDateTime << 32) | ftCreation.dwLowDateTime;
//            QString fileTimeStr = QString::number(ull);

//            qDebug() << processId << "\t|" << ull;

            // 获取进程的可执行文件路径
            TCHAR processPath[MAX_PATH];
            DWORD size = sizeof(processPath) / sizeof(TCHAR);
            if (QueryFullProcessImageName(hProcess, 0, processPath, &size))
            {
                // 获取进程名称
                TCHAR processName[MAX_PATH];
                lstrcpyn(processName, processPath, MAX_PATH);
                PathStripPath(processName); // 从路径中提取文件名

                QString drivepath = QString::fromWCharArray(processPath);
                // 将QString转换为UTF-16编码的wchar_t数组
                const wchar_t* wdrivepath = reinterpret_cast<const wchar_t*>(drivepath.utf16());
                QString processDescription = QString::fromWCharArray(processName);
                // 获取exe的description
                DWORD dummy;
                DWORD fileInfoSize = GetFileVersionInfoSize(wdrivepath, &dummy);
                if (fileInfoSize > 0)
                {
                    std::vector<BYTE> buffer(fileInfoSize);
                    if (GetFileVersionInfo(wdrivepath, 0, fileInfoSize, &buffer[0]))
                    {
                        std::vector<BYTE> target = {70, 0, 105, 0, 108, 0, 101, 0, 68, 0, 101, 0, 115, 0, 99, 0, 114, 0, 105, 0, 112, 0, 116, 0, 105, 0, 111, 0, 110, 0, 0, 0, 0, 0};
                        // 使用 std::search 函数查找匹配的字节序列
                        auto result = std::search(buffer.begin(), buffer.end(), target.begin(), target.end());
                        // 检查是否找到匹配
                        if (result != buffer.end())
                        {
                            // 计算匹配的字节序列的起始下标
                            std::ptrdiff_t index = std::distance(buffer.begin(), result);
                            // 判断标志位是否为真，为真则存在描述，否则不存在
                            if (buffer[index-4])
                            {
                                const wchar_t* wprocessDescription = reinterpret_cast<const wchar_t*>(&buffer[index+34]);
                                processDescription = QString::fromWCharArray(wprocessDescription);
                            }
                        }
                    }
                }
                AddProcessMap(processId, processDescription, drivepath, &TaskList);

            }
            CloseHandle(hProcess);
        }
    }
    return TaskList;
}


/**
 * @brief TaskMonitor::AddProcessMap 私有接口-将数据添加到列表里
 * @param pid [in] 任务的pid
 * @param name [in] 任务的friendname
 * @param path [in] 执行文件的驱动器地址
 * @param processList [out] 需要将数据添加到结果地址
 */
void TaskMonitor::AddProcessMap(unsigned long pid, QString name, QString path, ProcessList *processList)
{
    ProcessInfo processInfo;
    processInfo.pid = pid;
    processInfo.name = name;
    processInfo.path = path;
    processList->append(processInfo);
}
