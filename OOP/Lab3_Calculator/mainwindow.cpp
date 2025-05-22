#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 10; ++i)
        connect(findChild<QPushButton*>(QString("button%1").arg(i)),
                &QPushButton::clicked, this, &MainWindow::onNumberClicked);

    QStringList operators {"plus", "minus", "multiply", "divide"};
    for (const QString& op : operators)
        connect(findChild<QPushButton*>(QString("%1Button").arg(op)),
                &QPushButton::clicked, this, &MainWindow::onOperatorClicked);

    connect(ui->ACButton, &QPushButton::clicked, this, &MainWindow::onACClicked);
    connect(ui->delButton, &QPushButton::clicked, this, &MainWindow::onDelClicked);
    connect(ui->openBracketButton, &QPushButton::clicked, this, &MainWindow::onOpenBracketClicked);
    connect(ui->closeBracketButton, &QPushButton::clicked, this, &MainWindow::onClosedBracketClicked);
    connect(ui->pointButton, &QPushButton::clicked, this, &MainWindow::onPeriodClicked);
    connect(ui->resultButton, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);

    connect(ui->memClearButton, &QPushButton::clicked, this, &MainWindow::onMemClearClicked);
    connect(ui->memReadButton, &QPushButton::clicked, this, &MainWindow::onMemReadClicked);
    connect(ui->memPlusButton, &QPushButton::clicked, this, &MainWindow::onMemPlusClicked);
    connect(ui->memMinusButton, &QPushButton::clicked, this, &MainWindow::onMemMinusClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNumberClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    ui->formulaLabel->setText(ui->formulaLabel->toPlainText() + button->text());
    equalClicked = false;
    updateCursor();
}

void MainWindow::onOperatorClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString text = ui->formulaLabel->toPlainText();
    if ((!text.isEmpty() && !operators.contains(text[text.size()-1]))
        || (text.isEmpty() && button->text() == "-")) {
        if (text.isEmpty() && text[text.size()-1] == '.')
            text += "0";
        ui->formulaLabel->setText(text + button->text());
        equalClicked = false;
    }
    updateCursor();
}

void MainWindow::onACClicked() {
    ui->formulaLabel->setText("");
    equalClicked = false;
    updateCursor();
}

void MainWindow::onDelClicked() {
    if (equalClicked)
        ui->formulaLabel->setText("");
    else {
        QString text = ui->formulaLabel->toPlainText();
        if (!text.isEmpty()) {
            if (text.endsWith("(")) --openBracketCount;
            else if (text.endsWith(")")) ++openBracketCount;
            text.chop(1);
            ui->formulaLabel->setText(text);
        }
    }
    updateCursor();
}

void MainWindow::onOpenBracketClicked() {
    QString text = ui->formulaLabel->toPlainText();
    for (int i = 0; i < 10; ++i) {
        if (text.endsWith(".")) {
            ui->formulaLabel->setText(text +"0*(");
            break;
        }
        else if (text.endsWith(QString::number(i)) || text.endsWith(")")){
            ui->formulaLabel->setText(text +"*(");
            break;
        }
    }
    if (text == ui->formulaLabel->toPlainText())
        ui->formulaLabel->setText(ui->formulaLabel->toPlainText() + "(");
    ++openBracketCount;
    equalClicked = false;
    updateCursor();
}

void MainWindow::onClosedBracketClicked() {
    if (openBracketCount > 0) {
        ui->formulaLabel->setText(ui->formulaLabel->toPlainText() + ")");
        --openBracketCount;
        equalClicked = false;
    }
    updateCursor();
}

void MainWindow::onPeriodClicked() {
    QString text = ui->formulaLabel->toPlainText();
    if (text.isEmpty() || specials.contains(text[text.size()-1])) {
        text += "0";
    }
    ui->formulaLabel->setText(text + ".");
    equalClicked = false;
    updateCursor();
}

void MainWindow::onEqualsClicked() {
    if (ui->formulaLabel->toPlainText().isEmpty())
        return;
    try {
        double result = calculator.evaluate(ui->formulaLabel->toPlainText().toStdString());
        ui->formulaLabel->setText(QString::number(result));
        equalClicked = true;
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    updateCursor();
}

void MainWindow::onMemClearClicked() {
    calculator.memoryClear();
}

void MainWindow::onMemReadClicked() {
    try {
        ui->formulaLabel->setText(ui->formulaLabel->toPlainText() + QString::fromStdString(calculator.getMemory()));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
    updateCursor();
}

void MainWindow::onMemPlusClicked() {
    try {
        calculator.memoryPlus(ui->formulaLabel->toPlainText().toStdString());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::onMemMinusClicked() {
    try {
        calculator.memoryMinus(ui->formulaLabel->toPlainText().toStdString());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::updateCursor() {
    QTextCursor cursor = ui->formulaLabel->textCursor();
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::End);
    ui->formulaLabel->setTextCursor(cursor);
}
