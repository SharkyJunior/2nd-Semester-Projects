#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entrypoint.h"
#include "appcontext.h"
#include "constants.h"
#include <QClipboard>


QString getDescByErr(const ErrorCode* err);

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
    AppParams params;
    params.newFromBase = DEC;
    params.newToBase = context.toBase;

    doOperation(UpdateBases, &context, &params);
}

void MainWindow::on_fromBinRadioButton_clicked()
{
    AppParams params;
    params.newFromBase = BIN;
    params.newToBase = context.toBase;

    doOperation(UpdateBases, &context, &params);
}

void MainWindow::on_fromOctRadioButton_clicked()
{
    AppParams params;
    params.newFromBase = OCT;
    params.newToBase = context.toBase;

    doOperation(UpdateBases, &context, &params);
}

void MainWindow::on_toDecRadioButton_clicked()
{
    AppParams params;
    params.newFromBase = context.fromBase;
    params.newToBase = DEC;

    doOperation(UpdateBases, &context, &params);
}

void MainWindow::on_toBinRadioButton_clicked()
{
    AppParams params;
    params.newFromBase = context.fromBase;
    params.newToBase = BIN;

    doOperation(UpdateBases, &context, &params);
}

void MainWindow::on_toOctRadioButton_clicked()
{
    AppParams params;
    params.newFromBase = context.fromBase;
    params.newToBase = OCT;

    doOperation(UpdateBases, &context, &params);
}

void MainWindow::on_convertButton_clicked() {
    AppParams params;
    QByteArray array = ui->inputLineEdit->text().toLocal8Bit();
    strncpy(params.input, array.data(), array.size());

    doOperation(Convert, &context, &params);

    ui->outputLineEdit->setText(QString::fromUtf8(context.output));
    handleErrorCode();

    updateUi();
}

void MainWindow::on_copyButton_clicked()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(context.output);
}

void MainWindow::on_swapButton_clicked() {
    AppParams params;
    QByteArray inputArray = ui->inputLineEdit->text().toLocal8Bit();
    strncpy(params.input, inputArray.data(), STR_LEN + 1);
    QByteArray outputArray = ui->outputLineEdit->text().toLocal8Bit();
    strncpy(params.output, outputArray.data(), STR_LEN + 1);

    doOperation(Swap, &context, &params);

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
    QString msg = getDescByErr(&context.errorCode);
    ui->statusLabel->setText(msg);
}

QString getDescByErr(const ErrorCode* err) {
    QString desc;
    if (*err == OK)
        desc = QString::fromUtf8("");
    else if (*err == INVALID_INPUT)
        desc = QString::fromUtf8("Invalid input!");
    else if (*err == INTEGER_OVERFLOW)
        desc = QString::fromUtf8("Value larger than int!");
    else
        desc = QString::fromUtf8("Error while converting!");

    return desc;
}
