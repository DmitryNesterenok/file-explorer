#include "directorywatcher_win_p.h"

#include <conio.h>
#include <iostream>
#include <windows.h>

#define MAX_BUFFER 4096

typedef struct _DIRECTORY_INFO
{
    HANDLE hDir = nullptr;
    CHAR lpBuffer[MAX_BUFFER];
    DWORD dwBufLength;
    OVERLAPPED Overlapped;
} DIRECTORY_INFO, *PDIRECTORY_INFO, *LPDIRECTORY_INFO;

DIRECTORY_INFO DirInfo;
HANDLE hCompPort = nullptr; // Handle To a Completion Port
HANDLE hThread = nullptr;
Callback callback;

void WINAPI HandleDirectoryChange(PVOID dwCompletionPort)
{
    DWORD numBytes;
    DWORD cbOffset;
    LPDIRECTORY_INFO di;
    LPOVERLAPPED lpOverlapped;
    PFILE_NOTIFY_INFORMATION fni;

    do {
        // Retrieve the directory info for this directory
        // through the completion key
        GetQueuedCompletionStatus((HANDLE)dwCompletionPort, &numBytes, (PULONG_PTR)&di, &lpOverlapped, INFINITE);

        if (di) {
            fni = (PFILE_NOTIFY_INFORMATION)di->lpBuffer;

            do {
                FileAction fileAction = FileAction::Unknown;
                switch (fni->Action) {
                case FILE_ACTION_ADDED:
                case FILE_ACTION_RENAMED_NEW_NAME:
                    fileAction = FileAction::FileAdded;
                    break;
                case FILE_ACTION_REMOVED:
                case FILE_ACTION_RENAMED_OLD_NAME:
                    fileAction = FileAction::FileRemoved;
                    break;
                case FILE_ACTION_MODIFIED:
                    fileAction = FileAction::FileModified;
                    break;
                default:
                    break;
                }

                callback(std::wstring(fni->FileName, fni->FileNameLength / 2), fileAction);

                cbOffset = fni->NextEntryOffset;
                fni = (PFILE_NOTIFY_INFORMATION)((LPBYTE)fni + cbOffset);
            } while (cbOffset);

            // Reissue the watch command
            ReadDirectoryChangesW(di->hDir, di->lpBuffer, MAX_BUFFER, false,
                                  FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE,
                                  &di->dwBufLength, &di->Overlapped, nullptr);
        }
    } while (di);
}

WindowsDirectoryWatcherPrivate::WindowsDirectoryWatcherPrivate() : DirectoryWatcherPrivate()
{}

bool WindowsDirectoryWatcherPrivate::setPath(const std::wstring directory)
{
    clearPath();

    TCHAR *dir = (TCHAR *)directory.c_str();
    // Get a handle to the directory
    DirInfo.hDir = CreateFile(dir, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
                              FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

    if (DirInfo.hDir == INVALID_HANDLE_VALUE)
        return false;

    // Set up a key(directory info)
    hCompPort = CreateIoCompletionPort(DirInfo.hDir, hCompPort, (ULONG_PTR)&DirInfo, 0);
    if (hCompPort == INVALID_HANDLE_VALUE)
        return false;

    // Start watching each of the directories of interest
    ReadDirectoryChangesW(DirInfo.hDir, DirInfo.lpBuffer, MAX_BUFFER, false,
                          FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE,
                          &DirInfo.dwBufLength, &DirInfo.Overlapped, nullptr);

    // Create a thread to sit on the directory changes
    hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&HandleDirectoryChange, hCompPort, 0, 0);
    return hThread != INVALID_HANDLE_VALUE;
}

void WindowsDirectoryWatcherPrivate::clearPath()
{
    // Wait for the Directory thread to finish before exiting
    if (hCompPort)
        PostQueuedCompletionStatus(hCompPort, 0, 0, nullptr);
    if (hThread) {
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
        hThread = nullptr;
    }
    if (DirInfo.hDir) {
        CloseHandle(DirInfo.hDir);
        DirInfo.hDir = nullptr;
    }
    if (hCompPort) {
        CloseHandle(hCompPort);
        hCompPort = nullptr;
    }
}

void WindowsDirectoryWatcherPrivate::setCallBack(const Callback &_callback)
{
    callback = _callback;
}
