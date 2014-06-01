#include "cylinder.h"


Cylinder::Cylinder()
{
    this->xyz=new vec(3);
    this->ijk=new vec(3);
}

bool Cylinder::fit(QList<Point3D> points)
{
    QList<Point3D>samplePoints;

     //Hier werden zufällige Punkte für die Ausgleichung ausgewählt,
    //da 47000 Punkte die B-Matrix sprengen --> zwar konnte man in Armadillp
    //die Einstellungen vornehmen um auf 64bit um zustellen,
    //jedoch reichen selbst 16GB-Arbeitsspeicher nicht aus!

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,points.size());

    int indizes[1000];
    for(int i=0; i<1000;i++)
    {
         int randomIndex =  distribution(generator);
         indizes[i]=randomIndex;
         if (i<1)
         {
            samplePoints.append(points.at(randomIndex));
         }
         else
         {
             for (int j=0; j<i;)
             {
                if (randomIndex == indizes[j])
                {
                    int randomIndex =  distribution(generator);
                    indizes[i]=randomIndex;
                    break;
                }
                else
                {
                    j++;
                }
              }
             samplePoints.append(points.at(randomIndex));

         }
         // qDebug << samplePoints.at(i).xyz->print;
    }


    this->calcApproximation(samplePoints);

    int n = samplePoints.size();
   // qDebug()<<QString::number(n);

    vec L(n*3); //Beobachtungen
    vec v(n*3); //Näherungswerte für Verbesserungen
    vec L0(n*3); //Beobachtungen + Näherungswerte für Verbesserungen
    vec X0(5); //Näherungswerte für Unbekannte (r, X0, Y0, alpha, beta)
    vec x(5); //Zuschläge für Unbekannte
    mat B(n, 3*n); //Ableitungen nach (L+v0)
    mat A(n, 5); //Ableitungen nach Unbekannten
    vec w(n); //Widerspruchsvektor


    X0(0)=nForm.radius;
    X0(1)=nForm.x;
    X0(2)=nForm.y;
    X0(3)=nForm.alpha;
    X0(4)=nForm.beta;




    //Aufstellen des Beobachtungsvektors
    for(int i = 0; i < n; i++){
        L(i*3)=samplePoints.at(i).xyz->at(0);
        L(i*3+1)=samplePoints.at(i).xyz->at(1);
        L(i*3+2)=samplePoints.at(i).xyz->at(2);
    }



    //TODO do while iteration
   // L.print();
    L0 = L;


    //Unbekannten neu berechnen
    X0=X0+x;

    //Verbesserter Beobachtungsvektor
    L0=L0+v;

    // Aufstellen der Rotationsmatrizen
    mat RotAlpha(3, 3);
    mat RotBeta(3, 3);

    //Zeile,Spalte,Inhalt
    RotAlpha(0, 0, 1.0);
    RotAlpha(1, 1, qCos(X0.at(3)));
    RotAlpha(1, 2, -qSin(X0.at(3)));
    RotAlpha(2, 1, qSin(X0.at(3)));
    RotAlpha(2, 2, qCos(X0.at(3)));

    RotBeta(0, 0, qCos(X0.at(4)));
    RotBeta(0, 2, qSin(X0.at(4)));
    RotBeta(1, 1, 1.0);
    RotBeta(2, 0, -qSin(X0.at(4)));
    RotBeta(2, 2, qCos(X0.at(4)));


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

        double a1 = tmpX0 + tmpX * qCos(tmpBeta) + tmpY * qSin(tmpAlpha) * qSin(tmpBeta) + tmpZ * qCos(tmpAlpha) * qSin(tmpBeta);
        double a2 = tmpY0 + tmpY * qCos(tmpAlpha) - tmpZ * qSin(tmpAlpha);

        //radius,X0,Y0,Alpha,Beta
        A(i, 0)= 1.0; //radius
        A(i, 1)= -1.0 * a1 / qSqrt(a1*a1 + a2*a2); // X0
        A(i, 2)= -1.0 * a2 / qSqrt(a1*a1 + a2*a2); // Y0
        A(i, 3)=   -1.0 * ((tmpY * qSin(tmpBeta) * qCos(tmpAlpha) - tmpZ * qSin(tmpBeta) * qSin(tmpAlpha)) * a1 - (tmpY * qSin(tmpAlpha) + tmpZ * qCos(tmpAlpha)) * a2) / qSqrt(a1*a1 + a2*a2);
        A(i, 4)= -1.0 * (tmpY * qSin(tmpAlpha) * qCos(tmpBeta) - tmpX * qSin(tmpBeta) + tmpZ * qCos(tmpAlpha) * qCos(tmpBeta)) * a1 / qSqrt(a1*a1 + a2*a2); // beta

        B(i, i*3)= -1.0 * qCos(tmpBeta) * a1 / qSqrt(a1*a1 + a2*a2); // x
        B(i, i*3+1)= -1.0 * (qSin(tmpAlpha) * qSin(tmpBeta) * a1 + qCos(tmpAlpha) * a2) / qSqrt(a1*a1 + a2*a2); // y
        B(i, i*3+2)= -1.0 * (qCos(tmpAlpha) * qSin(tmpBeta) * a1 - qSin(tmpAlpha) * a2) / qSqrt(a1*a1 + a2*a2); // z

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
    for(int i = 0; i < n; i++){
        rechteSeite(i)= w(i);
    }

    //Aufstellen der Normalgleichungsmatrix N-Matric

    mat B_BT = B * B.t();
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
    mat N_inv=N.i();

    //Ausgleichungsrechnung
     vec ergebnis = -1.0 * N_inv * rechteSeite;

    //Weiterverarbeitung der Ergebnisse der Ausgleichung

     //get results
     vec k(n);
     //Zuschläge für die Unbekannten stehen unten im Ergebnisvektor
     for(int i = n; i < n+5; i++){
         x(i-n)= ergebnis(i);
     }
     for(int i = 0; i < n; i++){
         k(i)=ergebnis(i);
     }

     v = B.t() * k;


    return true;
}

void Cylinder::calcApproximation(QList<Point3D> points)
{

    this->nForm.x = 666;
    this->nForm.y = 666;
    this->nForm.alpha = 666;
    this->nForm.beta = 666;
    this->nForm.radius = 666;
}
