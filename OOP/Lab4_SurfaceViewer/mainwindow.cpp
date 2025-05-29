#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "appcontext.h"
#include "entrypoint.h"
#include "surfacepainter.h"
#include "gesturegraphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setInitialValues();
    ui->graphicsView->setWindow(this);

    connect(ui->loadFileButton, &QPushButton::clicked, this, &MainWindow::loadFileButtonClicked);

    connect(ui->minNormSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->maxNormSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->stepDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
    connect(ui->scaleSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::onEditorChanged);
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
    loadingInProgress = true;
    AppParams params;

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open CSV"), "/", tr("CSV File (*.csv)"));
    QByteArray array = fileName.toLocal8Bit();
    strncpy(params.filePath, array.data(), array.size());

    doOperation(LoadSurface, &context, &params);

    ui->loadedFileLabel->setText("Loaded file: " + QFileInfo(fileName).fileName());

    QGraphicsScene* scene = paintSurface(&context.surfaceData, &context.camera);

    ui->graphicsView->setScene(scene);

    updateUi();

    handleErrorCode();
    loadingInProgress = false;
}

void MainWindow::onEditorChanged() {
    if (!loadingInProgress) {
        qDebug() << "updated";

        AppParams params;

        params.isGesture = isGesture;

        params.posX = ui->posXSpinBox->value();
        params.posY = ui->posYSpinBox->value();
        params.posZ = ui->posZSpinBox->value();

        params.angleX = ui->rotXSpinBox->value();
        params.angleY = ui->rotYSpinBox->value();
        params.angleZ = ui->rotZSpinBox->value();

        params.scale = ui->scaleSpinBox->value();

        params.minNorm = ui->minNormSpinBox->value();
        params.maxNorm = ui->maxNormSpinBox->value();
        params.step = ui->stepDoubleSpinBox->value();

        doOperation(UpdateSurface, &context, &params);

        QGraphicsScene* scene = paintSurface(&context.surfaceData, &context.camera);

        scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
        ui->graphicsView->setScene(scene);
        ui->graphicsView->centerOn(context.camera.windowW / 2, context.camera.windowH / 2);

        // ui->graphicsView->setScene(scene);
        // ui->graphicsView->centerOn(ui->graphicsView->width() / 2, ui->graphicsView->height() / 2);

        handleErrorCode();
    }
}

void MainWindow::setInitialValues() {
    context.camera.windowH = ui->graphicsView->height();
    context.camera.windowW = ui->graphicsView->width();
}

void MainWindow::updateUi() {
    ui->posXSpinBox->setValue(context.camera.posX);
    ui->posYSpinBox->setValue(context.camera.posY);
    ui->posZSpinBox->setValue(context.camera.posZ);

    ui->rotXSpinBox->setValue(context.camera.angleX);
    ui->rotYSpinBox->setValue(context.camera.angleY);
    ui->rotZSpinBox->setValue(context.camera.angleZ);

    ui->scaleSpinBox->setValue(context.camera.scale);

    ui->minNormSpinBox->setValue(context.surfaceData.minNorm);
    ui->maxNormSpinBox->setValue(context.surfaceData.maxNorm);
    ui->stepDoubleSpinBox->setValue(context.surfaceData.step);
}

void MainWindow::handleErrorCode() {
    return;
}
