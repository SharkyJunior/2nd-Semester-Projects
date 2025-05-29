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

    friend class GestureGraphicsView;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AppContext context;
    bool loadingInProgress = false, isGesture = false;

    // utilities
    void setInitialValues();
    void handleErrorCode();
    void updateUi();

    // slots
    void loadFileButtonClicked();

    void onEditorChanged();
};
#endif // MAINWINDOW_H
