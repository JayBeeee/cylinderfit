#include <QCoreApplication>
#include <iostream>
#include <armadillo>
#include <QFile>
#include "dataimporter.h"
#include "cylinder.h"


using namespace std;
using namespace arma;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = qApp->applicationDirPath();

    path=QString(path+"/zylinder06.pts");
    qDebug()<<path;


     QIODevice *d = new QFile(path);

     qDebug()<<"starte Punktimport Bitte warten";

     QList<Point3D> points = DataImporter::importXYZ(d);

     qDebug()<<QString(QString::number(points.size())+" Punkte eingelesen");

     qDebug()<<"starte Auslgeichung";

     Cylinder c;
     c.fit(points);

     qDebug()<<"Ausgleichung fertig";

     qDebug()<<QString(" x "+QString::number(c.nForm.x));
     qDebug()<<QString(" y "+QString::number(c.nForm.y));
     qDebug()<<QString(" alpha "+QString::number(c.nForm.alpha));
     qDebug()<<QString(" beta "+QString::number(c.nForm.beta));
     qDebug()<<QString(" radius "+QString::number(c.nForm.radius));

     QString export_path = qApp->applicationDirPath();

     export_path=QString(export_path+"/zylinder_ausgabe.pts");
     qDebug()<<export_path;


     QIODevice *export_d = new QFile(export_path);

    DataImporter::exportXYZ(c.observations,export_d);

    return a.exec();
}
