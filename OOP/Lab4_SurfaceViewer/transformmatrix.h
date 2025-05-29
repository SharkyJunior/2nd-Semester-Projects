#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "point3d.h"

// done

class TransformMatrix
{
public:
    TransformMatrix();
    TransformMatrix(double matrix[4][4]);

    friend TransformMatrix operator *(const TransformMatrix& s1, const TransformMatrix& s2);
    Point3D transformPoint(const Point3D& point) const;

private:
    double _m[4][4];
};

// done

class TransformMatrixBuilder {
public:
    static TransformMatrix createRotationMatrix(double radianX,
                                                double radianY,
                                                double radianZ);

    static TransformMatrix createMoveMatrix(double x, double y, double z);

    static TransformMatrix createScaleMatrix(double x, double y, double z);
};

#endif // TRANSFORMMATRIX_H
