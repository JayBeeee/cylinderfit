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

      /*mat A = randu<mat>(4,5);
      mat B = randu<mat>(4,5);

      vec c(3);
      c(0)=5;
      c(1)=4;
      c(2)=13;

      mat R=A*B.t();

      c.print();
      R.print();*/

    QString path = qApp->applicationDirPath();

    path=QString(path+"/zylinder01.pts");
    qDebug()<<path;


     QIODevice *d = new QFile(path);

     qDebug()<<"starte Punktimport Bitte warten";

     QList<Point3D> points = DataImporter::importXYZ(d);

     qDebug()<<QString(QString::number(points.size())+" Punkte eingelesen");

     qDebug()<<"starte Auslgiechung";

     Cylinder c;
     c.fit(points);

     qDebug()<<"Ausgleichung fertig";

     qDebug()<<QString(" x "+QString::number(c.nForm.x));
     qDebug()<<QString(" y "+QString::number(c.nForm.y));
     qDebug()<<QString(" alpha "+QString::number(c.nForm.alpha));
     qDebug()<<QString(" beta "+QString::number(c.nForm.beta));
     qDebug()<<QString(" radius "+QString::number(c.nForm.radius));


    return a.exec();
}
