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

        QStringList list = line.split(QRegExp("\\s+")); //Ein oder mehrere Leerzeichen

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


bool DataImporter::exportTransformationsparameter(NormalForm nForm, QIODevice *d)
{
    //open and check device
    if (!d->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

     QTextStream ausgabe(d);


     ausgabe <<"Transformationsparameter des Zylinders in Normalform:\n\n"
             <<"Radius=  "<<nForm.radius<<"\n"
             <<"X=  "<<nForm.x<<"\n"
             <<"Y=  "<<nForm.y<<"\n"
             <<"Alpha=  "<<nForm.alpha<<"\n"
             <<"Beta=  "<<nForm.beta<<"\n";
     d->close();

     return true;
}


bool DataImporter::exportVRML(NormalForm nForm,QIODevice *d)
{
    //open and check device
    if (!d->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

     QTextStream ausgabe(d);
     QList<Point3D> points;
/*
     vec yWerte(points.size());

     foreach(Point3D p,points)
     {
     vec adjustedPoint=p.getAdjustedPoint();
     yWerte=adjustedPoint.at(1);
     }

     double maxY = yWerte.max() ;
     double minY = yWerte.min() ;

     double height=maxY-minY;
    // <<"Separator { \n"
*/
     ausgabe <<"#VRML V1.0 ascii \n"

             <<"DEF BackgroundColor Info{ \n"

             <<"string \"1 1 1\""<<"}"<<"\n"
             <<"Cylinder {\n"
             <<"radius "<< nForm.radius <<"\n"
             //<<"height" <<height<<"\n"
             <<"parts ALL }\n";

     d->close();

     return true;
}
