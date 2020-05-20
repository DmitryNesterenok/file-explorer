#ifndef WINDOWSDIRECTORYWATCHERPRIVATE_H
#define WINDOWSDIRECTORYWATCHERPRIVATE_H

#include "directorywatcher_p.h"

#include <memory>
#include <string>

class DirectoryInfo;
class WindowsDirectoryWatcherPrivate : public DirectoryWatcherPrivate
{
public:
    WindowsDirectoryWatcherPrivate();
    ~WindowsDirectoryWatcherPrivate();

    bool setPath(const std::wstring directory) override;
    void clearPath() override;

    void setCallBack(const Callback &callback) override;

    std::unique_ptr<DirectoryInfo> directoryInfo;
};

#endif // WINDOWSDIRECTORYWATCHERPRIVATE_H
