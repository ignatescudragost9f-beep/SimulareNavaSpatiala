#pragma once
#include <iostream>
#include <string>

using namespace std;

class MembruEchipaj {
protected:
    string nume;
    string rol;
    int planeteRamase;
public:
    MembruEchipaj(string n, string r, int p) : nume(n), rol(r), planeteRamase(p) {}
    virtual ~MembruEchipaj() {}

    bool esteActiv() { return planeteRamase > 0; }
    void scadeDurata() { planeteRamase--; }
    string getRol() { return rol; }
    string getNume() { return nume; }
    int getPlaneteRamase() { return planeteRamase; }

    void promoveazaLaCapitan() {
        rol = "Capitan";
        planeteRamase = 15;
        cout << "\n[SISTEM] " << nume << " a preluat comanda!" << endl;
    }

    virtual void afisare() {
        cout << "[" << rol << "] " << nume << " | Rezistenta: " << planeteRamase << " planete";
    }
};

class Capitan : public MembruEchipaj {
public: Capitan(string n) : MembruEchipaj(n, "Capitan", 15) {}
};

class Inginer : public MembruEchipaj {
public:
    static int contorIngineri;
    Inginer() : MembruEchipaj("Inginer " + to_string(++contorIngineri), "Inginer", 6) {}
};

class Medic : public MembruEchipaj {
public:
    static int contorMedici;
    Medic() : MembruEchipaj("Medic " + to_string(++contorMedici), "Medic", 8) {}
};