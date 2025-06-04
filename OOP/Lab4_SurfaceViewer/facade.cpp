#include "facade.h"

#include "transformmatrix.h"
#include "consts.h"

//-------------------------
// FacadeOperationResult
//-------------------------

FacadeOperationResult::FacadeOperationResult(bool isSuccess, const string& errorMessage)
    : _errorMessage(errorMessage), _isSuccess(isSuccess) {}


string FacadeOperationResult::getErrorMessage() const { return _errorMessage; }

bool FacadeOperationResult::isSuccess() const { return _isSuccess; }



//-------------------------
// Facade
//-------------------------


Facade::Facade(BaseFileReader& fileReader, SceneDrawerBase& sceneDrawer)
    : _fileReader(&fileReader), _sceneDrawer(&sceneDrawer), _scene(Scene()) {}

FacadeOperationResult Facade::drawScene() {
    try {
        _sceneDrawer->drawScene(_scene);
    } catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::loadFigure(const string& path,
                                         NormalizationParameters normParams) {
    try {
        _scene.addFigure( _fileReader->readFigure(path, normParams) );
    } catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::moveScene(double x, double y, double z) {
    double dx = x, dy = y, dz = z;

    if (posSet) {
        dx = x - _sceneState.getCurPosX();
        dy = y - _sceneState.getCurPosY();
        dz = z - _sceneState.getCurPosZ();
    }

    if (dx == 0 && dy == 0 && dz == 0)
        return FacadeOperationResult(true);

    try {
        _scene.transformFigures(TransformMatrixBuilder::createMoveMatrix(dx, dy, dz));
        _sceneState.setCurPosX(x);
        _sceneState.setCurPosY(y);
        _sceneState.setCurPosZ(z);
    } catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }

    posSet = true;

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::scaleScene(double x, double y, double z) {
    double dx = x, dy = y, dz = z;

    if (scaleSet) {
        dx = x / _sceneState.getCurScaleX();
        dy = y / _sceneState.getCurScaleY();
        dz = z / _sceneState.getCurScaleZ();
    }

    if (dx == 1 && dy == 1 && dz == 1)
        return FacadeOperationResult(true);


    try {
        _scene.transformFigures(TransformMatrixBuilder::createScaleMatrix(dx, dy, dz));
        _sceneState.setCurScaleX(x);
        _sceneState.setCurScaleY(y);
        _sceneState.setCurScaleZ(z);
    } catch (std::exception e) {
        return FacadeOperationResult(false, e.what());
    }

    scaleSet = true;

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::rotateScene(double x, double y, double z) {
    double dx = x, dy = y, dz = z;

    if (rotSet) {
        dx = (x - _sceneState.getCurRotX()) * M_PI / PI_RADIAN;
        dy = (y - _sceneState.getCurRotY()) * M_PI / PI_RADIAN;
        dz = (z - _sceneState.getCurRotZ()) * M_PI / PI_RADIAN;
    }

    if ((dx + dy + dz) == 0)
        return FacadeOperationResult(true);

    try {
        _scene.transformFigures(TransformMatrixBuilder::createRotationMatrix(dx, dy, dz));
        _sceneState.setCurRotX(x);
        _sceneState.setCurRotY(y);
        _sceneState.setCurRotZ(z);
    } catch (std::exception e) {
        return FacadeOperationResult(false, e.what());
    }

    rotSet = true;

    return FacadeOperationResult(true);
}

SceneState* Facade::sceneState() { return &_sceneState; }


