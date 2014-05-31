#include <QCoreApplication>
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

      mat A = randu<mat>(4,5);
      mat B = randu<mat>(4,5);

      vec c(3);
      c(0)=5;
      c(1)=4;
      c(2)=13;

      mat R=A*B.t();

      c.print();
      R.print();

    return a.exec();
}
