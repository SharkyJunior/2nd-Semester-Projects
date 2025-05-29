#include "transformmatrix.h"

#include <algorithm>
#include <cmath>
#include "consts.h"

using namespace std;



// -----------------------------
// TransformMatrix
// -----------------------------

TransformMatrix::TransformMatrix() {}

TransformMatrix::TransformMatrix(double matrix[4][4]) {
    copy(matrix[0], matrix[0] + MATRIX_SIZE * MATRIX_SIZE, _m[0]);
}

TransformMatrix operator *(const TransformMatrix& s1, const TransformMatrix& s2) {
    TransformMatrix result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result._m[row][col] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result._m[row][col] += s1._m[row][k] * s2._m[k][col];
            }
        }
    }

    return result;
}

Point3D TransformMatrix::transformPoint(const Point3D& point) const {
    float x = point.x();
    float y = point.y();
    float z = point.z();
    float w = 1.0f;

    double rx = _m[0][0] * x + _m[0][1] * y + _m[0][2] * z + _m[0][3] * w;
    double ry = _m[1][0] * x + _m[1][1] * y + _m[1][2] * z + _m[1][3] * w;
    double rz = _m[2][0] * x + _m[2][1] * y + _m[2][2] * z + _m[2][3] * w;

    double w_out = _m[3][0] * x + _m[3][1] * y + _m[3][2] * z + _m[3][3] * w;

    if (w_out != 0.0f && w_out != 1.0f) {
        rx /= w_out;
        ry /= w_out;
        rz /= w_out;
    }

    return Point3D(rx, ry, rz);
}



// -----------------------------
// TransformMatrixBuilder
// -----------------------------

TransformMatrix TransformMatrixBuilder::createRotationMatrix(double radianX,
                                                             double radianY,
                                                             double radianZ)
{
    double arrX[MATRIX_SIZE][MATRIX_SIZE] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, cos(radianX), -sin(radianX), 0.0},
        {0.0, sin(radianX), cos(radianX), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };

    TransformMatrix rotX = TransformMatrix(arrX);

    double arrY[MATRIX_SIZE][MATRIX_SIZE] = {
        {cos(radianY), 0.0, sin(radianY), 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {-sin(radianY), 0.0, cos(radianY), 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };

    TransformMatrix rotY = TransformMatrix(arrY);

    double arrZ[MATRIX_SIZE][MATRIX_SIZE] = {
        {cos(radianZ), sin(radianZ), 0.0, 0.0},
        {-sin(radianZ), cos(radianZ), 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };

    TransformMatrix rotZ = TransformMatrix(arrZ);

    return rotX * rotY * rotZ;
}

TransformMatrix TransformMatrixBuilder::createMoveMatrix(double x, double y, double z)
{
    double arr[MATRIX_SIZE][MATRIX_SIZE] = {
        {1.0, 0.0, 0.0, x},
        {0.0, 1.0, 0.0, y},
        {0.0, 0.0, 1.0, z},
        {0.0, 0.0, 0.0, 1.0}
    };

    return TransformMatrix(arr);
}

TransformMatrix TransformMatrixBuilder::createScaleMatrix(double x, double y, double z)
{
    double arr[MATRIX_SIZE][MATRIX_SIZE] = {
        {x, 0.0, 0.0, 0.0},
        {0.0, y, 0.0, 0.0},
        {0.0, 0.0, z, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };

    return TransformMatrix(arr);
}

