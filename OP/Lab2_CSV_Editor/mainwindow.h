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

    // utilities
    void updateUi();
    void updateTableWidget(const QString& filterName);
    void updateTableInfo(const QString& filterName);
    QStringList convToQStringList();
    void handleErrorCode();
    QString getErrorInfo(const ErrorCode err);
    void showMessageBox(QString info);

    // slots
    void chooseFileButtonClicked();
    void loadCsvButtonClicked();
    void filterRegionButtonClicked();
    void calcMetricsButtonClicked();
};


#endif // MAINWINDOW_H
