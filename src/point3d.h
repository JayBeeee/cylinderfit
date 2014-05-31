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
};

#endif // POINT3D_H
