#ifndef NORMALIZATIONPARAMETERS_H
#define NORMALIZATIONPARAMETERS_H

// done

class NormalizationParameters {
    double _min, _max, _dxStep, _dyStep;

public:
    NormalizationParameters();
    NormalizationParameters(double min, double max, double dxStep, double dyStep);

    double min() const;
    void setMin(double value);
    double max() const;
    void setMax(double value);
    double dxStep() const;
    void setDxStep(double value);
    double dyStep() const;
    void setDyStep(double value);
};


#endif // NORMALIZATIONPARAMETERS_H
