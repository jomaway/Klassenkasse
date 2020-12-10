#include "mainwindow.h"

#include <QGroupBox>
#include <QStatusBar>
#include <QHeaderView>
#include <QMenu>
#include <QCloseEvent>
#include <QMenuBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createCentralLayout();
    createActions();
    createStatusBar();

    createModel();

    // connect signals and slots
    connect(btnAddStudent, SIGNAL(clicked()),this, SLOT(on_btnAddStudent_clicked()));
    connect(btnBuy, SIGNAL(clicked()), this, SLOT(on_btnBuy_clicked()));
    connect(btnDeposit, &QPushButton::clicked, this, &MainWindow::on_btn_Deposit_clicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //save before Exit
    event->accept();
}

void MainWindow::newFile()
{
    qDebug() << "newFile Action triggered";
}

void MainWindow::open()
{
    qDebug() << "open Action triggered";
}

void MainWindow::save()
{
    qDebug() << "save Action triggered";
}

void MainWindow::listWasModified()
{
    qDebug() << "listWasModified()";
}

void MainWindow::on_btnAddStudent_clicked()
{
    qDebug() << "on_btnAddStudent_clicked()";
    auto name = lEditStudentName->text().trimmed();
    if (!name.isEmpty()) {
        personModel->addPerson(name);
        lEditStudentName->clear();
    }
}

void MainWindow::on_btnBuy_clicked()
{
    qDebug() << "on_btnBuy_clicked()";
    // Get current user from comboBox
    auto personIndex = cBoxStudent->currentIndex();
    personModel->drinkCoffee(personIndex);

}

void MainWindow::on_btn_Deposit_clicked()
{
    qDebug() << "on_btnDeposit_clicked()";
    auto personIndex = cBoxStudent->currentIndex();
    auto amount = leditDeposit->text().toDouble();
    personModel->deposit(personIndex, amount);
}

void MainWindow::createCentralLayout()
{
    // Create Table View
    this->view = new QTableView();
    this->view->verticalHeader()->hide();
    this->view->setTabKeyNavigation(false);
    this->view->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Create Widgets for Add Group
    this->btnAddStudent = new QPushButton(tr("Add Student"));
    btnAddStudent->setAutoDefault(true);

    this->lEditStudentName = new QLineEdit();
    lEditStudentName->setPlaceholderText(tr("name"));

    cBoxStudent = new QComboBox();
    btnBuy = new QPushButton(tr("Buy Coffee"));
    btnDeposit = new QPushButton(tr("Deposit"));
    leditDeposit = new QLineEdit();
    leditDeposit->setPlaceholderText("Set Amount you want to deposit here");
    leditDeposit->setValidator( new QDoubleValidator(0, 100, 2, this) );

    auto gridPayOption = new QGridLayout();
    gridPayOption->addWidget(cBoxStudent,0,0,1,2);
    gridPayOption->addWidget(btnBuy,1,0,1,2);
    gridPayOption->addWidget(leditDeposit,2,0);
    gridPayOption->addWidget(btnDeposit,2,1);
    gridPayOption->setAlignment(Qt::AlignTop);
    gridPayOption->setSpacing(10);

    auto gBoxPayOption = new QGroupBox(tr("Payment Options"));
    gBoxPayOption->setLayout(gridPayOption);

    // Create Layouts
    auto vBoxAdd = new QVBoxLayout();
    vBoxAdd->addWidget(lEditStudentName);
    vBoxAdd->addWidget(btnAddStudent);
    vBoxAdd->setAlignment(Qt::AlignTop);
    vBoxAdd->setSpacing(20);
    //vBoxAdd->addSpacerItem(new QSpacerItem(1,30,QSizePolicy::Expanding, QSizePolicy::Expanding));

    auto gBoxAdd = new QGroupBox(tr("Add Student"));
    gBoxAdd->setLayout(vBoxAdd);

    // Horizontal Box
    auto hBox = new QHBoxLayout();
    hBox->addWidget(view);
    hBox->addWidget(gBoxPayOption);
    hBox->addWidget(gBoxAdd);

    // Create central widget
    auto cWidget = new QWidget();
    cWidget->setLayout(hBox);
    this->setCentralWidget(cWidget);
}

void MainWindow::createActions()
{
    // Create the FileMenu
    QMenu *fileMenu = this->menuBar()->addMenu(tr("&File"));
    // Create newFile Action
    auto newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new list"));
    fileMenu->addAction(newAction);
    // Create open Action
    auto openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a list"));
    fileMenu->addAction(openAction);
    // Create save Action
    auto saveAction = new QAction(tr("&Save"), this);
    fileMenu->addAction(saveAction);
}

void MainWindow::createStatusBar()
{
    // Create the StatusBar
    this->statusBar()->showMessage(tr("Ready"));

}

void MainWindow::createModel()
{
    this->personModel = new PersonTableModel();
    this->view->setModel(personModel);
    cBoxStudent->setModel(personModel);
}

