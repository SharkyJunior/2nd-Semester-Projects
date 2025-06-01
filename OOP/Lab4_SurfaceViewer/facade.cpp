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
    } catch (std::exception e) {
        return FacadeOperationResult(false, e.what());
    }

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::loadFigure(const string& path,
                                         NormalizationParameters normParams) {
    try {
        _scene.addFigure( _fileReader->readFigure(path, normParams) );
    } catch (std::exception e) {
        return FacadeOperationResult(false, e.what());
    }

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::moveScene(double x, double y, double z) {
    double dx = x, dy = y, dz = z;

    if (posSet) {
        dx = x - curPosX;
        dy = y - curPosY;
        dz = z - curPosZ;
    }

    if (dx == 0 && dy == 0 && dz == 0)
        return FacadeOperationResult(true);

    try {
        _scene.transformFigures(TransformMatrixBuilder::createMoveMatrix(dx, dy, dz));
        curPosX = x; curPosY = y; curPosZ = z;
    } catch (const std::exception& e) {
        return FacadeOperationResult(false, e.what());
    }

    posSet = true;

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::scaleScene(double x, double y, double z) {
    double dx = x, dy = y, dz = z;

    if (scaleSet) {
        dx = x / curScaleX;
        dy = y / curScaleY;
        dz = z / curScaleZ;
    }

    if (dx == 1 && dy == 1 && dz == 1)
        return FacadeOperationResult(true);


    try {
        _scene.transformFigures(TransformMatrixBuilder::createScaleMatrix(dx, dy, dz));
        curScaleX = x; curScaleY = y; curScaleZ = z;
    } catch (std::exception e) {
        return FacadeOperationResult(false, e.what());
    }

    scaleSet = true;

    return FacadeOperationResult(true);
}

FacadeOperationResult Facade::rotateScene(double x, double y, double z) {
    double dx = x, dy = y, dz = z;

    if (rotSet) {
        dx = (x - curRotX) * M_PI / PI_RADIAN;
        dy = (y - curRotY) * M_PI / PI_RADIAN;
        dz = (z - curRotZ) * M_PI / PI_RADIAN;
    }

    if ((dx + dy + dz) == 0)
        return FacadeOperationResult(true);

    try {
        _scene.transformFigures(TransformMatrixBuilder::createRotationMatrix(dx, dy, dz));
        curRotX = x; curRotY = y; curRotZ = z;
    } catch (std::exception e) {
        return FacadeOperationResult(false, e.what());
    }

    rotSet = true;

    return FacadeOperationResult(true);
}





