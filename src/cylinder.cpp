#include "cylinder.h"


Cylinder::Cylinder()
{
    this->xyz=new vec(3);
    this->ijk=new vec(3);
}

bool Cylinder::fit(QList<Point3D> points)
{
    RandomFactory r;
    r.distribution= new  std::uniform_int_distribution<int> (0, points.size()-1);
    std::random_device rd;
    r.generator= new std::default_random_engine ( rd() );

    QList<Point3D>samplePoints;
    r.indizes= new QList<int>;
    r.grenze= new int(10000);

    r.zaehler=new int(0);
    qDebug()<<"Start subsampling";
    this->subsamplePointList(r,points,samplePoints);


    qDebug()<<"Start approximation";
    this->calcApproximation(samplePoints);

    qDebug()<<"Start fit";
    int n = samplePoints.size();
    //qDebug()<<QString::number(n);

    vec L(n*3); //Beobachtungen
    vec v(n*3); //Näherungswerte für Verbesserungen
    v=v.zeros();
    vec L0(n*3); //Beobachtungen + Näherungswerte für Verbesserungen
    vec X0(5); //Näherungswerte für Unbekannte (r, X0, Y0, alpha, beta)
    vec x(5); //Zuschläge für Unbekannte
    mat A(n, 5); //Ableitungen nach Unbekannten
    mat B(n, 3*n); //Ableitungen nach Beobachtungen +v0
    B=B.zeros();

    vec w(n); //Widerspruchsvektor


    X0(0)=nForm.radius;
    X0(1)=nForm.x;
    X0(2)=nForm.y;
    X0(3)=nForm.alpha;
    X0(4)=nForm.beta;

    X0.print();


    //Aufstellen des Beobachtungsvektors
    for(int i = 0; i < n; i++)
    {
        L.at(i*3)=samplePoints.at(i).xyz->at(0);
        L.at(i*3+1)=samplePoints.at(i).xyz->at(1);
        L.at(i*3+2)=samplePoints.at(i).xyz->at(2);
    }


    L0= L;
    int z=0;
    int iteration=1;
    while(z < iteration)
    {
        //Unbekannten neu berechnen
        X0=X0+x;


        //Verbesserter Beobachtungsvektor
        L0=L0+v;
        // Aufstellen der Rotationsmatrizen
        mat RotAlpha(3, 3);
        mat RotBeta(3, 3);

        //Zeile,Spalte=Inhalt
        RotAlpha(0, 0)= 1.0;
        RotAlpha(0, 1)= 0.0;
        RotAlpha(0, 2)= 0.0;
        RotAlpha(1, 0)= 0.0;
        RotAlpha(1, 1)= cos(X0.at(3));
        RotAlpha(1, 2)= -sin(X0.at(3));
        RotAlpha(2, 0)= 0.0;
        RotAlpha(2, 1)= sin(X0.at(3));
        RotAlpha(2, 2)= cos(X0.at(3));

        RotBeta(0, 0)= cos(X0.at(4));
        RotBeta(0, 1)= 0.0;
        RotBeta(0, 2)= sin(X0.at(4));
        RotBeta(1, 0)= 0.0;
        RotBeta(1, 1)= 1.0;
        RotBeta(1, 2)= 0.0;
        RotBeta(2, 0)= sin(X0.at(4));
        RotBeta(2, 1)= 0.0;
        RotBeta(2, 2)= cos(X0.at(4));


        //Aufstellen der A-Funktionalmatrix and B-Ränderungsmatrix

        double tmpX0 = X0(1);
        double tmpY0 = X0(2);
        double tmpAlpha = X0(3);
        double tmpBeta = X0(4);

        for(int i = 0; i < n; i++)
        {
            double tmpX = L(i*3);
            double tmpY = L(i*3+1);
            double tmpZ = L(i*3+2);
            // qDebug()<<QString::number(tmpX0);


            double a1 = tmpX0 + tmpX * cos(tmpBeta) + tmpY * sin(tmpAlpha) * sin(tmpBeta) + tmpZ * cos(tmpAlpha) * sin(tmpBeta);
            double a2 = tmpY0 + tmpY * cos(tmpAlpha) - tmpZ * sin(tmpAlpha);
           //qDebug()<<QString::number(a1);
          // qDebug()<<QString::number(a2);

            //radius,X0,Y0,Alpha,Beta
            A(i, 0)= 1.0; //radius
            A(i, 1)= -1.0 * a1 / sqrt(a1*a1 + a2*a2); // X0
            A(i, 2)= -1.0 * a2 / sqrt(a1*a1 + a2*a2); // Y0
            A(i, 3)=   -1.0 * ((tmpY * sin(tmpBeta) * cos(tmpAlpha) - tmpZ * sin(tmpBeta) * sin(tmpAlpha)) * a1 - (tmpY * sin(tmpAlpha) + tmpZ * cos(tmpAlpha)) * a2) / sqrt(a1*a1 + a2*a2);
            A(i, 4)= -1.0 * (tmpY * sin(tmpAlpha) * cos(tmpBeta) - tmpX * sin(tmpBeta) + tmpZ * cos(tmpAlpha) * cos(tmpBeta)) * a1 / sqrt(a1*a1 + a2*a2); // beta

      // A.print();
           // B=B*0.0;
            B(i, i*3)=1.0*( -1.0 * cos(tmpBeta) * a1 / sqrt(a1*a1 + a2*a2)); // x
            B(i, i*3+1)= 1.0*(-1.0 * (sin(tmpAlpha) * sin(tmpBeta) * a1 + cos(tmpAlpha) * a2) / sqrt(a1*a1 + a2*a2)); // y
            B(i, i*3+2)=1.0* (-1.0 * (cos(tmpAlpha) * sin(tmpBeta) * a1 - sin(tmpAlpha) * a2) / sqrt(a1*a1 + a2*a2)); // z
        }



        //Aufstellen des Widerspruchsvektors
        for(int i = 0; i < n; i++)
        {

            vec punkt_i(3);
            punkt_i(0)=L0(i*3);
            punkt_i(1)=L0(i*3+1);
            punkt_i(2)= L0(i*3+2);


            vec Ntransform_punkt_i = RotBeta * RotAlpha * punkt_i;
            Ntransform_punkt_i(0)= Ntransform_punkt_i(0) + X0(1);
            Ntransform_punkt_i(1)= Ntransform_punkt_i(1) + X0(2);



            //genäherter Radius des Zylinders minus Abstand Punkt i zur z-Achse ist der Widerspruch
            double widerspruch = X0(0) - qSqrt(Ntransform_punkt_i(0)*Ntransform_punkt_i(0) + Ntransform_punkt_i(1)*Ntransform_punkt_i(1));

            w(i)=widerspruch;
        }


        //rechte Seite  (Beobachtungen+Unbekannte als Dimension)
        vec rechteSeite(n+5);
        rechteSeite=rechteSeite.zeros();
        for(int i = 0; i < n; i++)
        {
            rechteSeite(i)= w(i);
        }

        //Aufstellen der Normalgleichungsmatrix N-Matric

        mat B_BT = B * B.t();

       // B_BT.print();

        mat AT = A.t();
        mat N(n+5, n+5);
        for(int i = 0; i < (n+5); i++){
            for(int j = 0; j < (n+5); j++)
            {
                if(i < n && j < n)
                {
                    N(i, j)= B_BT(i, j);
                }else if(i < n && j >= n)
                {
                    N(i, j)= A(i, (j-n));
                }else if(i >= n && j < n)
                {
                    N(i, j)= AT((i-n), j);
                }else if(i >= n && j >= n)
                {
                    N(i, j)= 0.0;
                }
            }
        }

        //Inverse von N
       //N.print();
        mat N_inv=N.i();
      // N_inv.print();
        //Ausgleichungsrechnung
        vec ergebnis = -1.0 * N_inv * rechteSeite;
       //ergebnis.print();

        //Weiterverarbeitung der Ergebnisse der Ausgleichung

        //get results
        vec k(n);

        for(int i = n; i < n+5; i++){
            x(i-n)= ergebnis(i-n);
        }
        x.print();
        for(int i = 0; i < n; i++){
             k(i)=ergebnis(i);
        }

        v = B.t() * k;
        z++;
    }
   //v.print();
    //Verbesserter Beobachtungsvektor
    L0=L0+v;

    for(int i = 0; i < n; i++)
    {
       samplePoints.at(i).setVerb(v(i),v(i+1),v(i+2));
      // samplePoints.at(i).verb->print()
    }
    this->observations=samplePoints;

    //Unbekannten neu berechnen
    X0=X0+x;

    this->nForm.x = X0(1);
    this->nForm.y = X0(2);
    this->nForm.alpha = X0(3);
    this->nForm.beta = X0(4);
    this->nForm.radius =  X0(0);
    return true;
}

