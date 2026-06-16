#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Filmas {
    string pavadinimas;
    string rezisierius;
    int metai;
    string zanras;
    double ivertinimas;
    int trukme;
};

const int MAX = 100;
Filmas filmai[MAX];
int kiekis = 0;

void nuskaityti() {
    ifstream failas("filmai.txt");
    if (!failas) { cout << "filmai.txt nerastas!\n"; return; }
    string eil;
    while (getline(failas, eil) && kiekis < MAX) {
        if (eil.empty()) continue;
        Filmas fi;
        string d = "";
        int st = 0;
        for (int i = 0; i <= (int)eil.size(); i++) {
            if (i == (int)eil.size() || eil[i] == ';') {
                if (st == 0) fi.pavadinimas = d;
                else if (st == 1) fi.rezisierius = d;
                else if (st == 2) fi.metai = stoi(d);
                else if (st == 3) fi.zanras = d;
                else if (st == 4) fi.ivertinimas = stod(d);
                else if (st == 5) fi.trukme = stoi(d);
                d = ""; st++;
            } else d += eil[i];
        }
        filmai[kiekis++] = fi;
    }
    failas.close();
}

void issaugoti() {
    ofstream f("filmai.txt");
    for (int i = 0; i < kiekis; i++)
        f << filmai[i].pavadinimas << ";" << filmai[i].rezisierius << ";"
          << filmai[i].metai << ";" << filmai[i].zanras << ";"
          << filmai[i].ivertinimas << ";" << filmai[i].trukme << "\n";
    f.close();
}

void spausdinti(Filmas arr[], int n) {
    if (n == 0) { cout << "Nera filmu.\n"; return; }
    cout << "\n" << left << setw(4) << "Nr." << setw(40) << "Pavadinimas"
         << setw(22) << "Rezisierius" << setw(6) << "Metai"
         << setw(22) << "Zanras" << setw(7) << "Ivert." << "Trukme\n"
         << string(110, '-') << "\n";
    for (int i = 0; i < n; i++)
        cout << left << setw(4) << i+1 << setw(40) << arr[i].pavadinimas
             << setw(22) << arr[i].rezisierius << setw(6) << arr[i].metai
             << setw(22) << arr[i].zanras << setw(7) << arr[i].ivertinimas
             << arr[i].trukme << " min\n";
    cout << "\n";
}

void prideti() {
    if (kiekis >= MAX) { cout << "Katalogas pilnas!\n"; return; }
    Filmas fi;
    cin.ignore();
    cout << "Pavadinimas: "; getline(cin, fi.pavadinimas);
    cout << "Rezisierius: "; getline(cin, fi.rezisierius);
    cout << "Metai: "; cin >> fi.metai; cin.ignore();
    cout << "Zanras: "; getline(cin, fi.zanras);
    cout << "Ivertinimas (0.0-10.0): "; cin >> fi.ivertinimas;
    cout << "Trukme (min): "; cin >> fi.trukme;
    filmai[kiekis++] = fi;
    issaugoti();
    cout << "Filmas pridetas!\n";
}

void redaguoti() {
    spausdinti(filmai, kiekis);
    cout << "Filmo numeris: ";
    int nr; cin >> nr;
    if (nr < 1 || nr > kiekis) { cout << "Neteisingas numeris.\n"; return; }
    Filmas& fi = filmai[nr - 1];
    cin.ignore();
    string l;
    cout << "Pavadinimas [" << fi.pavadinimas << "]: "; getline(cin, l); if (!l.empty()) fi.pavadinimas = l;
    cout << "Rezisierius [" << fi.rezisierius << "]: "; getline(cin, l); if (!l.empty()) fi.rezisierius = l;
    cout << "Metai [" << fi.metai << "]: "; getline(cin, l); if (!l.empty()) fi.metai = stoi(l);
    cout << "Zanras [" << fi.zanras << "]: "; getline(cin, l); if (!l.empty()) fi.zanras = l;
    cout << "Ivertinimas [" << fi.ivertinimas << "]: "; getline(cin, l); if (!l.empty()) fi.ivertinimas = stod(l);
    cout << "Trukme [" << fi.trukme << "]: "; getline(cin, l); if (!l.empty()) fi.trukme = stoi(l);
    issaugoti();
    cout << "Atnaujinta!\n";
}

