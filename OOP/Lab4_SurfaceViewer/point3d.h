#ifndef POINT3D_H
#define POINT3D_H

// done

class Point3D
{
    double _x, _y, _z;

public:
    Point3D();
    Point3D(double x, double y, double z);

    double x() const;
    void setX(double value);
    double y() const;
    void setY(double value);
    double z() const;
    void setZ(double value);
};

#endif // POINT3D_H
