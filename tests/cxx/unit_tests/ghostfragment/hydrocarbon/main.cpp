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
    int numCarbon;
    if(argc == 2) {
        numCarbon = stoi(argv[1]);
    } else {
        cout << "How many carbons would you like this molecule to have? ";
        cin >> numCarbon;
    }

    int numAtoms = numCarbon * 3 + 2;

    Atom* atoms = (Atom*)calloc(numAtoms, sizeof(Atom));

    int atomsCreated = 0;

    Atom source(atomsCreated, "C");
    atoms[atomsCreated] = source;
    atomsCreated++;

    for(; atomsCreated < numCarbon; atomsCreated++) {
        Atom a(atomsCreated, "C");
        positionCarbon(&a, (atoms + atomsCreated - 1), 1.53, 109.5);
        atoms[atomsCreated] = a;
    }

    for(int i = 0; i < numCarbon; i++) {
        Atom* c = atoms + i;
        if(i == 0 || i == numCarbon - 1) {
            Atom h(atomsCreated, "H");
            positionHydrogen(&h, c, 0, 1.09, 109.5);
            atoms[atomsCreated++] = h;
        }

        Atom h1(atomsCreated, "H");
        positionHydrogen(&h1, c, 1, 1.09, 109.5);
        atoms[atomsCreated++] = h1;

        Atom h2(atomsCreated, "H");
        positionHydrogen(&h2, c, -1, 1.09, 109.5);
        atoms[atomsCreated++] = h2;
    }

    printPositions("hydrocarbon.xyz", atoms, atomsCreated);

    return 0;
}
