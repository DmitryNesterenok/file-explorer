#include "directorywatcher.h"

#include "directorywatcher_win_p.h"

DirectoryWatcher::DirectoryWatcher()
{
    d_ptr = new WindowsDirectoryWatcherPrivate();
}

DirectoryWatcher::~DirectoryWatcher()
{
    d_ptr->clearPath();
}

bool DirectoryWatcher::setPath(const std::wstring directory)
{
    return d_ptr->setPath(directory);
}

void DirectoryWatcher::clearPath()
{
    d_ptr->clearPath();
}

void DirectoryWatcher::setCallBack(const Callback &callback)
{
    d_ptr->setCallBack(callback);
}
