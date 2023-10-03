
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include <QStringList>
#include "custom.h"

//音频相关
#include <Mmdeviceapi.h>
#include <Endpointvolume.h>
#include <functiondiscoverykeys.h>
#include <Audioclient.h>
#include <Devicetopology.h>


class AudioManager
{
public:
    AudioManager();
    AudioDeviceList GetOutAudioDeviceList();
    bool SetOutAudioDevice(QString DeviceId);
    QString GetDefaultAudioDevice();
};

#endif // AUDIOMANAGER_H
