#pragma once
#include <simde/simde.hpp>

namespace ghostfragment::type {

using fragmented_nuclei =
    chemist::fragmenting::FragmentedNuclei<simde::type::nuclei>;

using fragmented_molecule = 
  chemist::fragmenting::FragmentedMolecule<simde::type::molecule>;

using fragmented_chemical_system = 
  chemist::fragmenting::FragmentedChemicalSystem<simde::type::chemical_system>;

}