#include "position.h"

void create_hydrocarbon(Atom* atoms, int num_carbon) {
    int atoms_created = 0;

    Atom source(atoms_created, "C");
    atoms[atoms_created] = source;
    atoms_created++;

    create_carbons(atoms, num_carbon, &atoms_created, 1.53, 109.5);
    create_hydrogens(atoms, num_carbon, &atoms_created, 1.09, 109.5);
}

void create_carbons(Atom* atoms, int num_carbon, int* atoms_created,
                   float carbon_bond, float angle_deg) {
    for(; *atoms_created < num_carbon; (*atoms_created)++) {
        Atom a(*atoms_created, "C");
        position_carbon(&a, (atoms + (*atoms_created) - 1), carbon_bond, angle_deg);
        atoms[*atoms_created] = a;
    }
}

void position_carbon(Atom* new_carbon, Atom* source_carbon, float carbon_bond,
                    float angle_deg) {
    // Convert degrees to radians
    float angle_rad = angle_deg * (3.14159 / 180);

    // Sets the distance in the x-axis from the previous atom
    float x_distance = carbon_bond * sin(angle_rad / 2);
    x_distance += (*source_carbon).get_x();
    (*new_carbon).set_x(x_distance);

    // Sets the distance in the y-axis from the previous atom
    // Going up if the atom is even, or down otherwise
    float y_distance = carbon_bond * cos(angle_rad / 2);
    if((*source_carbon).get_id() % 2 == 0)
        y_distance = (*source_carbon).get_y() + y_distance;
    else
        y_distance = (*source_carbon).get_y() - y_distance;
    (*new_carbon).set_y(y_distance);
}

void create_hydrogens(Atom* atoms, int num_carbon, int* atoms_created,
                     float hydrogen_bond, float angle_deg) {
    for(int i = 0; i < num_carbon; i++) {
        Atom* c = atoms + i;
        if(i == 0 || i == num_carbon - 1) {
            Atom h(*atoms_created, "H");
            position_hydrogen(&h, c, 0, hydrogen_bond, angle_deg);
            atoms[(*atoms_created)++] = h;
        }

        Atom h1(*atoms_created, "H");
        position_hydrogen(&h1, c, 1, hydrogen_bond, angle_deg);
        atoms[(*atoms_created)++] = h1;

        Atom h2(*atoms_created, "H");
        position_hydrogen(&h2, c, -1, hydrogen_bond, angle_deg);
        atoms[(*atoms_created)++] = h2;
    }
}

void position_hydrogen(Atom* new_hydrogen, Atom* source_carbon, int flag,
                      float hydrogen_bond, float angle_deg) {
    // Sets the same X value as the carbon
    (*new_hydrogen).set_x((*source_carbon).get_x());

    // Gets the distances for y and z axes
    float angle_rad = angle_deg * (3.14159 / 180);
    float z        = hydrogen_bond * sin(angle_rad / 2);
    float y        = hydrogen_bond * cos(angle_rad / 2);

    // Because multiple hydrogen atoms get the same carbon atom, theyneed to be
    // defined by which place they are taking
    switch(flag) {
        // Goes behind the carbon
        case -1:
            z = (*source_carbon).get_z() - z;
            (*new_hydrogen).set_z(z);

            if((*source_carbon).get_id() % 2 == 0)
                y = (*source_carbon).get_y() - y;
            else
                y = (*source_carbon).get_y() + y;
            break;
        // Goes in front of the carbon
        case 1:
            z = (*source_carbon).get_z() + z;
            (*new_hydrogen).set_z(z);

            if((*source_carbon).get_id() % 2 == 0)
                y = (*source_carbon).get_y() - y;
            else
                y = (*source_carbon).get_y() + y;
            break;
        // Goes next to the carbon in the x-axis
        case 0:
            if((*source_carbon).get_id() == 0) {
                z = (*source_carbon).get_x() - z;
                y = (*source_carbon).get_y() + y;
            } else {
                z = (*source_carbon).get_x() + z;
                y = (*source_carbon).get_y() - y;
            }
            (*new_hydrogen).set_x(z);
            break;
    }
    (*new_hydrogen).set_y(y);
}
