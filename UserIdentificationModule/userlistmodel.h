#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H
#include <QAbstractItemModel>
#include <QDataStream>
#include <QVariant>
#include <QDebug>

#include "user.h"

class UserListModel : public QAbstractItemModel
{
private:
    QList<User> userList;
    const int COLUMN_COUNT = 1;
    enum class ColumnNames{
        Name
    };
public:
    UserListModel();
    ~UserListModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex parent(const QModelIndex &child) const;

    const User& at(int i) const { return userList.at(i); }
    void removeAt(int i){ userList.removeAt(i);}
    int size() const { return userList.size(); }
    inline bool isEmpty() const { return userList.isEmpty(); }
    void append(const User &user);
    const User& last() const { Q_ASSERT(!isEmpty()); return userList.at(userList.size() - 1); }
    //const User &operator[](int i) const;
    User& operator[](int i) {return userList[i];}
    friend QDataStream& operator<<(QDataStream& out, const UserListModel& ulm);
    friend QDataStream& operator>>(QDataStream& in, UserListModel& ulm);
};

#endif // USERLISTMODEL_H
