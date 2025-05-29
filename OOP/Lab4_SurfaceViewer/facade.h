#ifndef FACADE_H
#define FACADE_H

#include "filereader.h"
#include "scene.h"

class FacadeOperationResult {
public:
    string getErrorMessage();
    bool isSuccess();
private:
    string _errorMessage;
    bool _isSuccess;
};

class Facade
{
public:
    Facade();
    FacadeOperationResult drawScene();
    FacadeOperationResult loadFigure(const string& path,
                                    NormalizationParameters normParams);
    FacadeOperationResult moveScene(double x, double y, double z);
    FacadeOperationResult rotateScene(double x, double y, double z);
    FacadeOperationResult scaleScene(double x, double y, double z);

private:
    BaseFileReader _fileReader;
    SceneDrawerBase _sceneDrawer;
    Scene& _scene;
};

#endif // FACADE_H
