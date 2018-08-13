#include <iostream>

using namespace std;

class Magazyn
{
public:
    int s; // ilosc surowcow
    int n; // ilosc miesiecy
    int pojemnosc; // pojemnosc magazynu
    int fundusze;  // aktualne fundusze
    int kara;
    int fitness; // ocena jakosci
    int *objetosc; // objetosc surowcow (s)
    int *zuzycie;  // zuzycie surowcow (s)
    int *oplata;   // oplata za przechowywanie (s)
    int **cena;    // cena surowcow w kazdym miesiacu (s*n)
    int **zakup;   // tablica zakupow (s*n)
public:
    Magazyn(int s_=3, int n_=12, int pojemnosc_=5000, int fundusze_=30000);
    ~Magazyn();
    float znizka(int ilosc); // zwraca znizke w zaleznosci od ilosci kupionych surowcow
    void losuj(int rozbierznosc=10); // inicjuje tablice zakupów losowymi wartoœciami
    void ocena(int poj_kara=30, int fun_kara=30, int brak_kara=400); // dokonuje oceny osobnika. Stosuje funkcje kary, gdzie jej wartosc zalezy od wartosci argumentow.
    void wyswietl(); // wyswietla cala liste zakupow magazynu
    void zapisPlik(int numer, int generacja, const char* nazwa); // zapisuje liste zakupow magazynu do pliku
};


