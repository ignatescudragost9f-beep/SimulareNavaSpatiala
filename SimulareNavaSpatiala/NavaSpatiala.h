#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "MembruEchipaj.h"
#include "Depozit.h"

using namespace std;

class NavaSpatiala {
private:
    string nume;
    double combustibil;
    int hrana;
    int planeteVizitate;
    bool AvariiNava;
    vector<MembruEchipaj*> echipaj;
    DepozitSpecial<string> cala;

public:
    NavaSpatiala(string n);
    ~NavaSpatiala(); // Previne eroarea LNK2019

    void incarcaDinFisier(string numeFisier);
    void reparatii();
    void viziteazaPlaneta();
    bool verificaGameOver(); // Previne eroarea VCR001
    void afisareEchipaj();

    // Operatorul de afisare
    friend ostream& operator<<(ostream& os, const NavaSpatiala& nava);
};