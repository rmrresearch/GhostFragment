#include"position.h"

void createHydrocarbon(Atom *atoms, int numCarbon){
	int atomsCreated = 0;

	Atom source(atomsCreated, "C");
        atoms[atomsCreated] = source;
        atomsCreated++;

	createCarbons(atoms, numCarbon, &atomsCreated);
	createHydrogens(atoms, numCarbon, &atomsCreated);
}

void createCarbons(Atom *atoms, int numCarbon, int *atomsCreated){
	for(; *atomsCreated < numCarbon; (*atomsCreated)++){
                Atom a(*atomsCreated, "C");
                positionCarbon(&a, (atoms + (*atomsCreated) - 1), 1.53, 109.5);
                atoms[*atomsCreated] = a;
        }
}

void positionCarbon(Atom *c, Atom *source, float r, float theta){
	//Convert degrees to radians
	float rad = theta * (3.14159/180);

	//Sets the distance in the x-axis from the previous atom
	float x = r * sin(rad/2);
	x += (*source).getX();
	(*c).setX(x);

	//Sets the distance in the y-axis from the previous atom
	//Going up if the atom is even, or down otherwise
	float y = r * cos(rad/2);
	if((*source).getId() % 2 == 0)
		y = (*source).getY() + y;
	else
		y = (*source).getY() - y;
	(*c).setY(y);
}

void createHydrogens(Atom *atoms, int numCarbon, int *atomsCreated){
	for(int i = 0; i < numCarbon; i++){
                Atom *c = atoms+i;
                if(i == 0 || i == numCarbon-1){
                        Atom h(*atomsCreated, "H");
                        positionHydrogen(&h, c, 0, 1.09, 109.5);
                        atoms[(*atomsCreated)++] = h;
                }

                Atom h1(*atomsCreated, "H");
                positionHydrogen(&h1, c, 1, 1.09, 109.5);
                atoms[(*atomsCreated)++] = h1;

                Atom h2(*atomsCreated, "H");
                positionHydrogen(&h2, c, -1, 1.09, 109.5);
                atoms[(*atomsCreated)++] = h2;
        }
}

void positionHydrogen(Atom *h, Atom *source, int pos, float r, float theta){
	//Sets the same X value as the carbon
	(*h).setX((*source).getX());

	//Gets the distances for y and z axes
	float rad = theta * (3.14159/180);
	float z = r * sin(rad/2);
	float y = r * cos(rad/2);
	
	//Because multiple hydrogen atoms get the same carbon atom, theyneed to be defined by which place they are taking
	switch(pos){
		//Goes behind the carbon
		case -1:
			z = (*source).getZ() - z;
			(*h).setZ(z);

			if((*source).getId() % 2 == 0)
				y = (*source).getY() - y;
			else
				y = (*source).getY() + y;
			break;
		//Goes in front of the carbon
		case 1:
			z = (*source).getZ() + z;
			(*h).setZ(z);

			if((*source).getId() % 2 == 0)
                                y = (*source).getY() - y;
                        else
                                y = (*source).getY() + y;
			break;
		//End hydrogen. Z axis actually becomes X axis
		case 0:
			if((*source).getId() == 0){
				z = (*source).getX() - z;
				y = (*source).getY() + y;
			}
			else{
				z = (*source).getX() + z;
                                y = (*source).getY() - y;
			}
			(*h).setX(z);
			break;
	}
	(*h).setY(y);
}