void trinti() {
    spausdinti(filmai, kiekis);
    cout << "Filmo numeris: ";
    int nr; cin >> nr;
    if (nr < 1 || nr > kiekis) { cout << "Neteisingas numeris.\n"; return; }
    cout << "Trinti \"" << filmai[nr-1].pavadinimas << "\"? (1 - taip, 2 - ne): ";
    int p; cin >> p;
    if (p == 1) {
        for (int i = nr - 1; i < kiekis - 1; i++) filmai[i] = filmai[i+1];
        kiekis--;
        issaugoti();
        cout << "Istrintas!\n";
    } else cout << "Atsaukta.\n";
}

void rikiuoti() {
    cout << "1. Pavadinimas (A-Z)\n2. Metai (naujausi)\n3. Ivertinimas\n4. Trukme\nPasirinkimas: ";
    int p; cin >> p;
    if (p < 1 || p > 4) { cout << "Neteisingas pasirinkimas.\n"; return; }
    for (int i = 0; i < kiekis - 1; i++)
        for (int j = 0; j < kiekis - i - 1; j++) {
            Filmas tmp = filmai[j];
            if (p == 1 && filmai[j].pavadinimas > filmai[j+1].pavadinimas)
            { filmai[j] = filmai[j+1]; filmai[j+1] = tmp; }
            else if (p == 2 && filmai[j].metai < filmai[j+1].metai)
            { filmai[j] = filmai[j+1]; filmai[j+1] = tmp; }
            else if (p == 3 && filmai[j].ivertinimas < filmai[j+1].ivertinimas)
            { filmai[j] = filmai[j+1]; filmai[j+1] = tmp; }
            else if (p == 4 && filmai[j].trukme < filmai[j+1].trukme)
            { filmai[j] = filmai[j+1]; filmai[j+1] = tmp; }
        }
    spausdinti(filmai, kiekis);
}

void filtruoti() {
    cout << "1. Pagal zanra\n2. Pagal metus (nuo-iki)\n3. Pagal min. ivertinima\nPasirinkimas: ";
    int p; cin >> p;
    Filmas rez[MAX]; int n = 0;
    if (p == 1) {
        cin.ignore(); string z; cout << "Zanras: "; getline(cin, z);
        for (int i = 0; i < kiekis; i++)
            if (filmai[i].zanras.find(z) != string::npos) rez[n++] = filmai[i];
    } else if (p == 2) {
        int nuo, iki; cout << "Nuo: "; cin >> nuo; cout << "Iki: "; cin >> iki;
        for (int i = 0; i < kiekis; i++)
            if (filmai[i].metai >= nuo && filmai[i].metai <= iki) rez[n++] = filmai[i];
    } else if (p == 3) {
        double min; cout << "Min. ivertinimas: "; cin >> min;
        for (int i = 0; i < kiekis; i++)
            if (filmai[i].ivertinimas >= min) rez[n++] = filmai[i];
    } else { cout << "Neteisingas pasirinkimas.\n"; return; }
    spausdinti(rez, n);
}

int main() {
    nuskaityti();
    cout << "Nuskaityti " << kiekis << " filmai.\n";
    int pasirinkimas;
    do {
        cout << "\n=== FILMU KATALOGAS ===\n"
             << "1. Rodyti visus\n2. Prideti\n3. Redaguoti\n"
             << "4. Istrinti\n5. Rikiuoti\n6. Filtruoti\n0. Iseiti\n"
             << "Pasirinkimas: ";
        cin >> pasirinkimas;
        switch (pasirinkimas) {
            case 1: spausdinti(filmai, kiekis); break;
            case 2: prideti(); break;
            case 3: redaguoti(); break;
            case 4: trinti(); break;
            case 5: rikiuoti(); break;
            case 6: filtruoti(); break;
            case 0: cout << "Iki pasimatymo!\n"; break;
            default: cout << "Neteisingas pasirinkimas.\n";
        }
    } while (pasirinkimas != 0);
    return 0;
}
