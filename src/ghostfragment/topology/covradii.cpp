/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "covalent_radius.hpp"
#include "topology.hpp"
#include <ghostfragment/property_types/topology/connectivity_table.hpp>
#include <simde/simde.hpp>

namespace ghostfragment::topology {

using my_pt       = pt::ConnectivityTable;
using traits_type = pt::ConnectivityTableTraits;

const auto mod_desc = R"(
Connectivity Table via Covalent Radii
-------------------------------------

Let :math:`r_{ij}` be the distance between the :math:`i`-th and :math:`j`-th
nucleus, and :math:`\sigma_{k}` be the covalent radius of nucleus :math:`k`
then this module considers the :math:`i` and :math:`j`-th nuclei to be bonded
if:

.. math::

  r_{ij} \le \left(1 + \tau\right)\left(\sigma_{i} + \sigma_{j}\right)

where :math:`r_{ij}` can be no more than :math:`1+\tau` times larger than
:math:`\sigma_{i} + \sigma_{j}` for :math:`i` and :math:`j` to be bonded. For
example, for :math:`tau=1` :math:`r_{ij}` is allowed to be two times larger
than the distance predicted by the covalent radii.
)";

const auto tau_desc = R"(
How much larger the actual distance can be compared to the predicted distance
(as a ratio).
)";

MODULE_CTOR(CovRadii) {
    description(mod_desc);
    satisfies_property_type<my_pt>();
    add_input<double>("tau").set_description(tau_desc).set_default(0.10);
}

MODULE_RUN(CovRadii) {
    const auto& [mol]     = my_pt::unwrap_inputs(inputs);
    const auto tau        = inputs.at("tau").value<double>();
    const auto tau_plus_1 = tau + 1.0;
    const auto natoms     = mol.size();

    traits_type::result_type ct(natoms);

    using size_type = typename std::decay_t<decltype(mol)>::size_type;
    for(size_type i = 0; i < natoms; ++i) {
        const auto atom_i  = mol[i];
        const auto sigma_i = covalent_radius(atom_i.Z());

        for(size_type j = i + 1; j < natoms; ++j) {
            const auto atom_j  = mol[j].as_nucleus();
            const auto sigma_j = covalent_radius(atom_j.Z());

            const auto rij      = (atom_i.as_nucleus() - atom_j).magnitude();
            const auto max_bond = tau_plus_1 * (sigma_i + sigma_j);
            if(rij <= max_bond) ct.add_bond(i, j);
        }
    }

    auto rv = results();
    return my_pt::wrap_results(rv, ct);
}

} // namespace ghostfragment::topology
