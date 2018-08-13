#include "class.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <fstream>

void Magazyn::losuj(int rozbierznosc)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<s; j++)
        {
            zakup[j][i]=rand()%rozbierznosc;
        }
    }
}


void Magazyn::ocena(int poj_kara, int fun_kara, int brak_kara)
{
    int sur[3]={0,0,0};
    int wydane=0;
    int zajete;
    fundusze=30000;
    kara=0;
    for (int i=0; i<n; i++)
    {
        zajete=0;
        for (int j=0; j<s; j++)
        {

            sur[j]+=zakup[j][i];
            if (sur[j]>=0)
            {
                wydane+=zakup[j][i]*cena[j][i]*znizka(zakup[j][i])+sur[j]*oplata[j];
                zajete+=sur[j]*objetosc[j];
            }
            else
            {
                wydane+=zakup[j][i]*cena[j][i]*znizka(zakup[j][i]);

            }
            sur[j]-=zuzycie[j];
            if (sur[j]<0)
                kara-=sur[j]*brak_kara; // - bo sur ujemne
        }
        if (zajete>pojemnosc)
            kara+=(zajete-pojemnosc)*poj_kara;
    }

    if (wydane>fundusze)
        kara+=(wydane-fundusze)*fun_kara;
    fundusze=fundusze-wydane;
    fitness=fundusze-kara;
}


float Magazyn::znizka(int ilosc)
{
    return (pow(2.718, -1.609*ilosc)+0.8); // e^ - f(1)=1, f(10)=0.8
}


void Magazyn::wyswietl()
{
    for (int i=0; i<s; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout << "[" << zakup[i][j] << "] ";
        }
        cout << endl;
    }
    cout << "Fundusze: " << fundusze << endl;
    cout << "Kara: " << kara << endl;
    cout << "Fitness: " << fitness << endl;
}


void Magazyn::zapisPlik(int numer, int generacja, const char* nazwa)
{
    fstream plik;
    plik.open(nazwa, ios::out | ios::app);
    if( plik.good() == true )
    {
        if (numer==0)
            plik << "-------------------GENERACJA " << generacja+1 << " ----------------------------" << endl;
        plik << numer+1 << "." << endl;
        for (int i=0; i<s; i++)
        {
            for (int j=0; j<n; j++)
            {
                plik << "[" << zakup[i][j] << "] ";
            }
            plik << endl;
        }
        plik << "Fundusze: " << fundusze << endl;
        plik << "Kara: " << kara << endl;
        plik << "Fitness: " << fitness << endl << endl;
        plik.close();
    }
}


Magazyn::Magazyn(int s_, int n_, int pojemnosc_, int fundusze_) : s(s_), n(n_), pojemnosc(pojemnosc_), fundusze(fundusze_), fitness(0), kara(0)
{
    int cena_[3][12]=
    {
        {100, 80, 70, 65, 80, 90, 110, 140, 135, 120, 120, 105},
        {350, 370, 360, 340, 320, 350, 345, 320, 350, 330, 310, 310},
        {200, 180, 195, 210, 220, 200, 170, 180, 210, 225, 215, 200}
    };
    int objetosc_[3]={50, 10, 25};
    int zuzycie_[3]={6, 2, 3};
    int oplata_[3]={10, 30, 20};


    objetosc=new int[s];
    zuzycie=new int[s];
    oplata=new int[s];
    zakup=new int*[s];
    cena=new int*[s];
    for (int i=0; i<s; i++)
    {
        zakup[i]=new int[n];
        cena[i]=new int[n];
    }
    for (int i=0; i<s; i++)
    {
        for (int j=0; j<n; j++)
        {
            cena[i][j]=cena_[i][j];
            zakup[i][j]=0;
        }
    }
    for (int i=0; i<s; i++)
    {
        objetosc[i]=objetosc_[i];
        zuzycie[i]=zuzycie_[i];
        oplata[i]=oplata_[i];
    }
}

 Magazyn::~Magazyn()
 {

 }


// ---------------------------------------------------------------------------------------




