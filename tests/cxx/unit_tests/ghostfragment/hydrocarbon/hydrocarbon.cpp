#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

//#include "atom.h"
#include "position.h"
//#include "xyzWrite.h"

#include <chemist/molecule/atom.hpp>
#include <chemist/molecule/molecule.hpp>

#define C_C_BOND 1.53
#define H_C_BOND 1.09
#define ANGLE 109.5

#define C_MASS 21874.662
#define H_MASS 1837.289
#define C_NPROTON 6
#define H_NPROTON 1

using namespace chemist;

Molecule hydrocarbon(int num_carbon) {
    Molecule m;

    int num_atoms = num_carbon * 3 + 2;

    // A log of all carbon atom positions.
    // Used to determine the position of the next carbon and connected hydrogens
    float* source_coords = (float*)calloc(num_carbon * 3, sizeof(float));

    // The first carbon atom positioned at {0, 0, 0}
    m.push_back(Atom("C", C_NPROTON, C_MASS, 0, 0, 0));

    // Positions each of the following carbon atoms
    for(int i = 0; i < num_carbon; i++) {
        // Finds the new coordinates using the previous ones
        float* coords =
          position_carbon(source_coords + (3 + i), C_C_BOND, i, ANGLE);

        // Adds the new atom
        m.push_back(
          Atom("C", C_NPROTON, C_MASS, coords[0], coords[1], coords[2]));

        // Logs the new atoms coordinates
        for(int j = 0; j < 3; j++) { source_coords[(3 * i) + j] = coords[j]; }
    }

    //Positions each connected hydrogen atom
    for(int i = 0; i < num_carbon; i++) {
        //Will skip a side hydrogen if carbon is one of the middle ones
        //If the carbon atom is the first or last, 
        //it must not skip the side hydrogen
        int step = (i == 0 || i == num_carbon-1) ? 1 : 2;

        //Creates each hydrogen necessary
        for(int h = 1; h >= -1; h -= step){
            // Finds the new coordinates using the previous ones
            float* coords =
            position_hydrogen(source_coords + (3 + i), h, H_C_BOND, i, ANGLE);

            // Adds the new atom
            m.push_back(
            Atom("H", H_NPROTON, H_MASS, coords[0], coords[1], coords[2]));
        }
    }

    return m;
}
