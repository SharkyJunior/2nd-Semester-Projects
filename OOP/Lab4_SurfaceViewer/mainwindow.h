#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include "facade.h"
#include "scene.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// done
class QtSceneDrawer : public SceneDrawerBase {
public:
    QtSceneDrawer();
    void setView(QGraphicsView* view);
    void drawAxles(bool value);
    void setNormParams(NormalizationParameters normParams);
    void setSceneState(SceneState* state);
    void drawScene(const Scene& scene) override;
private:
    QGraphicsView* _view;
    NormalizationParameters _normParams;
    SceneState* _state;
    bool _drawAxles = false;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class GestureGraphicsView;
    friend void QtSceneDrawer::drawScene(const Scene& scene);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FileReader fileReader;
    QtSceneDrawer drawer;
    Facade facade;
    NormalizationParameters normParams;
    bool editingValues = false;

    // utilities
    void throwException(const std::exception& e);

    void gestureScale(double delta);
    void gestureMove(double deltaX, double deltaY);
    void gestureRotate(double deltaX, double deltaY, double deltaZ);

    void resetEditor();

    // slots
    void loadFileButtonClicked();
    void onEditorChanged();

};
#endif // MAINWINDOW_H
