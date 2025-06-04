#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "gesturegraphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , facade(fileReader, drawer)
{
    ui->setupUi(this);

    drawer.setView(ui->graphicsView);
    drawer.drawAxles(true);
    drawer.setSceneState(facade.sceneState());

    ui->graphicsView->setWindow(this);

    connect(ui->loadFileButton, &QPushButton::clicked, this, &MainWindow::loadFileButtonClicked);

    connect(ui->scaleXSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->scaleYSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->scaleZSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->posXSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->posYSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->posZSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->rotXSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->rotYSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->rotZSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFileButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open CSV"), "/", tr("CSV File (*.csv)"));

    normParams.setMin(ui->minNormSpinBox->value());
    normParams.setMax(ui->maxNormSpinBox->value());
    normParams.setDxStep(ui->stepXSpinBox->value());
    normParams.setDyStep(ui->stepYSpinBox->value());
    normParams.setWindowH(ui->graphicsView->height());
    normParams.setWindowW(ui->graphicsView->width());

    drawer.setNormParams(normParams);

    editingValues = true;
    resetEditor();
    editingValues = false;

    try {
    facade.loadFigure(fileName.toStdString(), normParams);
    facade.drawScene();

    } catch (std::exception e) {
        throwException(e);
    }

    ui->loadedFileLabel->setText("Loaded file: " + QFileInfo(fileName).fileName());

}

void MainWindow::onEditorChanged() {
    if (!editingValues) {
        double posX = ui->posXSpinBox->value();
        double posY = ui->posYSpinBox->value();
        double posZ = ui->posZSpinBox->value();

        facade.moveScene(posX, posY, posZ);

        double angleX = ui->rotXSpinBox->value();
        double angleY = ui->rotYSpinBox->value();
        double angleZ = ui->rotZSpinBox->value();

        facade.rotateScene(angleX, angleY, angleZ);

        double scaleX = ui->scaleXSpinBox->value();
        double scaleY = ui->scaleYSpinBox->value();
        double scaleZ = ui->scaleZSpinBox->value();

        facade.scaleScene(scaleX, scaleY, scaleZ);

        facade.drawScene();
    }
}

void MainWindow::gestureScale(double delta) {
    editingValues = true;

    ui->scaleXSpinBox->setValue(ui->scaleXSpinBox->value() + delta);
    ui->scaleYSpinBox->setValue(ui->scaleYSpinBox->value() + delta);
    ui->scaleZSpinBox->setValue(ui->scaleZSpinBox->value() + delta);

    editingValues = false;

    onEditorChanged();
}

void MainWindow::gestureMove(double deltaX, double deltaY) {
    editingValues = true;

    ui->posXSpinBox->setValue(ui->posXSpinBox->value() + deltaX);
    ui->posYSpinBox->setValue(ui->posYSpinBox->value() + deltaY);

    editingValues = false;

    onEditorChanged();
}

void MainWindow::gestureRotate(double deltaX, double deltaY, double deltaZ) {
    editingValues = true;

    ui->rotXSpinBox->setValue(
        std::fmod(ui->rotXSpinBox->value() + deltaX + 360.0, 360.0));
    ui->rotYSpinBox->setValue(
        std::fmod(ui->rotYSpinBox->value() + deltaY + 360.0, 360.0));
    ui->rotZSpinBox->setValue(
        std::fmod(ui->rotZSpinBox->value() + deltaZ + 360.0, 360.0));

    editingValues = false;

    onEditorChanged();
}

void MainWindow::throwException(const std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
}

void MainWindow::resetEditor() {
    ui->posXSpinBox->setValue(0);
    ui->posYSpinBox->setValue(0);
    ui->posZSpinBox->setValue(0);

    ui->rotXSpinBox->setValue(0);
    ui->rotYSpinBox->setValue(0);
    ui->rotZSpinBox->setValue(0);

    ui->scaleXSpinBox->setValue(1);
    ui->scaleXSpinBox->setValue(1);
    ui->scaleXSpinBox->setValue(1);

}
