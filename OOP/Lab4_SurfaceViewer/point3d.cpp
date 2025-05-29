#include "point3d.h"

Point3D::Point3D() {}

Point3D::Point3D(double x, double y, double z)
    : _x(x), _y(y), _z(z) {}

double Point3D::x() const { return _x; }

double Point3D::y() const { return _y; }

double Point3D::z() const { return _z; }

void Point3D::setX(double value) { _x = value; }

void Point3D::setY(double value) { _y = value; }

void Point3D::setZ(double value) { _z = value; }
