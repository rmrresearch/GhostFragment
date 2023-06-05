#include "position.h"

void createHydrocarbon(Atom* atoms, int numCarbon) {
    int atomsCreated = 0;

    Atom source(atomsCreated, "C");
    atoms[atomsCreated] = source;
    atomsCreated++;

    createCarbons(atoms, numCarbon, &atomsCreated, 1.53, 109.5);
    createHydrogens(atoms, numCarbon, &atomsCreated, 1.09, 109.5);
}

void createCarbons(Atom* atoms, int numCarbon, int* atomsCreated,
                   float carbonBond, float angleDeg) {
    for(; *atomsCreated < numCarbon; (*atomsCreated)++) {
        Atom a(*atomsCreated, "C");
        positionCarbon(&a, (atoms + (*atomsCreated) - 1), carbonBond, angleDeg);
        atoms[*atomsCreated] = a;
    }
}

void positionCarbon(Atom* newCarbon, Atom* sourceCarbon, float carbonBond,
                    float angleDeg) {
    // Convert degrees to radians
    float angleRad = angleDeg * (3.14159 / 180);

    // Sets the distance in the x-axis from the previous atom
    float xDistance = carbonBond * sin(angleRad / 2);
    xDistance += (*sourceCarbon).getX();
    (*newCarbon).setX(xDistance);

    // Sets the distance in the y-axis from the previous atom
    // Going up if the atom is even, or down otherwise
    float yDistance = carbonBond * cos(angleRad / 2);
    if((*sourceCarbon).getId() % 2 == 0)
        yDistance = (*sourceCarbon).getY() + yDistance;
    else
        yDistance = (*sourceCarbon).getY() - yDistance;
    (*newCarbon).setY(yDistance);
}

void createHydrogens(Atom* atoms, int numCarbon, int* atomsCreated,
                     float hydrogenBond, float angleDeg) {
    for(int i = 0; i < numCarbon; i++) {
        Atom* c = atoms + i;
        if(i == 0 || i == numCarbon - 1) {
            Atom h(*atomsCreated, "H");
            positionHydrogen(&h, c, 0, hydrogenBond, angleDeg);
            atoms[(*atomsCreated)++] = h;
        }

        Atom h1(*atomsCreated, "H");
        positionHydrogen(&h1, c, 1, hydrogenBond, angleDeg);
        atoms[(*atomsCreated)++] = h1;

        Atom h2(*atomsCreated, "H");
        positionHydrogen(&h2, c, -1, hydrogenBond, angleDeg);
        atoms[(*atomsCreated)++] = h2;
    }
}

void positionHydrogen(Atom* newHydrogen, Atom* sourceCarbon, int flag,
                      float hydrogenBond, float angleDeg) {
    // Sets the same X value as the carbon
    (*newHydrogen).setX((*sourceCarbon).getX());

    // Gets the distances for y and z axes
    float angleRad = angleDeg * (3.14159 / 180);
    float z        = hydrogenBond * sin(angleRad / 2);
    float y        = hydrogenBond * cos(angleRad / 2);

    // Because multiple hydrogen atoms get the same carbon atom, theyneed to be
    // defined by which place they are taking
    switch(flag) {
        // Goes behind the carbon
        case -1:
            z = (*sourceCarbon).getZ() - z;
            (*newHydrogen).setZ(z);

            if((*sourceCarbon).getId() % 2 == 0)
                y = (*sourceCarbon).getY() - y;
            else
                y = (*sourceCarbon).getY() + y;
            break;
        // Goes in front of the carbon
        case 1:
            z = (*sourceCarbon).getZ() + z;
            (*newHydrogen).setZ(z);

            if((*sourceCarbon).getId() % 2 == 0)
                y = (*sourceCarbon).getY() - y;
            else
                y = (*sourceCarbon).getY() + y;
            break;
        // Goes next to the carbon in the x-axis
        case 0:
            if((*sourceCarbon).getId() == 0) {
                z = (*sourceCarbon).getX() - z;
                y = (*sourceCarbon).getY() + y;
            } else {
                z = (*sourceCarbon).getX() + z;
                y = (*sourceCarbon).getY() - y;
            }
            (*newHydrogen).setX(z);
            break;
    }
    (*newHydrogen).setY(y);
}
