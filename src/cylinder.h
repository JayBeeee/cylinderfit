#ifndef CYLINDER_H
#define CYLINDER_H

#include <iostream>
#include <armadillo>
#include <QList>
#include "point3d.h"
#include <QDebug>
#include <QtCore/QtMath> //qSin, qCos.....
#include <random>


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

struct RandomFactory
{


    QList<int> *indizes;
    int *grenze;
    int *zaehler;
    std::uniform_int_distribution<int> *distribution;
    std::default_random_engine *generator;
};

class Cylinder
{
public:
    Cylinder();

    vec *xyz;
    vec *ijk;
    double radius;

    QList<Point3D> observations;

    NormalForm nForm;

    bool fit(QList<Point3D> points);

private:
    void calcApproximation(QList<Point3D> points);

    bool subsamplePointList(RandomFactory &r,QList<Point3D> &points,QList<Point3D> &samplePoints);


};

#endif // CYLINDER_H
