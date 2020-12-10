#ifndef PERSONS_H
#define PERSONS_H

#include <QAbstractTableModel>
#include <QList>
#include <QVector>



enum ModelColumn {
    Name = 0,
    Balance = 1,
};


struct Person {
    QString name;
    double balance;
};

class PersonTableModel : public QAbstractTableModel
{
    Q_OBJECT


public:
    explicit PersonTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void addPerson(QString name);
    void drinkCoffee(int pIndex);
    void deposit(int pIndex, double amount);

private:
    const int COLUMNS = 2;
    QList<Person> personList;



};

#endif // PERSONS_H
