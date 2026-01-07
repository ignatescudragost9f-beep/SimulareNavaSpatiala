#include "NavaSpatiala.h"

int main() {
    srand((unsigned int)time(0));
    NavaSpatiala nava("Explorator");
    int opt;

    do {
        cout << nava;
        cout << "\n1. Salt Planeta | 2. Personal | 3. Reparatii | 4. Incarca Fisier | 0. Exit\nOptiune: ";
        cin >> opt;
        if (opt == 1) nava.viziteazaPlaneta();
        else if (opt == 2) nava.afisareEchipaj();
        else if (opt == 3) nava.reparatii();
        else if (opt == 4) nava.incarcaDinFisier("date_nava.txt");

        if (nava.verificaGameOver()) break;
    } while (opt != 0);

    return 0;
}