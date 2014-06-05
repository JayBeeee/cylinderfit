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

           // qDebug() << QString::number(tmpPoint.xyz->at(2));
        }

    }

    d->close();

    return punktListe;
}

bool DataImporter::exportXYZ(QList<Point3D> points, QIODevice *d)
{
    //open and check device
    if (!d->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

     QTextStream ausgabe(d);

     foreach(Point3D p,points)
     {
         vec adjustedPoint=p.getAdjustedPoint();
         ausgabe << adjustedPoint.at(0)<<" "<<adjustedPoint.at(1)<<" "<<adjustedPoint.at(2) <<"\n";

     }
     d->close();

     return true;
}
