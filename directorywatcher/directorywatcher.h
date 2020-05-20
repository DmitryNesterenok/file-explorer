#ifndef DIRECTORYWATCHER_H
#define DIRECTORYWATCHER_H

#include "directorywatcherhelper.h"

#include <memory>
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
    std::unique_ptr<DirectoryWatcherPrivate> d_ptr;
};

#endif // DIRECTORYWATCHER_H
