#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entrypoint.h"
#include "appcontext.h"
#include <QClipboard>

#define STR_LEN 32

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->fromDecRadioButton, &QAbstractButton::toggled, this, &MainWindow::on_fromDecRadioButton_clicked);
    connect(ui->fromBinRadioButton, &QAbstractButton::toggled, this, &MainWindow::on_fromBinRadioButton_clicked);
    connect(ui->fromOctRadioButton, &QAbstractButton::toggled, this, &MainWindow::on_fromOctRadioButton_clicked);
    connect(ui->toDecRadioButton, &QAbstractButton::toggled, this, &MainWindow::on_toDecRadioButton_clicked);
    connect(ui->toBinRadioButton, &QAbstractButton::toggled, this, &MainWindow::on_toBinRadioButton_clicked);
    connect(ui->toOctRadioButton, &QAbstractButton::toggled, this, &MainWindow::on_toOctRadioButton_clicked);
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::on_convertButton_clicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::on_copyButton_clicked);
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::on_swapButton_clicked);

    doOperation(Initialization, &context, NULL);
    updateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUi() {
    updateRadioButtons();

    ui->inputLineEdit->setText(QString::fromUtf8(context.input));
    ui->outputLineEdit->setText(QString::fromUtf8(context.output));
}

void MainWindow::on_fromDecRadioButton_clicked()
{
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    params->newFromBase = DEC;
    params->newToBase = context.toBase;

    doOperation(UpdateBases, &context, params);

    free(params);
}

void MainWindow::on_fromBinRadioButton_clicked()
{
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    params->newFromBase = BIN;
    params->newToBase = context.toBase;

    doOperation(UpdateBases, &context, params);

    free(params);
}

void MainWindow::on_fromOctRadioButton_clicked()
{
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    params->newFromBase = OCT;
    params->newToBase = context.toBase;

    doOperation(UpdateBases, &context, params);

    free(params);
}

void MainWindow::on_toDecRadioButton_clicked()
{
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    params->newFromBase = context.fromBase;
    params->newToBase = DEC;

    doOperation(UpdateBases, &context, params);

    free(params);
}

void MainWindow::on_toBinRadioButton_clicked()
{
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    params->newFromBase = context.fromBase;
    params->newToBase = BIN;

    doOperation(UpdateBases, &context, params);

    free(params);
}

void MainWindow::on_toOctRadioButton_clicked()
{
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    params->newFromBase = context.fromBase;
    params->newToBase = OCT;

    doOperation(UpdateBases, &context, params);

    free(params);
}

void MainWindow::on_convertButton_clicked() {
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    QByteArray array = ui->inputLineEdit->text().toLocal8Bit();
    strncpy(params->input, array.data(), array.size());

    doOperation(Convert, &context, params);

    free(params);

    handleErrorCode();

    updateUi();
}

void MainWindow::on_copyButton_clicked()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(context.output);
}

void MainWindow::on_swapButton_clicked() {
    AppParams* params = (AppParams*) malloc(sizeof(AppParams));
    QByteArray inputArray = ui->inputLineEdit->text().toLocal8Bit();
    strncpy(params->input, inputArray.data(), STR_LEN + 1);
    QByteArray outputArray = ui->outputLineEdit->text().toLocal8Bit();
    strncpy(params->output, outputArray.data(), STR_LEN + 1);

    doOperation(Swap, &context, params);

    free(params);

    updateUi();
}

void MainWindow::updateRadioButtons() {
    switch (context.fromBase) {
    case DEC:
        ui->fromDecRadioButton->click();
        break;
    case BIN:
        ui->fromBinRadioButton->click();
        break;
    case OCT:
        ui->fromOctRadioButton->click();
        break;
    }

    switch (context.toBase) {
    case DEC:
        ui->toDecRadioButton->click();
        break;
    case BIN:
        ui->toBinRadioButton->click();
        break;
    case OCT:
        ui->toOctRadioButton->click();
        break;
    }
}

void MainWindow::handleErrorCode() {
    if (context.errorCode == OK) {
        ui->outputLineEdit->setText(QString::fromUtf8(context.output));
        ui->statusLabel->setText("");
    }
    else if (context.errorCode == INVALID_INPUT)
        ui->statusLabel->setText("Invalid input!");
    else if (context.errorCode == INTEGER_OVERFLOW)
        ui->statusLabel->setText("Value larger than int!");
    else
        ui->statusLabel->setText("Error while converting!");
}
