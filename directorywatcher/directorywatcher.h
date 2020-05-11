#ifndef DIRECTORYWATCHER_H
#define DIRECTORYWATCHER_H

#include "directorywatcherhelper.h"

#include <string>

class DirectoryWatcherPrivate;
class DirectoryWatcher
{
public:
    DirectoryWatcher();
    virtual ~DirectoryWatcher();

    bool setPath(const std::wstring directory);
    void clearPath();

    void setCallBack(const Callback &callback);

private:
    DirectoryWatcherPrivate *d_ptr = nullptr;
};

#endif // DIRECTORYWATCHER_H
