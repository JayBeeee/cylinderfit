#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;


class Point3D
{
public:
    Point3D();

    vec *xyz;
    vec *verb;

    void setXYZ(double x, double y, double z) const;
    void setVerb(double vx, double vy, double vz) const;
    vec getAdjustedPoint() const;

};

#endif // POINT3D_H
