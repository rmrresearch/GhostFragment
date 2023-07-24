#include "drivers.hpp"

#include <ghostfragment/property_types/property_types.hpp>
#include <ghostfragment/property_types/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmented_molecule.hpp>
#include <fragmenting/inter_finder.hpp>

namespace ghostfragment::drivers {

const auto mod_desc = R"(
    Input Queue
    --------------------------------

    This module takes as input a ChemicalSystem object, and returns a vector of pairs
    of ChemicalSystem objects along with their associated integer weights. The new ChemicalSystem
    objects are produced via fragmentation of the original ChemicalSystem, and subsequent use 
    of the Intersection Finder module to produce all unique intersections of fragments and their
    weights. The module then returns the original fragments with weight one and all of the intersections with their corresponding weights as a vector of pairs.
)";

using my_pt   = pt::InputQueue;
using frag_pt = pt::FragmentedNuclei;
using mol_pt  = pt::FragmentedMolecule;

MODULE_CTOR(InputQueue) {
    description(mod_desc);

    satisfies_property_type<my_pt>();

    add_submodule<frag_pt>("Fragmentation");
    add_submodule<mol_pt>("FragtoMol");
}

MODULE_RUN(InputQueue) {
    using result_type = pt::InputQueueTraits::result_type;
    using input_type  = pt::InputQueueTraits::system_type;
    using pair_type   = std::pair<chemist::ChemicalSystem, double>;
    using return_type = std::vector<pair_type>;

    const auto& [system] = my_pt::unwrap_inputs(inputs);

    // Fragments chemical system
    auto& frag_mod                  = submods.at("Fragmentation");
    chemist::FragmentedNuclei frags = frag_mod.run_as<frag_pt>(system);

    // Converts FragmentedNuclei to FragmentedMolecule
    // (For intersection finder)
    auto& mol_mod                         = submods.at("FragtoMol");
    chemist::FragmentedMolecule mol_frags = mol_mod.run_as<mol_pt>(frags);

    // Finds all intersections
    const auto& ints = ghostfragment::fragmenting::intersections(mol_frags);

    // Stores weights
    std::vector<double> weights;
    for(std::size_t i = 0; i < frags.size(); ++i) {
        weights.push_back(1);
    }

    // Adds intersections to existing fragments
    for(const auto& pair : ints) {
        frags.add_fragment(pair.first.begin(), pair.first.end());
        weights.push_back(pair.second);
    }

    // Converts FragmentedNuclei to FragmentedMolecule
    mol_frags = mol_mod.run_as<mol_pt>(frags);

    // Converts each fragment into a chemical system
    std::vector<chemist::ChemicalSystem> systems;
    for(const auto& frag : mol_frags) {
        chemist::Molecule mol(frag.charge(), frag.multiplicity(), {});
        for(const auto& atom : frag) {
            mol.push_back(chemist::Atom(atom.name(), atom.Z(), atom.mass(), atom.x(), atom.y(), atom.z()));
        }
        systems.push_back(chemist::ChemicalSystem(mol));
    }

    // Associates systems with their respective weights
    return_type pairs;
    for(std::size_t i = 0; i < systems.size(); ++i) {
        pairs.push_back(pair_type(systems[i], weights[i]));
    }

    auto rv = results();
    return my_pt::wrap_results(rv, pairs);
}

} // namespace ghostfragment