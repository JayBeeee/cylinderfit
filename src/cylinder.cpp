#include "cylinder.h"

Cylinder::Cylinder()
{
    this->xyz=new vec(3);
    this->ijk=new vec(3);
}

bool Cylinder::fit(QList<Point3D> points)
{
    this->calcApproximation(points);




    return false;
}

void Cylinder::calcApproximation(QList<Point3D> points)
{

    this->nForm.x = 666;
    this->nForm.y = 666;
    this->nForm.alpha = 666;
    this->nForm.beta = 666;
    this->nForm.radius = 666;
}
