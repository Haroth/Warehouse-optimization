#include <iostream>
#include "class.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

#define liczbaGeneracji 500
#define wielkoscPopulacji 50
#define wielkoscWybranych 15

using namespace std;

void generujPierwszaPopulacje(Magazyn* mag);
void sortuj(Magazyn* mag);
void wybierzRodzicow(Magazyn* wyb, Magazyn* pop);
void krzyzuj(Magazyn* pop, Magazyn* wyb);
void mutuj(Magazyn* pop);

int main()
{
    fstream plik;
    plik.open("populacja.txt", ios::out);
    plik.close();
    plik.open("wybrani.txt", ios::out);
    plik.close();
    plik.open("fitness.txt", ios::out);
    srand(time(NULL));
    Magazyn populacja[wielkoscPopulacji];
    Magazyn wybrani[wielkoscWybranych];
    generujPierwszaPopulacje(populacja);
    sortuj(populacja);

    for (int i=0; i<liczbaGeneracji; i++)
    {
        for (int j=0; j<wielkoscPopulacji; j++)
            populacja[j].zapisPlik(j, i, "populacja.txt");
        mutuj(populacja);
        sortuj(populacja);
        for (int j=0; j<wielkoscPopulacji; j++)
            populacja[j].zapisPlik(j, i, "zmutowani.txt");
        wybierzRodzicow(wybrani, populacja);
        for (int j=0; j<wielkoscWybranych; j++)
            wybrani[j].zapisPlik(j, i, "wybrani.txt");
        krzyzuj(populacja, wybrani);
        sortuj(populacja);
        plik << populacja[0].fitness << endl;
    }
    plik.close();

    return 0;
}


void generujPierwszaPopulacje(Magazyn* mag)
{
    for (int i=0; i<wielkoscPopulacji; i++)
    {
        mag[i].losuj();
        mag[i].ocena();
    }
}

void sortuj(Magazyn* mag)
{
    Magazyn posortowani[wielkoscPopulacji];
    int maxx=-2147483648;
    int pom;
    int flaga=0;
    int zakaz[wielkoscPopulacji];
    for (int i=0; i<wielkoscPopulacji; i++)
        zakaz[i]=wielkoscPopulacji;
    for (int k=0; k<wielkoscPopulacji; k++)
    {
        for (int i=0; i<wielkoscPopulacji; i++)
        {
            for (int j=0; j<wielkoscPopulacji; j++) //sprawdzenie czy nie jest zakazane
            {
                if (i==zakaz[j])
                    flaga=1;
            }
            if (mag[i].fitness>maxx && flaga==0)
            {
                maxx=mag[i].fitness;
                pom=i;
            }
            flaga=0;
        }
        maxx=-2147483648;
        zakaz[k]=pom;
        posortowani[k]=mag[pom];
    }
    for (int i=0; i<wielkoscPopulacji; i++)
        mag[i]=posortowani[i];
}

void wybierzRodzicow(Magazyn* wyb, Magazyn* pop)
{
    int szansa[wielkoscPopulacji];
    float a=-30/float(wielkoscPopulacji);
    for (int i=0; i<5; i++) // 100% dla pierwszych 4
        szansa[i]=100;
    for (int i=5; i<wielkoscPopulacji; i++) // od 80% do 50%
        szansa[i]=a*(i-5)+80;
    int zabron[wielkoscWybranych];
    for (int i=0; i<wielkoscWybranych; i++)
        zabron[i]=wielkoscPopulacji;

    int pom;
    int ilosc=0, flaga=0;
    while (ilosc<wielkoscWybranych)
    {
        for (int i=0; i<wielkoscPopulacji; i++)
        {
            for (int j=0; j<wielkoscWybranych; j++)
            {
                if (zabron[j]==i)
                    flaga=1;
            }
            pom=rand()%100;
            if (pom<szansa[i] && flaga==0 && ilosc<wielkoscWybranych)
            {
                wyb[ilosc]=pop[i];
                ilosc++;
                zabron[ilosc]=i;
            }
            flaga=0;
        }
    }
}

void krzyzuj(Magazyn* pop, Magazyn* wyb)
{
    int pom;
    int szansa[wielkoscWybranych];
    int srodek=100/wielkoscWybranych;
    srodek*=2;
    float a=(100-srodek)/float(wielkoscWybranych-1); //funkcja f(x)=ax+b, f(0)=srodek, f(wielkoscWybranych)=100
    for (int i=0; i<wielkoscWybranych; i++)
        szansa[i]=a*i+srodek;
    szansa[wielkoscWybranych-1]=100; //dla pewnosci
    for (int i=0; i<wielkoscPopulacji; i++)
    {
        for (int j=0; j<3; j++)
        {
            for (int k=0; k<12; k++)
            {
                pom=rand()%100;
                for (int l=0; l<wielkoscWybranych; l++)
                {
                    if (pom<szansa[l])
                    {
                        pom=l;
                        break;
                    }
                }
                pop[i].zakup[j][k]=wyb[pom].zakup[j][k];
            }
        }
        pop[i].ocena();
    }
}

void mutuj(Magazyn* pop)
{
    int szansa[wielkoscPopulacji];
    float a=25/float(wielkoscPopulacji-8);
    for (int i=0; i<8; i++)
        szansa[i]=0;
    for (int i=8; i<wielkoscPopulacji; i++)
        szansa[i]=a*(i-8)+75;
    int pom;
    for (int i=0; i<wielkoscPopulacji; i++)
    {
        pom=rand()%100;
        if (pom<szansa[i])
        {
            pom=rand();
            pop[i].zakup[pom%3][pom%12]=rand()%10;
            pop[i].ocena();
        }
    }
}

/*void mutuj(Magazyn* pop)
{
    int szansa[wielkoscPopulacji];
    float a=25/float(wielkoscPopulacji-8);
    for (int i=0; i<8; i++)
        szansa[i]=0;
    for (int i=8; i<wielkoscPopulacji; i++)
        szansa[i]=a*(i-8)+75;
    int pom, pom1, pom2, pom3;
    for (int i=0; i<wielkoscPopulacji; i++)
    {
        pom=rand()%100;
        if (pom<szansa[i])
        {
            pom1=rand()%3;
            pom2=rand()%12;
            pom3=pop[i].zakup[pom1][pom2];
            if (pom3>0)
            {
                pom=rand()%2;
                if (pom==0)
                    pop[i].zakup[pom1][pom2]++;
                else
                    pop[i].zakup[pom1][pom2]--;
            }
            else
                pop[i].zakup[pom1][pom2]++;
            pop[i].ocena();
        }
    }
}*/
