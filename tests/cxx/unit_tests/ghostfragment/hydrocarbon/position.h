#include "atom.h"
#include <math.h>

void create_hydrocarbon(Atom* atoms, int num_carbon);

void create_carbons(Atom* atoms, int num_carbon, int* atoms_created,
                    float carbon_bond, float angle_deg);

void position_carbon(Atom* new_carbon, Atom* source_carbon, float carbon_bond,
                     float angle_deg);

void create_hydrogens(Atom* atoms, int num_carbon, int* atoms_created,
                      float hydrogen_bond, float angle_deg);

void position_hydrogen(Atom* h, Atom* source, int pos, float hydrogen_bond,
                       float angle_deg);
