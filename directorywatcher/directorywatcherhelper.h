#ifndef DIRECTORYWATCHERHELPER_H
#define DIRECTORYWATCHERHELPER_H

#include <functional>

enum class FileAction
{
    Unknown,
    FileAdded,
    FileRemoved,
    FileModified
};

using Callback = std::function<void(const std::wstring &fileName, FileAction fileAction)>;

#endif // DIRECTORYWATCHERHELPER_H
