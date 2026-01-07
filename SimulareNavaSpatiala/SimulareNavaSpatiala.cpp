#include "NavaSpatiala.h"
#include <fstream>
#include <ctime>
#include <cstdlib>

int Inginer::contorIngineri = 0;
int Medic::contorMedici = 0;

NavaSpatiala::NavaSpatiala(string n) : nume(n), combustibil(100), hrana(60), planeteVizitate(0), AvariiNava(false) {
    echipaj.push_back(new Capitan("Comandant"));
}

NavaSpatiala::~NavaSpatiala() {
    for (auto m : echipaj) delete m;
}

void NavaSpatiala::incarcaDinFisier(string numeFisier) {
    ifstream f(numeFisier);
    if (!f.is_open()) return;
    int nI, nM;
    f >> nume >> combustibil >> hrana >> planeteVizitate >> nI >> nM;
    if (nI > 3) nI = 3;

    for (auto m : echipaj) delete m;
    echipaj.clear();
    Inginer::contorIngineri = 0; Medic::contorMedici = 0;
    echipaj.push_back(new Capitan("Comandant"));
    for (int i = 0; i < nI; i++) echipaj.push_back(new Inginer());
    for (int i = 0; i < nM; i++) echipaj.push_back(new Medic());
    f.close();
}

void NavaSpatiala::viziteazaPlaneta() {
    if (AvariiNava) {
        cout << "\n[EROARE] Nava este avariata! Reparati structura (3) inainte de salt." << endl;
        return;
    }

    cout << "\n========== PLANETA " << planeteVizitate + 1 << " ==========" << endl;

    // Avertismente retragere
    for (auto m : echipaj) {
        if (m->getPlaneteRamase() == 2) cout << "[AVERTISMENT] " << m->getNume() << " pleaca dupa vizita viitoare!" << endl;
        if (m->getPlaneteRamase() == 1) cout << "[ATENTIE] " << m->getNume() << " este la ultima vizita!" << endl;
    }

    planeteVizitate++;
    combustibil -= 20;

    // Resurse: Hrana (0-35), Combustibil (0-35)
    int hGasita = rand() % 36;
    int cGasit = rand() % 36;

    hrana += hGasita;
    combustibil += cGasit;

    cout << "[RESURSE] Echipajul a descoperit " << hGasita << " hrana." << endl;
    cout << "[RESURSE] Echipajul a descoperit " << cGasit << " combustibil." << endl;

    // CORECTIE: Am folosit consumE peste tot pentru a evita eroarea consumH
    int consumE = (int)echipaj.size() * 4;
    hrana -= consumE;
    cout << "[LOG] Consum hrana echipaj: -" << consumE << "." << endl;

    if (planeteVizitate % 4 == 0) {
        AvariiNava = true;
        cout << "[ALERTA] Nava s-a avariat la aterizare!" << endl;
    }

    // Evolutie personal si Sacrificiu Medic
    bool areCap = false; int nIng = 0, nMed = 0;
    for (int i = 0; i < (int)echipaj.size(); ) {
        echipaj[i]->scadeDurata();
        if (!echipaj[i]->esteActiv()) {
            cout << "[-] RETRAS: " << echipaj[i]->getNume() << endl;
            delete echipaj[i];
            echipaj.erase(echipaj.begin() + i);
        }
        else {
            if (echipaj[i]->getRol() == "Capitan") areCap = true;
            if (echipaj[i]->getRol() == "Inginer") nIng++;
            if (echipaj[i]->getRol() == "Medic") nMed++;
            i++;
        }
    }

    if (nIng == 0 && nMed > 0) {
        cout << "[SACRIFICIU] Un medic s-a sacrificat pentru un Inginer!" << endl;
        for (int i = 0; i < (int)echipaj.size(); i++) {
            if (echipaj[i]->getRol() == "Medic") {
                delete echipaj[i];
                echipaj.erase(echipaj.begin() + i);
                break;
            }
        }
        echipaj.push_back(new Inginer());
        nIng = 1;
    }

    if (!areCap && nIng > 0) {
        for (auto m : echipaj) if (m->getRol() == "Inginer") { m->promoveazaLaCapitan(); break; }
    }

    // Recrutare (max 3 ingineri)
    if (rand() % 100 < 25) {
        if (rand() % 2 == 0 && nIng < 3) {
            echipaj.push_back(new Inginer());
            cout << "[EVENIMENT] Inginer nou gasit!" << endl;
        }
        else if (nMed < 3) {
            echipaj.push_back(new Medic());
            cout << "[EVENIMENT] Medic nou gasit!" << endl;
        }
    }
}

void NavaSpatiala::reparatii() {
    if (AvariiNava) {
        int nI = 0;
        for (auto m : echipaj) if (m->getRol() == "Inginer") nI++;
        if (nI > 0) { AvariiNava = false; cout << "[OK] Reparatii finalizate." << endl; }
        else cout << "[EROARE] Nu aveti ingineri pentru reparatii!" << endl;
    }
}

void NavaSpatiala::afisareEchipaj() {
    cout << "\n--- LISTA ECHIPAJ ---" << endl;
    for (auto m : echipaj) { m->afisare(); cout << endl; }
}

bool NavaSpatiala::verificaGameOver() {
    bool areCap = false; int nI = 0;
    for (auto m : echipaj) {
        if (m->getRol() == "Capitan") areCap = true;
        if (m->getRol() == "Inginer") nI++;
    }
    if (combustibil <= 0 || hrana <= 0) return true;
    if (!areCap && nI == 0) return true;
    return false;
}

ostream& operator<<(ostream& os, const NavaSpatiala& nava) {
    os << "\nNAVA: " << nava.nume << " | C: " << (int)nava.combustibil << " | H: " << nava.hrana << " | Avarii: " << (nava.AvariiNava ? "DA" : "NU");
    return os;
}