#ifndef WORKER_H
#define WORKER_H

#include "directorywatcher/directorywatcher.h"

#include <QDir>
#include <QObject>

#include <memory>

class FilesModel;

class Worker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(FilesModel *filesModel READ filesModel CONSTANT)
    Q_PROPERTY(QString currentPath READ currentPath NOTIFY currentPathChanged)
public:
    explicit Worker(QObject *parent = 0);

    Q_INVOKABLE void enterToDirectory(const QString &dirName);
    Q_INVOKABLE void upDirectory();
    Q_INVOKABLE void rename(const QString &oldName, const QString &newName);

    FilesModel *filesModel() const;
    QString currentPath() const;

signals:
    void currentPathChanged(const QString &currentPath);

private:
    FilesModel *m_filesModel = nullptr;
    std::unique_ptr<DirectoryWatcher> m_directoryWatcher;
    QDir m_currentDir;
};

#endif // WORKER_H
