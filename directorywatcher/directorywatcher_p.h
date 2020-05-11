#ifndef DIRECTORYWATCHER_P_H
#define DIRECTORYWATCHER_P_H

#include "directorywatcherhelper.h"

#include <string>

class DirectoryWatcher;
class DirectoryWatcherPrivate
{
public:
    DirectoryWatcherPrivate() = default;
    virtual ~DirectoryWatcherPrivate() = default;

    virtual bool setPath(const std::wstring directory) = 0;
    virtual void clearPath() = 0;

    virtual void setCallBack(const Callback &callback) = 0;
};

#endif // DIRECTORYWATCHER_P_H
