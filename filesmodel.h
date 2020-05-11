#ifndef FILESMODEL_H
#define FILESMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include <QFileInfo>

class FilesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FilesModel(QObject *parent = nullptr);

    enum Roles
    {
        Name = Qt::UserRole,
        ModifiedDate,
        Size,
        IsDir
    };

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QString nameAt(int index) const;

    QFileInfoList fileInfoList() const;
    Q_INVOKABLE void setFileInfoList(const QFileInfoList &fileInfoList);
    Q_INVOKABLE void addFileInfo(const QFileInfo &fileInfo);
    Q_INVOKABLE void removeFileInfo(const QString &fileName);
    Q_INVOKABLE void updateFileInfo(const QString &fileName);

private:
    QHash<int, QByteArray> m_roleNames;
    QFileInfoList m_fileInfoList;
};

#endif // FILESMODEL_H
