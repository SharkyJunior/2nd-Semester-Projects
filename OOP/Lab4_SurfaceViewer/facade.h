#ifndef FACADE_H
#define FACADE_H

#include "filereader.h"
#include "scene.h"

// done

class FacadeOperationResult {
public:
    FacadeOperationResult(bool isSuccess, const string& errorMessage = "");
    string getErrorMessage() const;
    bool isSuccess() const;
private:
    string _errorMessage;
    bool _isSuccess;
};

class Facade
{
public:
    Facade(BaseFileReader& fileReader, SceneDrawerBase& sceneDrawer);
    FacadeOperationResult drawScene();
    FacadeOperationResult loadFigure(const string& path,
                                    NormalizationParameters normParams);
    FacadeOperationResult moveScene(double x, double y, double z);
    FacadeOperationResult rotateScene(double x, double y, double z);
    FacadeOperationResult scaleScene(double x, double y, double z);

    SceneState* sceneState();

private:
    BaseFileReader* _fileReader;
    SceneDrawerBase* _sceneDrawer;
    Scene _scene;
    SceneState _sceneState;
    bool posSet = false, rotSet = false, scaleSet = false;
};

#endif // FACADE_H
