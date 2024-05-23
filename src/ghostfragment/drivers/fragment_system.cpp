#include "drivers.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_chemical_system.hpp>
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>
namespace ghostfragment::drivers {

using my_pt    = pt::FragmentedChemicalSystem;
using frags_pt = pt::FragmentedNuclei;

const auto mod_desc = R"(
FragmentedSystem Driver
-----------------------

This module is responsible for wrapping the process of turning a
ChemicalSystem into a FragmentedChemicalSystem instance. This has the following
steps:

#. Fragment the nuclei.
#. Assign charge/multiplicity to each fragment
#. Assign fields to each fragment

Step 1 is done by a submodule of type FragmentedNuclei.
Step 2 and 3 are (for now) just done by the driver.
)";

MODULE_CTOR(FragmentedChemicalSystem) {
    description(mod_desc);

    satisfies_property_type<my_pt>();

    add_submodule<frags_pt>("Fragmenter");
}

MODULE_RUN(FragmentedChemicalSystem) {
    using traits_type        = pt::FragmentedChemicalSystemTraits;
    using frag_chem_sys_type = typename traits_type::result_type;
    using frag_molecule_type =
      typename frag_chem_sys_type::fragmented_molecule_type;
    using charge_list = typename frag_molecule_type::charge_container;
    using multiplicity_list =
      typename frag_molecule_type::multiplicity_container;

    // Step 0: Unpack input and inspect
    const auto& [sys] = my_pt::unwrap_inputs(inputs);

    if(sys.molecule().charge())
        throw std::runtime_error("Charged systems are NYI.");

    // Step 1: Form fragments
    auto& fragmenter         = submods.at("Fragmenter");
    const auto& nuclei_frags = fragmenter.run_as<frags_pt>(sys);

    // Step 2: Assign charge/multiplicity
    auto charge = sys.molecule().charge();
    auto mult   = sys.molecule().multiplicity();
    charge_list frag_charges(nuclei_frags.size(), charge);
    multiplicity_list frag_mults(nuclei_frags.size(), mult);

    frag_molecule_type mol_frags(nuclei_frags, charge, mult,
                                 std::move(frag_charges),
                                 std::move(frag_mults));

    // Step 3: Assign fields
    frag_chem_sys_type sys_frags(std::move(mol_frags));

    auto rv = results();
    return my_pt::wrap_results(rv, sys_frags);
}

} // namespace ghostfragment::drivers
