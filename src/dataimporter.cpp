#include "dataimporter.h"

DataImporter::DataImporter()
{
}

QList<Point3D> DataImporter::importXYZ(QIODevice *d)
{
    QList<Point3D> punktListe;

    //open and check device
    if (!d->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return punktListe;
    }


    QTextStream einleser(d);

    while(!einleser.atEnd())
    {
        QString line = einleser.readLine();

        QStringList list = line.split(QRegExp("\\s+"));

        if (list.size()>=3)
        {
            Point3D tmpPoint;
            tmpPoint.xyz->at(0)=list.at(0).toDouble();
            tmpPoint.xyz->at(1)=list.at(1).toDouble();
            tmpPoint.xyz->at(2)=list.at(2).toDouble();

            punktListe.append(tmpPoint);

            //qDebug() << QString::number(tmpPoint.xyz->at(0));
        }

    }

    d->close();

    return punktListe;
}
