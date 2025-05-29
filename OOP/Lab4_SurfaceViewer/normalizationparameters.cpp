#include "normalizationparameters.h"

NormalizationParameters::NormalizationParameters() {}

NormalizationParameters::NormalizationParameters(
    double min, double max, double dxStep, double dyStep)
    : _min(min), _max(max), _dxStep(dxStep), _dyStep(dyStep) {}

double NormalizationParameters::min() const { return _min; }
double NormalizationParameters::max() const { return _max; }
double NormalizationParameters::dxStep() const { return _dxStep; }
double NormalizationParameters::dyStep() const { return _dyStep; }

void NormalizationParameters::setMin(double value) { _min = value; }
void NormalizationParameters::setMax(double value) { _max = value; }
void NormalizationParameters::setDxStep(double value) { _dxStep = value; }
void NormalizationParameters::setDyStep(double value) { _dyStep = value; }
