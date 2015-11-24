#include "userlistmodel.h"
#include <QMapIterator>

UserListModel::UserListModel() : QAbstractItemModel(0)
{

}

UserListModel::~UserListModel()
{

}

User UserListModel::getLastActiveUser(){
    if(!lastActiveUser.isEmpty()){
        QString systemUserName = qgetenv("USER");
        if (systemUserName.isEmpty()){
            systemUserName = qgetenv("USERNAME");
        }
        if(lastActiveUser.contains(systemUserName)){
          return findUser(lastActiveUser.value(systemUserName));
        }
    }
    return User();
}
User UserListModel::findUser(int ID){
QMapIterator<QString, int> iter(lastActiveUser);
while(iter.hasNext()){
    iter.next();
qDebug() << iter.key() << " " << iter.value();
}
    for(int i = 0; i < userList.size(); ++i){
        if(userList.at(i).getId() == ID) {
            return userList.at(i);
        }
    }
    return User();
}

void UserListModel::setLastActiveUser(int ID){
    QString systemUserName = qgetenv("USER");
    if (systemUserName.isEmpty()){
        systemUserName = qgetenv("USERNAME");
    }
    lastActiveUser[systemUserName] = ID;
}

void UserListModel::append(const User &user){

    beginInsertRows(QModelIndex(), userList.size(), userList.size());
    userList.append(user);
    endInsertRows();
}

QDataStream& operator<<(QDataStream& out, const UserListModel& ulm) {
    return out << ulm.userList
               << ulm.lastActiveUser;
}

QDataStream& operator>>(QDataStream& in, UserListModel& ulm) {
    return in >> ulm.userList
              >> ulm.lastActiveUser;
}

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
    //Q_UNUSED(role)
    if((index.column() < 0 ||
        columnCount() <= index.column() ||
        index.row() < 0 ||
        rowCount() <= index.row()))
    {
        qDebug() << "Warning: " << index.row() << ", " << index.column();
        return QVariant();
    }
    switch(role){
    case Qt::DisplayRole :
        return *(userList.at(index.row()).getUserName());
    }
    return QVariant();
}

QModelIndex UserListModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child)
    return QModelIndex();
}
