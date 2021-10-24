#include "ghostfragment/types.hpp"
#include "partitioned.hpp"
#include <cmath>
#include <limits>

namespace ghostfragment::partitioned {

using my_pt = simde::AtomToAO;

const auto mod_desc = R"(
Center To Atom Mapper
---------------------

This module will map each center to the atom it is closest to. This algorithm is
not suitable for use when centers are not atom-centered (*e.g.*, ghost atoms, 
and mid-bond functions).

)";

MODULE_CTOR(AO2Atom) {
    description(mod_desc);

    satisfies_property_type<my_pt>();
}

MODULE_RUN(AO2Atom) {
    using return_type = simde::atom_to_center_return_type;

    const auto& [mol, aos] = my_pt::unwrap_inputs(inputs);

    return_type atom2center(mol.size());

    for(std::size_t ao_i = 0; ao_i < aos.size(); ++ao_i) {
        // This will be the index of that atom that the basis function is
        // closest to
        std::size_t winner = 0;

        // This is the distance to the winning atom. The default values is
        // many times larger than the observable universe...
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
        atom2center[winner].insert(ao_i);
    }

    auto rv = results();
    return my_pt::wrap_results(rv, atom2center);
}

} // namespace ghostfragment::partitioned