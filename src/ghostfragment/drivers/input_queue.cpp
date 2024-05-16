// #include "drivers.hpp"

// #include <ghostfragment/property_types/property_types.hpp>
// #include <ghostfragment/property_types/fragmented_nuclei.hpp>
// #include <ghostfragment/property_types/fragmented_molecule.hpp>
// #include <fragmenting/inter_finder.hpp>

// namespace ghostfragment::drivers {

// bool comparePairs(const std::pair<std::vector<std::size_t>, double>& a,
// const std::pair<std::vector<std::size_t>, double>& b) {
//     return a.first < b.first;
// }

// const auto mod_desc = R"(
//     Input Queue
//     --------------------------------

//     This module takes as input a ChemicalSystem object, and returns a vector
//     of pairs of ChemicalSystem objects along with their associated integer
//     weights. The new ChemicalSystem objects are produced via fragmentation of
//     the original ChemicalSystem, and subsequent use of the Intersection
//     Finder module to produce all unique intersections of fragments and their
//     weights. The module then returns the original fragments with weight one
//     and all of the intersections with their corresponding weights as a vector
//     of pairs.
// )";

// using my_pt   = pt::InputQueue;
// using frag_pt = pt::FragmentedNuclei;
// using mol_pt  = pt::FragmentedMolecule;

// MODULE_CTOR(InputQueue) {
//     description(mod_desc);

//     satisfies_property_type<my_pt>();

//     add_submodule<frag_pt>("Fragmentation");
//     add_submodule<mol_pt>("FragtoMol");
// }

// MODULE_RUN(InputQueue) {
//     using result_type = pt::InputQueueTraits::result_type;
//     using input_type  = pt::InputQueueTraits::system_type;
//     using pair_type   = std::pair<chemist::ChemicalSystem, double>;
//     using return_type = std::vector<pair_type>;

//     const auto& [system] = my_pt::unwrap_inputs(inputs);

//     if(system == input_type()) {
//         throw std::runtime_error("Wasn't expecting default construction");
//     }

//     // Fragments chemical system
//     auto& frag_mod                  = submods.at("Fragmentation");
//     chemist::FragmentedNuclei frags = frag_mod.run_as<frag_pt>(system);

//     // Converts FragmentedNuclei to FragmentedMolecule
//     // (For intersection finder)
//     auto& mol_mod                         = submods.at("FragtoMol");
//     chemist::FragmentedMolecule mol_frags = mol_mod.run_as<mol_pt>(frags);

//     // Finds all intersections
//     const auto& ints = ghostfragment::fragmenting::intersections(mol_frags);

//     // Stores weights and extracts indices from fragments
//     std::vector<double> weights;
//     std::vector<std::vector<std::size_t>> indices;
//     for(std::size_t i = 0; i < frags.size(); ++i) {
//         weights.push_back(1);
//         std::vector<std::size_t> indx;
//         for(const auto atom : frags[i]) {
//             indx.push_back(atom);
//         }
//         indices.push_back(indx);
//     }

//     // Adds intersections to vector of indices
//     for(auto pair : ints) {
//         std::vector<std::size_t> indx;
//         for(const auto& num : pair.first) {
//             indx.push_back(num);
//         }
//         indices.push_back(indx);
//         weights.push_back(pair.second);
//     }

//     std::vector<std::pair<std::vector<std::size_t>, double>> pairs;

//     for(std::size_t i = 0; i < indices.size(); ++i) {
//         pairs.push_back(std::make_pair(indices[i], weights[i]));
//     }

//     std::sort(pairs.begin(), pairs.end(), comparePairs);

//     // Combines all FragmentedNuclei, extracts weights
//     chemist::FragmentedNuclei all_frags(system.molecule().nuclei());
//     std::vector<double> all_weights;
//     for(std::size_t i = 0; i < pairs.size(); ++i) {
//         all_frags.add_fragment(pairs[i].first.begin(), pairs[i].first.end());
//         all_weights.push_back(pairs[i].second);
//     }

//     // Converts FragmentedNuclei to FragmentedMolecule
//     mol_frags = mol_mod.run_as<mol_pt>(all_frags);

//     // Converts each fragment into a chemical system
//     std::vector<chemist::ChemicalSystem> systems;
//     for(const auto& frag : mol_frags) {
//         chemist::Molecule mol(frag.charge(), frag.multiplicity(), {});
//         for(const auto& atom : frag) {
//             mol.push_back(chemist::Atom(atom.name(), atom.Z(), atom.mass(),
//             atom.x(), atom.y(), atom.z()));
//         }
//         systems.push_back(chemist::ChemicalSystem(mol));
//     }

//     // Associates systems with their respective weights
//     return_type system_weights;
//     for(std::size_t i = 0; i < systems.size(); ++i) {
//         system_weights.push_back(pair_type(systems[i], all_weights[i]));
//     }

//     auto rv = results();
//     return my_pt::wrap_results(rv, system_weights);
// }

// } // namespace ghostfragment
