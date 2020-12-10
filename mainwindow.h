#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <persontablemodel.h>
#include <QComboBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void open();
    void save();
    void listWasModified();
    void on_btnAddStudent_clicked();
    void on_btnBuy_clicked();
    void on_btn_Deposit_clicked();

private:
    void createCentralLayout();
    void createActions();
    void createStatusBar();
    void createModel();
    QTableView *view;
    QPushButton *btnAddStudent;
    QLineEdit *lEditStudentName;

    QComboBox *cBoxStudent;
    QPushButton *btnBuy;
    QPushButton *btnDeposit;
    QLineEdit *leditDeposit;

    PersonTableModel *personModel;
};
#endif // MAINWINDOW_H
