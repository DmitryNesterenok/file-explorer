#include "worker.h"

#include "filesmodel.h"

#include <QDir>

Worker::Worker(QObject *parent)
    : QObject(parent), m_filesModel(new FilesModel(this)), m_directoryWatcher(new DirectoryWatcher)
{
    m_directoryWatcher->setCallBack([this](const std::wstring &fileName, FileAction fileAction) {
        QString name = QString::fromStdWString(fileName);
        switch (fileAction) {
        case FileAction::FileAdded:
            m_filesModel->addFileInfo(QFileInfo(m_currentDir, name));
            break;
        case FileAction::FileRemoved:
            m_filesModel->removeFileInfo(name);
            break;
        case FileAction::FileModified:
            m_filesModel->updateFileInfo(name);
            break;
        default:
            break;
        }
    });
    connect(this, &Worker::currentPathChanged, this, [this](const QString &currentPath) {
        const QFileInfoList list = m_currentDir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
        m_filesModel->setFileInfoList(list);
        m_directoryWatcher->setPath(currentPath.toStdWString());
    });

    enterToDirectory(QDir::homePath());
}

void Worker::enterToDirectory(const QString &dirName)
{
    if (m_currentDir.cd(dirName))
        emit currentPathChanged(currentPath());
}

void Worker::upDirectory()
{
    if (m_currentDir.cdUp())
        emit currentPathChanged(currentPath());
}

void Worker::rename(const QString &oldName, const QString &newName)
{
    m_currentDir.rename(oldName, newName);
}

FilesModel *Worker::filesModel() const
{
    return m_filesModel;
}

QString Worker::currentPath() const
{
    return m_currentDir.absolutePath();
}
