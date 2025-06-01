#include "normalizationparameters.h"

NormalizationParameters::NormalizationParameters() {}

NormalizationParameters::NormalizationParameters(
    double min, double max, double dxStep, double dyStep, int windowH, int windowW)
    : _min(min), _max(max), _dxStep(dxStep), _dyStep(dyStep),
    _windowW(windowW), _windowH(windowH) {}

double NormalizationParameters::min() const { return _min; }
double NormalizationParameters::max() const { return _max; }
double NormalizationParameters::dxStep() const { return _dxStep; }
double NormalizationParameters::dyStep() const { return _dyStep; }
int NormalizationParameters::windowH() const { return _windowH; }
int NormalizationParameters::windowW() const { return _windowW; }

void NormalizationParameters::setMin(double value) { _min = value; }
void NormalizationParameters::setMax(double value) { _max = value; }
void NormalizationParameters::setDxStep(double value) { _dxStep = value; }
void NormalizationParameters::setDyStep(double value) { _dyStep = value; }
void NormalizationParameters::setWindowH(int value) { _windowH = value; }
void NormalizationParameters::setWindowW(int value) { _windowW = value; }
