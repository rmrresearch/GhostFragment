#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "atom.h"
#include "position.h"
#include "xyzWrite.h"

using namespace std;

int main(int argc, char* argv[]) {
    int num_carbon;
    if(argc == 2) {
        num_carbon = stoi(argv[1]);
    } else {
        cout << "How many carbons would you like this molecule to have? ";
        cin >> num_carbon;
    }

    int num_atoms = num_carbon * 3 + 2;

    Atom* atoms = (Atom*)calloc(num_atoms, sizeof(Atom));

    int atoms_created = 0;

    Atom source(atoms_created, "C");
    atoms[atoms_created] = source;
    atoms_created++;

    for(; atoms_created < num_carbon; atoms_created++) {
        Atom a(atoms_created, "C");
        position_carbon(&a, (atoms + atoms_created - 1), 1.53, 109.5);
        atoms[atoms_created] = a;
    }

    for(int i = 0; i < num_carbon; i++) {
        Atom* c = atoms + i;
        if(i == 0 || i == num_carbon - 1) {
            Atom h(atoms_created, "H");
            position_hydrogen(&h, c, 0, 1.09, 109.5);
            atoms[atoms_created++] = h;
        }

        Atom h1(atoms_created, "H");
        position_hydrogen(&h1, c, 1, 1.09, 109.5);
        atoms[atoms_created++] = h1;

        Atom h2(atoms_created, "H");
        position_hydrogen(&h2, c, -1, 1.09, 109.5);
        atoms[atoms_created++] = h2;
    }

    printPositions("hydrocarbon.xyz", atoms, atoms_created);

    return 0;
}
