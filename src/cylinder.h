#ifndef CYLINDER_H
#define CYLINDER_H

#include <iostream>
#include <armadillo>
#include <QList>
#include "point3d.h"
#include <QDebug>
#include <QtCore/QtMath> //qSin, qCos.....

using namespace std;
using namespace arma;

struct NormalForm
{
    double x;
    double y;
    double alpha;
    double beta;
    double radius;
};

class Cylinder
{
public:
    Cylinder();

    vec *xyz;
    vec *ijk;
    double radius;

    NormalForm nForm;

    bool fit(QList<Point3D> points);

private:
    void calcApproximation(QList<Point3D> points);

};

#endif // CYLINDER_H
