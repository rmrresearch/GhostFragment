#include "../modules.hpp"
#include "distance.hpp"
#include <simde/simde.hpp>
#include <utilities/iter_tools/combinations.hpp>

namespace ghostfragment {
namespace detail_ {

/// TODO: This should go into ReferenceData
/// Data is generated with Mathematica 10.0 (only available up to Z=96)
static std::vector<double> cov_radii{
  0.585815, 0.529123, 2.418849, 1.814137, 1.606267, 1.436192, 1.341706,
  1.247219, 1.077144, 1.096041, 3.136945, 2.664514, 2.286569, 2.097596,
  2.022007, 1.984212, 1.927521, 2.003110, 3.836144, 3.325918, 3.212534,
  3.023562, 2.891281, 2.626719, 2.626719, 2.494438, 2.381055, 2.343260,
  2.494438, 2.305466, 2.305466, 2.267671, 2.248774, 2.267671, 2.267671,
  2.192082, 4.157397, 3.684966, 3.590480, 3.307021, 3.099151, 2.910178,
  2.777897, 2.759000, 2.683411, 2.626719, 2.740103, 2.721206, 2.683411,
  2.626719, 2.626719, 2.607822, 2.626719, 2.645617, 4.610932, 4.062911,
  3.911733, 3.855041, 3.836144, 3.798350, 3.760555, 3.741658, 3.741658,
  3.703863, 3.666069, 3.628274, 3.628274, 3.571582, 3.590480, 3.533788,
  3.533788, 3.307021, 3.212534, 3.061356, 2.853486, 2.721206, 2.664514,
  2.570028, 2.570028, 2.494438, 2.740103, 2.759000, 2.796795, 2.645617,
  2.834589, 2.834589, 4.913288, 4.176295, 4.062911, 3.892836, 3.779452,
  3.703863, 3.590480, 3.533788, 3.401507, 3.193637,
};

} // namespace detail_

const auto mod_desc = R"(
Connectivity Table via Covalent Radii
-------------------------------------

Let :math:`r_{ij}` be the distance between the :math:`i`-th and :math:`j`-th 
nucleus, and :math:`\sigma_{k}` be the covalent radius of nucleus :math:`k` then
this module considers the :math:`i` and :math:`j`-th nuclui to be bonded if:

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
    satisfies_property_type<simde::Connectivity>();
    add_input<double>("tau").set_description(tau_desc).set_default(0.10);
}

MODULE_RUN(CovRadii) {
    const auto& [mol]     = simde::Connectivity::unwrap_inputs(inputs);
    const auto tau        = inputs.at("tau").value<double>();
    const auto tau_plus_1 = tau + 1.0;
    const auto natoms     = mol.size();
    simde::type::connectivity_table ct(mol.size());

    using size_type = typename std::decay_t<decltype(mol)>::size_type;
    for(size_type i = 0; i < natoms; ++i) {
        const auto atom_i  = mol[i];
        const auto sigma_i = detail_::cov_radii[atom_i.Z() - 1];
        for(size_type j = i + 1; j < natoms; ++j) {
            const auto atom_j   = mol[j];
            const auto sigma_j  = detail_::cov_radii[atom_j.Z() - 1];
            const auto rij      = detail_::atomic_distance(atom_i, atom_j);
            const auto max_bond = tau_plus_1 * (sigma_i + sigma_j);
            if(rij <= max_bond) ct.add_bond(i, j);
        }
    }

    auto rv = results();
    return simde::Connectivity::wrap_results(rv, ct);
}

} // namespace ghostfragment