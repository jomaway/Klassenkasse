#include "persontablemodel.h"

#include <QBrush>
#include <QDebug>

PersonTableModel::PersonTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    personList.append({"pete", 1.99});
    personList.append({"anton", 14.50});
    personList.append({"claudi", -0.5});
}

QVariant PersonTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case ModelColumn::Name:
            return QString("Name");
        case ModelColumn::Balance:
            return QString("Balance");
        default:
            return QVariant();
        }
    } else {
        return QVariant();
    }

}


int PersonTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->personList.count();
}

int PersonTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->COLUMNS;
}

QVariant PersonTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return this->personList.at(index.row()).name;
        case 1:
            return this->personList.at(index.row()).balance;
        }
    }

    if (role == Qt::TextColorRole && index.column() == 1) {
        if (personList[index.row()].balance < 0) { return QBrush(Qt::red); }
    }
    return QVariant();
}

bool PersonTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (index.column() == 1) {
            personList[index.row()].balance = value.toDouble();
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PersonTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column() == 1){
        return  QAbstractTableModel::flags(index) |  Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}




void PersonTableModel::addPerson(QString name)
{
    qDebug() << "M: addPerson(" << name << ")";
    beginInsertRows(QModelIndex(), 0, 0);
    personList.append({name, 0});
    endInsertRows();
}


void PersonTableModel::drinkCoffee(int pIndex)
{
    auto &person = personList[pIndex];
    person.balance -= 0.5;
    qDebug() << person.name << "drinks Coffee. New Balance (" << person.balance << ")";

    emit dataChanged(index(pIndex,1),index(pIndex,1));
}

void PersonTableModel::deposit(int pIndex, double amount)
{
    auto &person = personList[pIndex];
    person.balance += amount;
    qDebug() << person.name << "deposited " << amount << "€. New Balance (" << person.balance << ")";
    emit dataChanged(index(pIndex,2),index(pIndex,2));
}

