#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H

#include <QIODevice>
#include <QTextStream>
#include <QList>
#include <QDebug>
#include "point3d.h"
#include "cylinder.h"

class DataImporter
{

public:
    explicit DataImporter();

public:

    /*!
     * \brief importXYZ
     * \param d
     * \return
     *
     * QIODevice ist eine Datei / Stream die / den ich einlesen will
     * die Import Funktion übergiebt eine QListe mit 3D Punkten
     */
    static QList<Point3D> importXYZ(QIODevice *d);

    static bool exportXYZ(QList<Point3D>,QIODevice *d);

    static bool exportTransformationsparameter(NormalForm,QIODevice*d);

    static bool exportVRML(QList<Point3D>,NormalForm,QIODevice*d);
};

#endif // DATAIMPORTER_H
