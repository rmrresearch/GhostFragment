#include"atom.h"
#include<math.h>

void createHydrocarbon(Atom *atoms, int numCarbon);

void createCarbons(Atom *atoms, int numCarbon, int *atomsCreated);

void positionCarbon(Atom *c, Atom *source, float r, float theta);

void createHydrogens(Atom *atoms, int numCarbon, int *atomsCreated);

void positionHydrogen(Atom *h, Atom *source, int pos, float r, float theta);