void Cylinder::calcApproximation(QList<Point3D> points)
{

    this->nForm.x = -534.4;
    this->nForm.y = -787.7;
    this->nForm.alpha = 0.84;
    this->nForm.beta = -0.21;
    this->nForm.radius = 0.4;
}

bool Cylinder::subsamplePointList(RandomFactory &r,QList<Point3D> &points,QList<Point3D> &samplePoints)
{

    //Hier werden zufällige Punkte für die Ausgleichung ausgewählt,
   //da 47000 Punkte die B-Matrix sprengen --> zwar konnte man in Armadillo
   //die Einstellungen vornehmen um auf 64bit um zustellen,
   //jedoch reichen selbst 16GB-Arbeitsspeicher nicht aus!

   //std::default_random_engine generator;
  // std::uniform_int_distribution<int> distribution(0,points.size());




   //Wenn die Punktwolke größer als der Grenzwert ist,dann
   if (*r.grenze<points.size())
   {
       //qDebug()<<zaehler;

            //Erzeuge eine Zufallszahl und schreibe diese in den Array indizes
           int randomIndex =  r.distribution->operator ()(*r.generator);



             if (r.indizes->contains(randomIndex))//Returns true if contains
                {
                  return subsamplePointList(r,points,samplePoints);
               }

             if (*r.zaehler<*r.grenze)
             {
               //qDebug()<<randomIndex;
               samplePoints.append(points.at(randomIndex));
               r.indizes->append(randomIndex);
               *r.zaehler+=1;


               return subsamplePointList(r,points,samplePoints);
               }
               else
               {
                   return true;
               }


    //Ansonsten werden alle Punkte für die Approximation verwendet
   }else
   {
          samplePoints=points;
          return true;
   }
}
