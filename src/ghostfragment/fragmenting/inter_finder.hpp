#include <chemist/molecule/fragmented_molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <map>
#include <utility>

namespace ghostfragment::fragmenting {

using mol_type  = chemist::FragmentedMolecule;
using nuke_type = chemist::FragmentedNuclei;

using frag_type   = std::vector<std::size_t>;
using system_type = std::vector<frag_type>;

using group_type = std::vector<std::size_t>;

using inter_type = std::vector<std::size_t>;
using res_type   = std::map<inter_type, float>;

using log_type = std::map<std::pair<std::size_t, std::size_t>, inter_type>;

void find_group_intersections(const system_type& fragments, inter_type inter,
                              std::size_t recent_add, res_type& m,
                              log_type& log, group_type& group);

void find_pair_intersections(const system_type& fragments, log_type& log);

void create_system(const mol_type& mol, system_type& fragments);

res_type intersections(const mol_type& mol);
} // namespace ghostfragment::fragmenting
