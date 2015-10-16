#include "userlistmodel.h"

UserListModel::UserListModel() : QAbstractItemModel(0)
{

}

UserListModel::~UserListModel()
{

}
void UserListModel::append(const User &user){

    beginInsertRows(QModelIndex(), userList.size(), userList.size());
    userList.append(user);
    endInsertRows();
}
QDataStream& operator<<(QDataStream& out, const UserListModel& ulm) {return out << ulm.userList;}
QDataStream& operator>>(QDataStream& in, UserListModel& ulm) {return in >> ulm.userList;}

//***************************************************************************************************************************************
QModelIndex UserListModel::index(int row, int column, const QModelIndex &parent) const
{
    if( parent.isValid() ||
            column > COLUMN_COUNT || column < 0 ||
            row >= userList.size() || row < 0) return QModelIndex();
    return createIndex(row, column);
}

QHash<int, QByteArray>  UserListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>( UserListModel::ColumnNames::Name)] = QObject::tr("User Name").toUtf8();
    return roles;
}

int UserListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return userList.size();
}

int UserListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return COLUMN_COUNT;
}

QVariant UserListModel::data(const QModelIndex &index, int role) const {
    Q_UNUSED(role)
    if((index.column() < 0 ||
            columnCount() <= index.column() ||
            index.row() < 0 ||
            rowCount() <= index.row()))
    {
        qDebug() << "Warning: " << index.row() << ", " << index.column();
        return QVariant();
    }
//    switch(role){
//    case Qt::DisplayRole :
        return userList.at(index.row()).getUserName();
//    }
}

QModelIndex UserListModel::parent(const QModelIndex &child) const {
   Q_UNUSED(child)
    return QModelIndex();
}
