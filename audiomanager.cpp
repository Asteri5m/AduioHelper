
#include "audiomanager.h"
#include "PolicyConfig.h"
#include <QDebug>

AudioManager::AudioManager()
{

}

/**
 * @brief AudioManager::GetOutAudioDeviceList 获取输出音频的设备列表
 * @return 返回一个QMap<key: friendname, value: deviceId>
 */
AudioDeviceList AudioManager::GetOutAudioDeviceList()
{
    AudioDeviceList outaudiodevicelist;
    qDebug("Audio Output Devices:");
    // 初始化COM接口
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        qDebug("Failed to initialize COM.");
        return outaudiodevicelist;
    }

    IMMDeviceEnumerator* pEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr)) {
        qDebug("Failed to create device enumerator.");
        CoUninitialize();
        return outaudiodevicelist;
    }

    // 获取设备集合
    IMMDeviceCollection* pDeviceCollection = NULL;
    hr = pEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDeviceCollection);
    if (FAILED(hr)) {
        qDebug("Failed to enumerate audio endpoints.");
        return outaudiodevicelist;
    }

    UINT deviceCount;
    pDeviceCollection->GetCount(&deviceCount);
    // 遍历设备
    for (UINT i = 0; i < deviceCount; i++) {
        IMMDevice* pDevice = NULL;
        pDeviceCollection->Item(i, &pDevice);
        // 获取设备ID
        LPWSTR pwszID = NULL;
        pDevice->GetId(&pwszID);

        IPropertyStore* pProps = NULL;
        hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
        if (SUCCEEDED(hr)) {
            // 获取设备友好名字
            PROPVARIANT varName;
            PropVariantInit(&varName);
            hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
            if (SUCCEEDED(hr)) {
                QString deviceName = QString::fromWCharArray(varName.pwszVal);
                QString deviceID = QString::fromWCharArray(pwszID);
                qDebug() << "Device" << i + 1 << ":" << deviceID << "|" << deviceName;
                PropVariantClear(&varName);
                outaudiodevicelist.insert(deviceName, deviceID);
            }

            pProps->Release();
        }
        CoTaskMemFree(pwszID);
        pDevice->Release();
    }
    pDeviceCollection->Release();
    return outaudiodevicelist;
}

/**
 * @brief AudioManager::SetOutAudioDevice 修改输出音频设备
 * @param DeviceId [in] 需要切换的目标设备的ID
 * @return success 成功返回true,失败返回false
 */
bool AudioManager::SetOutAudioDevice(QString DeviceId)
{
    // 将QString转换为UTF-16编码的wchar_t数组
    const wchar_t* wcharStr = reinterpret_cast<const wchar_t*>(DeviceId.utf16());
    // 将wchar_t数组转换为LPWSTR
    LPWSTR devID = const_cast<LPWSTR>(wcharStr);
    IPolicyConfigVista* pPolicyConfig;
    ERole reserved = eConsole;

    HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient),
                                  NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID*)&pPolicyConfig);
    if (SUCCEEDED(hr))
    {
        hr = pPolicyConfig->SetDefaultEndpoint(devID, reserved);
        pPolicyConfig->Release();
    }

    // 成功返回true
    if (SUCCEEDED(hr)) {
        return true;
    }
    return false;
}

/**
 * @brief AudioManager::GetDefaultAudioDevice 获取当前使用的音频设备
 * @return 返回当前设备的id
 */
QString AudioManager::GetDefaultAudioDevice()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        qDebug("Failed to initialize COM.");
        return "0";
    }

    IMMDeviceEnumerator* pEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr)) {
        qDebug("Failed to create device enumerator.");
        CoUninitialize();
        return "0";
    }

    // 获取设备
    IMMDevice* pDefaultPlaybackDevice = NULL;
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDefaultPlaybackDevice);
    if (SUCCEEDED(hr))
    {
        // 获取设备ID
        LPWSTR pwszID = NULL;
        pDefaultPlaybackDevice->GetId(&pwszID);
        QString deviceID = QString::fromWCharArray(pwszID);
        return deviceID;
    }
    return "0";
}

