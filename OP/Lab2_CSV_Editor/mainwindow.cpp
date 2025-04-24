#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <stdlib.h>
#include <math.h>
#include "entrypoint.h"
#include "appcontext.h"
#include "plotwidget.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dataTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->chooseFileButton, &QAbstractButton::clicked, this, &MainWindow::chooseFileButtonClicked);
    connect(ui->loadDataButton, &QAbstractButton::clicked, this, &MainWindow::loadCsvButtonClicked);
    connect(ui->filterRegionButton, &QAbstractButton::clicked, this, &MainWindow::filterRegionButtonClicked);
    connect(ui->calcMetricsButton, &QAbstractButton::clicked, this, &MainWindow::calcMetricsButtonClicked);

    doOperation(Initialization, &context, NULL);
    updateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUi() {
    QString filterName = ui->regionLineEdit->text();
    if (context.data->columnCount > 0)
        ui->selectColumnSpinBox->setMaximum(context.data->columnCount);
    else
        ui->selectColumnSpinBox->setMaximum(1);

    if (context.data->rowCount > 0) {
        updateTableWidget(filterName);
        updateTableInfo(filterName);
    }
}

void MainWindow::updateTableWidget(const QString& filterName) {
    ui->dataTableWidget->clearContents();
    ui->dataTableWidget->setRowCount(0);

    QStringList colNames = convToQStringList();
    ui->dataTableWidget->setColumnCount(colNames.size());
    ui->dataTableWidget->setHorizontalHeaderLabels(colNames);
    RowNode* cur = context.data->head;
    int row = 0;
    while (cur != NULL) {
        if (filterName == "" || cur->data[REGION_COL] == filterName) {
            ui->dataTableWidget->insertRow(row);
            for (int i = 0; i < context.data->columnCount; i++) {
                char* endptr = NULL;
                errno = 0;
                double d = strtod(cur->data[i], &endptr);
                if (errno == 0 && endptr != cur->data[i]) {
                    QString value = QString::number(d);
                    if (d - ((long) d) == 0)
                        value = QString::number((long) d);
                    ui->dataTableWidget->setItem(row, i, new QTableWidgetItem(value));
                }
                else
                    ui->dataTableWidget->setItem(row, i, new QTableWidgetItem(QString(cur->data[i])));
            }
            row++;
        }
        cur = cur->next;
    }
}

void MainWindow::updateTableInfo(const QString& filterName) {
    QString text;
    if (filterName == "") {
        text = "Valid rows: ";
        text.append(QString::number(context.data->rowCount));
        text.append(", errors: ");
        text.append(QString::number(context.data->errEntryCount));
        text.append(", total: ");
        text.append(QString::number(context.data->rowCount + context.data->errEntryCount));
    }
    else {
        text = "Filtered rows: ";
        text.append(QString::number(ui->dataTableWidget->rowCount()));
    }

    ui->tableInfoLabel->setText(text);
}

void MainWindow::chooseFileButtonClicked()
{
    AppParams params;

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open CSV"), "/", tr("CSV File (*.csv)"));
    QByteArray array = fileName.toLocal8Bit();
    strncpy(params.filePath, array.data(), array.size());

    doOperation(SetPath, &context, &params);

    handleErrorCode();
}

void MainWindow::loadCsvButtonClicked()
{
    doOperation(LoadCSV, &context, NULL);

    if (context.errorCode == OK)
        updateUi();
    else
        handleErrorCode();
}

void MainWindow::filterRegionButtonClicked() {
    AppParams params;

    QByteArray array = ui->regionLineEdit->text().toLocal8Bit();
    strncpy(params.filterName, array.data(), array.size());
    params.filterName[array.size()] = '\0';

    updateUi();

    params.filteredRowsCount = ui->dataTableWidget->rowCount();

    doOperation(FilterCSV, &context, &params);
}

void MainWindow::calcMetricsButtonClicked() {
    AppParams params;

    params.selectedColumn = ui->selectColumnSpinBox->value();

    doOperation(CalculateMetrics, &context, &params);

    if (context.errorCode == OK) {
        ui->minValueOutputLine->setText(QString::number(context.metrics->minValue));
        ui->maxValueOutputLine->setText(QString::number(context.metrics->maxValue));
        ui->medianValueOutputLine->setText(QString::number(context.metrics->medianValue));
    }
    else
        handleErrorCode();

    if (strncmp(context.filterName, "", strlen(context.filterName))) {
        PlotWidget* plot = new PlotWidget();
        plot->setContext(&context);
        plot->show();
    }
}

QStringList MainWindow::convToQStringList() {
    QList<QString> lst;
    for (int i = 0; i < context.data->columnCount; i++)
        lst.append(QString(context.data->columnNames[i]));

    return lst;
}

void MainWindow::showMessageBox(QString info) {
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setText("Error");
    msgBox->setInformativeText(info);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->exec();
}

void MainWindow::handleErrorCode() {
    if (context.errorCode != OK)
        showMessageBox(getErrorInfo(context.errorCode));
}

QString MainWindow::getErrorInfo(const ErrorCode err) {
    QString info;

    switch (err) {
    case OK:
        info = "OK";
        break;
    case BAD_FILENAME:
        info = "Empty filename or wrong extension!";
        break;
    case FILE_NOT_OPENED:
        info = "Couldn't open the file!";
        break;
    case INVALID_INPUT:
        info = "Invalid input!";
        break;
    case CALC_ERROR:
        info = "Couldn't calculate metrics!";
        break;
    case EMPTY_FILE:
        info = "File is empty!";
        break;
    case NO_COLUMNS:
        info = "Incorrect format or no columns!";
        break;
    case BAD_COLUMN:
        info = "Invalid column number for calculating!";
        break;
    case BAD_METRICS_VALUE:
        info = "Value error (possibly not a number)!";
        break;
    default:
        info = "Unexpected error!";
        break;
    }

    return info;
}
