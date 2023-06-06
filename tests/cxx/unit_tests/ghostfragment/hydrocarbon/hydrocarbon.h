#include <cstdlib>
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

Molecule hydrocarbon(int num_carbon);