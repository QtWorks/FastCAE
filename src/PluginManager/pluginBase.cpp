#include "pluginBase.h"
#include <QTranslator>
#include <QSettings>
#include <QCoreApplication>
#ifdef Q_OS_WIN
#include <windows.h>
#include <WinBase.h>
#endif

#ifdef Q_OS_UNIX
#include <dlfcn.h>
#endif
#include <QDebug>

namespace Plugins
{

PluginBase::PluginBase()
{
    _translator = new QTranslator;
}

PluginBase::~PluginBase()
{
    if (_translator != nullptr) delete _translator;

#ifdef Q_OS_WIN
#ifndef _DEBUG
    //	bool ok = FreeLibrary(_winModule);
#endif
#endif

#ifdef Q_OS_LINUX
    //dlclose(_linuxModule);
#endif
}

void PluginBase::setFileName(QString f)
{
    _libFileName = f;
}

QString PluginBase::getFileName()
{
    return _libFileName;
}

Plugins::PluginType PluginBase::getPluginType()
{
    return _pluginType;
}

void PluginBase::readINI(QSettings* settings)
{
    Q_UNUSED(settings)
}
void PluginBase::writeINI(QSettings*)
{

}

#ifdef Q_OS_WIN
void PluginBase::setWinModule(HMODULE m)
{
    _winModule = m;
}

HMODULE PluginBase::getWinModule()
{
    return _winModule;
}

#endif

QString PluginBase::getDescribe()
{
    return _describe;
}

bool PluginBase::uninstall()
{
    QString path = qApp->applicationDirPath();
    QSettings settingwrite(path + "/FastCAE.ini", QSettings::IniFormat);
    this->writeINI(&settingwrite);

    return false;
}

bool PluginBase::install()
{
    QString path = qApp->applicationDirPath();
    QSettings settingreader(path + "/FastCAE.ini", QSettings::IniFormat);
    this->readINI(&settingreader);

    return false;
}

void PluginBase::reTranslate(QString lang)
{
    qDebug() << lang;
}

void PluginBase::exec(int commandType)
{
    Q_UNUSED(commandType)
}

#ifdef Q_OS_LINUX
void PluginBase::setLinuxModule(void* m)
{
    _linuxModule = m;
}

void* PluginBase::getLinuxModule()
{
    return _linuxModule;
}




#endif
void PluginBase::setType(PluginType t)
{
    _pluginType = t;
}

Plugins::PluginType PluginBase::getType()
{
    return _pluginType;
}


void PluginBase::writeToProjectFile(QDomDocument* doc, QDomElement* parent)
{
    Q_UNUSED(doc)
    Q_UNUSED(parent)
}

void PluginBase::readFromProjectFile(QDomElement* parentEle)
{
    Q_UNUSED(parentEle)
}

bool PluginBase::hasInfoToSave()
{
    return false;
}

}


