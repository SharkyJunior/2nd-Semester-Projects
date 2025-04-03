#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"

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
    AppContext context;

    //utilities
    void updateRadioButtons();
    void handleErrorCode();
    void updateUi();

    //slots
    void on_fromDecRadioButton_clicked();
    void on_fromBinRadioButton_clicked();
    void on_fromOctRadioButton_clicked();
    void on_toDecRadioButton_clicked();
    void on_toBinRadioButton_clicked();
    void on_toOctRadioButton_clicked();
    void on_convertButton_clicked();
    void on_copyButton_clicked();
    void on_swapButton_clicked();
};
#endif // MAINWINDOW_H
