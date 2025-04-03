#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->chooseFileButton, &QAbstractButton::clicked, this, &MainWindow::chooseFileButtonClicked);
    connect(ui->loadDataButton, &QAbstractButton::clicked, this, &MainWindow::loadCsvButtonClicked);

    doOperation(Initialization, &context, NULL);
    updateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUi() {
    ui->dataTableWidget->setHorizontalHeaderLabels(context.data->columnNames);
    for(int row = 0;current!=NULL;row++,current = current->next)
        while (current != NULL) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(current->year)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromUtf8(current->region)));
            for (int i = 0; i < context.columnCount-2; i++) {
                ui->tableWidget->setItem(row, i+2, new QTableWidgetItem(QString::number(current->metrics[i])));
            }
            current = current->next;
            row++;
        }
}

void MainWindow::chooseFileButtonClicked()
{
    AppParams params;

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open CSV"), "/", tr("CSV File (*.csv)"));
    QByteArray array = fileName.toLocal8Bit();
    strncpy(params.filePath, array.data(), array.size());

    doOperation(SetPath, &context, &params);
}

void MainWindow::loadCsvButtonClicked()
{
    doOperation(LoadCSV, &context, NULL);
}
