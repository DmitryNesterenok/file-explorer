#include "filesmodel.h"

#include <QThread>

FilesModel::FilesModel(QObject *parent) : QAbstractListModel(parent)
{
    m_roleNames[Roles::Name] = "name";
    m_roleNames[Roles::ModifiedDate] = "modifiedDate";
    m_roleNames[Roles::Size] = "size";
    m_roleNames[Roles::IsDir] = "isDir";
}

int FilesModel::rowCount(const QModelIndex &) const
{
    return m_fileInfoList.count();
}

QVariant FilesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.column() != 0 || index.row() < 0 || index.row() >= m_fileInfoList.size())
        return QVariant();

    switch (role) {
    case Roles::Name:
        return m_fileInfoList[index.row()].fileName();
    case Roles::ModifiedDate:
        return m_fileInfoList[index.row()].lastModified().toString("dd.MM.yyyy hh:mm:ss");
    case Roles::Size:
        return m_fileInfoList[index.row()].size();
    case Roles::IsDir:
        return m_fileInfoList[index.row()].isDir();
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> FilesModel::roleNames() const
{
    return m_roleNames;
}

QString FilesModel::nameAt(int index) const
{
    return m_fileInfoList.count() > index ? m_fileInfoList.at(index).fileName() : QString();
}

QFileInfoList FilesModel::fileInfoList() const
{
    return m_fileInfoList;
}

void FilesModel::setFileInfoList(const QFileInfoList &fileInfoList)
{
    if (thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, __func__, Qt::QueuedConnection, Q_ARG(QFileInfoList, fileInfoList));
        return;
    }

    beginResetModel();
    m_fileInfoList = fileInfoList;
    endResetModel();
}

void FilesModel::addFileInfo(const QFileInfo &fileInfo)
{
    if (thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, __func__, Qt::QueuedConnection, Q_ARG(QFileInfo, fileInfo));
        return;
    }

    beginInsertRows(QModelIndex(), m_fileInfoList.count(), m_fileInfoList.count());
    m_fileInfoList.append(fileInfo);
    endInsertRows();
}

void FilesModel::removeFileInfo(const QString &fileName)
{
    if (thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, __func__, Qt::QueuedConnection, Q_ARG(QString, fileName));
        return;
    }

    for (int i = 0; i < m_fileInfoList.count(); ++i) {
        if (m_fileInfoList.at(i).fileName() == fileName) {
            beginRemoveRows(QModelIndex(), i, i);
            m_fileInfoList.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}

void FilesModel::updateFileInfo(const QString &fileName)
{
    if (thread() != QThread::currentThread()) {
        QMetaObject::invokeMethod(this, __func__, Qt::QueuedConnection, Q_ARG(QString, fileName));
        return;
    }

    for (int i = 0; i < m_fileInfoList.count(); ++i) {
        if (m_fileInfoList.at(i).fileName() == fileName) {
            m_fileInfoList[i].refresh();
            emit dataChanged(index(i, 0, QModelIndex()), index(i, 0, QModelIndex()));
            break;
        }
    }
}
