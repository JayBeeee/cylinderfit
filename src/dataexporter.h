#ifndef DATAEXPORTER_H
#define DATAEXPORTER_H
#include <QIODevice>
#include <QTextStream>
#include <QList>
#include <QDebug>
#include "point3d.h"
#include "cylinder.h"

class dataexporter
{
public:
     dataexporter();
     int writefile();
     int len;
     double x[1000];
     double y[1000];
     double z[1000];

public:
       //static QList<Point3D> exportXYZ(QIODevice *out);
};


#endif // DATAEXPORTER_H
