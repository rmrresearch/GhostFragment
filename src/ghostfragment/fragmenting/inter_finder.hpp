#include <chemist/molecule/fragmented_molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>

#include <map>
#include <utility>

namespace ghostfragment::fragmenting {

using mol_type  = chemist::FragmentedMolecule;
using nuke_type = chemist::FragmentedNuclei;

using inter_type = std::vector<std::size_t>;
using res_type   = std::map<inter_type, float>;

res_type intersections(const mol_type& mol);
} // namespace ghostfragment::fragmenting
