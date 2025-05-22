#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Calculator calculator;

    QString specials = " +-*/()";
    QString operators = "+-*/";
    bool equalClicked = false;
    int openBracketCount = 0;

    // utilities
    void updateCursor();

    // slots
    void onACClicked();
    void onDelClicked();
    void onPeriodClicked();
    void onEqualsClicked();
    void onOpenBracketClicked();
    void onClosedBracketClicked();

    void onNumberClicked();
    void onOperatorClicked();

    void onMemClearClicked();
    void onMemReadClicked();
    void onMemPlusClicked();
    void onMemMinusClicked();
};

#endif // MAINWINDOW_H
