#include "hydrocarbon.hpp"
#include <simde/simde.hpp>

namespace ghostfragment::hydrocarbon {

using n_type = unsigned short;

const auto mod_desc = R"(
Hydrocarbon Chain Generator
___________________________

This module generates carbon chains of given "n"

)";

MODULE_CTOR(hydrocarbon) {
    description(mod_desc);
    satisfies_property_type<simde::MoleculeFromString>

    // Inputs/modules controlling
    add_input<n_type>("n").set_default(n_type(1));
}

MODULE_RUN(hydrocarbon) {
    auto num_carbon = inputs.at("n").value<n_type>();
	chemist::Molecule hydrocarbon(int num_carbon);
    	chemist::Molecule m;

    	// A log of all carbon atom positions.
    	// Used to determine the position of the next carbon and connected hydrogens
    	std::vector<float> source_coords{0.0, 0.0, 0.0};
    	source_coords.reserve(num_carbon * 3);

    	// The first carbon atom positioned at {0, 0, 0}
    	m.push_back(chemist::Atom("C", C_NPROTON, C_MASS, 0, 0, 0));

    	// Positions each of the following carbon atoms
    	for(int i = 1; i < num_carbon; i++) {
        	// Finds the new coordinates using the previous ones
        	std::array<float, 3> coords = position_carbon(source_coords, C_C_BOND, i - 1, ANGLE);

        	// Adds the new atom
        	m.push_back(chemist::Atom("C", C_NPROTON, C_MASS, coords[0], coords[1], coords[2]));

        	// Logs the new atoms coordinates
        	for(int j = 0; j < 3; j++) { source_coords[(3 * i) + j] = coords[j]; }
    	}

    	// Positions each connected hydrogen atom
    	for(int i = 0; i < num_carbon; i++) {
            // Creates the first hydrogen in the chain
            if(i == 0) {
                // Finds the coordinates using the carbon
                std::array<float, 3> coords = position_hydrogen(source_coords, 2, i, H_C_BOND, ANGLE);

                // Adds the new atom
                m.push_back(chemist::Atom("H", H_NPROTON, H_MASS, coords[0], coords[1], coords[2]));
        }

            // Creates the side hydrogens
            for(int j = 0; j <= 1; j++) {
                // Finds the coordinates using the carbon
                std::array<float, 3> coords = position_hydrogen(source_coords, j, i, H_C_BOND, ANGLE);

                // Adds the new atom
                m.push_back(chemist::Atom("H", H_NPROTON, H_MASS, coords[0], coords[1], coords[2]));
        }

            if(i == num_carbon - 1) {
                // Finds the coordinates using the carbon
                std::array<float, 3> coords = position_hydrogen(source_coords, 3, i, H_C_BOND, ANGLE);

                // Adds the new atom
                m.push_back(chemist::Atom("H", H_NPROTON, H_MASS, coords[0], coords[1], coords[2]));
        }
    }
    auto rv = results();
    return simde::MoleculeToString::wrap_results(rv, m);

  }



}// namespace ghostfragment::hydrocarbon
