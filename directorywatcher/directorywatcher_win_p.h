#ifndef WINDOWSDIRECTORYWATCHERPRIVATE_H
#define WINDOWSDIRECTORYWATCHERPRIVATE_H

#include "directorywatcher_p.h"

#include <string>

class WindowsDirectoryWatcherPrivate : public DirectoryWatcherPrivate
{
public:
    WindowsDirectoryWatcherPrivate();
    ~WindowsDirectoryWatcherPrivate() = default;

    bool setPath(const std::wstring directory) override;
    void clearPath() override;

    void setCallBack(const Callback &callback) override;
};

#endif // WINDOWSDIRECTORYWATCHERPRIVATE_H
