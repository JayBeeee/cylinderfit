#include "point3d.h"

Point3D::Point3D()
{
    xyz= new vec(3);
    verb=new vec(3);
}

void Point3D::setXYZ(double x, double y, double z) const
{
    this->xyz->at(0)=x;
    this->xyz->at(1)=y;
    this->xyz->at(2)=z;

}

void Point3D::setVerb(double vx, double vy, double vz) const
{
    this->verb->at(0)=vx;
    this->verb->at(1)=vy;
    this->verb->at(2)=vz;
}

vec Point3D::getAdjustedPoint() const
{
    vec adjustedPoint(3);
    adjustedPoint=*this->xyz+*this->verb;
    return adjustedPoint;
}
