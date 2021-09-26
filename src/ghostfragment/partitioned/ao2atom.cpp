#include "ghostfragment/types.hpp"
#include "partitioned.hpp"
#include <cmath>
#include <limits>

namespace ghostfragment::partitioned {

using my_pt = simde::FragmentedAOSystem;

const auto mod_desc = R"(
AO To Atom Mapper
-----------------

This module will map each AO to the atom it is closest to. This algorithm is
not suitable for use when AOs are not atom-centered (*e.g.*, ghost atoms, and
mid-bond functions).

)";

MODULE_CTOR(AO2Atom) { satisfies_property_type<my_pt>(); }

MODULE_RUN(AO2Atom) {
    using return_type = type::fragmented_mols_and_aos;
    using value_type  = typename return_type::value_type;

    const auto& [mol_ao_pair] = my_pt::unwrap_inputs(inputs);
    const auto& mol           = std::get<0>(mol_ao_pair);
    const auto& aos           = std::get<1>(mol_ao_pair);

    return_type frags_and_aos(mol_ao_pair);

    // These are our buffers
    std::vector<value_type> subsets;
    for(std::size_t i = 0; i < mol.size(); ++i) {
        subsets.push_back(frags_and_aos.new_subset());
        std::get<1>(subsets.back()).insert(i);
    }

    for(std::size_t ao_i = 0; ao_i < aos.size(); ++ao_i) {
        std::size_t winner = 0;
        // This is many times larger than the observable universe...
        double dist = std::numeric_limits<double>::max();

        const auto& ao = aos[ao_i];
        for(std::size_t atom_i = 0; atom_i < mol.size(); ++atom_i) {
            const auto& xyz = mol[atom_i].coords();
            double dx       = ao.x() - xyz[0];
            double dy       = ao.y() - xyz[1];
            double dz       = ao.z() - xyz[2];
            double temp     = std::sqrt(dx * dx + dy * dy + dz * dz);
            if(temp >= dist) continue;
            winner = atom_i;
            dist   = temp;
        }
        std::get<0>(subsets[winner]).insert(ao_i);
    }
    for(auto&& x : subsets) frags_and_aos.insert(std::move(x));

    auto rv = results();
    return my_pt::wrap_results(rv, frags_and_aos);
}

} // namespace ghostfragment::partitioned