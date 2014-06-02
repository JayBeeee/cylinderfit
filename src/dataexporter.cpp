#include "dataexporter.h"
#include <fstream>
#include <iomanip>
dataexporter::dataexporter()
{
    int len=10;
}

    int dataexporter::writefile()
    {
        ofstream  outfile;
        outfile.open("transform.dat");
        if (!outfile)
        {
            cout << "File open error."; return(-2);
        }
        outfile << "Dies ist das Ausgabeprotokoll zur Zylinderausgleichung.\n";
        outfile << "------------------------------------------------------\n\n";

        outfile<<"Ausgangswerte: \n\n\n";
        outfile<<"      x         y         z\n";

        int len=100;
        for (int i=0; i<len; i++)
        {
            outfile << fixed << setw(9) << setprecision(3) << x[i];
            outfile <<          setw(1) << " ";
            outfile << fixed << setw(9) << setprecision(3) << y[i];
            outfile <<          setw(1) << " ";
            outfile << fixed << setw(9) << setprecision(3) << z[i];
            outfile <<          setw(1) << "\n";
         }
        outfile << "------------------------------------------\n";


        outfile.close();
        return 0;


    }


