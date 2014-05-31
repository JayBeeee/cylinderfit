#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H

#include <QIODevice>
#include <QTextStream>
#include <QList>
#include <QDebug>
#include "point3d.h"


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

};

#endif // DATAIMPORTER_H
