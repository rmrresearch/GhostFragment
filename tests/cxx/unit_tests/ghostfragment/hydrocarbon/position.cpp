#include "position.h"

float* position_carbon(float* source_coords, float carbon_bond, int num,
                       float angle_deg) {
    // Creates the pointer for positions
    float* coords = (float*)calloc(3, sizeof(float));
    // Convert degrees to radians
    float angle_rad = angle_deg * (3.14159265358979 / 180);

    // Sets the distance in each axis from the source coordinates
    // X: r*sin(theta)
    // Y: r*cos(theta)
    // Z: 0
    coords[0] = carbon_bond * sin(angle_rad / 2);
    coords[1] = carbon_bond * cos(angle_rad / 2);
    coords[2] = 0;

    // If the source atom is even, the new one must go up, otherwise,
    // it must go down
    coords[1] *= (num % 2 == 0) ? 1 : -1;

    for(int i = 0; i < 3; i++) { coords[i] += source_coords[i]; }

    return coords;
}

float* position_hydrogen(float* source_coords, int flag, int num,
                         float hydrogen_bond, float angle_deg) {
    // Creates the pointer for positions
    float* coords = (float*)calloc(3, sizeof(float));
    // Convert degrees to radians
    float angle_rad = angle_deg * (3.14159 / 180);

    // Because multiple hydrogen atoms get the same carbon atom, they need to be
    // defined by which place they are taking
    switch(flag) {
        // Goes behind the carbon (z is negative)
        case 0:
            // X: 0
            // Y: r*cos(theta)
            // Z: r*sin(theta)
            coords[0] = 0;
            coords[1] = hydrogen_bond * cos(angle_rad / 2);
            coords[2] = (-1) * hydrogen_bond * sin(angle_rad / 2);

            // If the carbon atom is odd, the hydrogen must be above, otherwise,
            // it must be below
            coords[1] *= (num % 2 == 0) ? -1 : 1;
            break;

        // Goes in front of the carbon (z is positive)
        case 1:
            // X: 0
            // Y: r*cos(theta)
            // Z: r*sin(theta)
            coords[0] = 0;
            coords[1] = hydrogen_bond * cos(angle_rad / 2);
            coords[2] = hydrogen_bond * sin(angle_rad / 2);

            // If the carbon atom is odd, the hydrogen must be above, otherwise,
            // it must be below
            coords[1] *= (num % 2 == 0) ? -1 : 1;
            break;

        // Goes to the left of the first carbon
        case 2:
            // X: r*sin(theta)
            // Y: r*cos(theta)
            // Z: 0
            coords[0] = (-1) * hydrogen_bond * sin(angle_rad / 2);
            coords[1] = hydrogen_bond * cos(angle_rad / 2);
            coords[2] = 0;
            break;

        // Goes to the right of the last carbon
        case 3:
            // X: r*sin(theta)
            // Y: r*cos(theta)
            // Z: 0
            coords[0] = hydrogen_bond * sin(angle_rad / 2);
            coords[1] = hydrogen_bond * cos(angle_rad / 2);
            coords[2] = 0;

            // If the last carbon is even, the hydrogen must be above,
            // otherwise, it must be below
            coords[1] *= (num % 2 == 0) ? 1 : -1;
            break;
    }

    for(int i = 0; i < 3; i++) { coords[i] += source_coords[i]; }

    return coords;
}
