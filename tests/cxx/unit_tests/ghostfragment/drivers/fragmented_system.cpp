#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmenting/fragmented_chemical_system.hpp>
#include <ghostfragment/property_types/fragmenting/fragmented_nuclei.hpp>

using namespace ghostfragment;
using namespace testing;

using frag_sys_pt        = pt::FragmentedChemicalSystem;
using frag_nuclei_pt     = pt::FragmentedNuclei;
using frag_sys_traits    = pt::FragmentedChemicalSystemTraits;
using frag_nuclei_traits = pt::FragmentedNucleiTraits;
using chem_system_type   = typename frag_sys_traits::system_type;
using frag_nuclei_type   = typename frag_nuclei_traits::result_type;
using frag_system_type   = typename frag_sys_traits::result_type;
using frag_molecule_type = typename frag_system_type::fragmented_molecule_type;
using charge_list        = typename frag_molecule_type::charge_container;
using mult_list          = typename frag_molecule_type::multiplicity_container;

namespace {

auto make_frag_submod(const chem_system_type& sys,
                      const frag_nuclei_type& frags) {
    return pluginplay::make_lambda<frag_nuclei_pt>([=](auto&& sys_in) {
        REQUIRE(sys_in == sys);
        return frags;
    });
}

} // namespace

/* Testing Strategy:
 *
 * The driver routine is pretty straightforward. All we really need to do is
 * ensure that the driver calls the submodules with the appropriate inputs and
 * that it correctly assigns electrons to atoms.
 */

TEST_CASE("FragmentedChemicalSystem Module") {
    auto mm   = initialize();
    auto& mod = mm.at("FragmentedChemicalSystem Driver");

    for(std::size_t i = 1; i < 5; ++i) {
        SECTION("Water " + std::to_string(i)) {
            chem_system_type sys(testing::water(i));
            auto frags = testing::water_fragmented_nuclei(i);
            mod.change_submod("Fragmenter", make_frag_submod(sys, frags));
            const auto& sys_frags = mod.run_as<frag_sys_pt>(sys);

            charge_list charges(i, 0);
            mult_list mults(i, 1);

            frag_molecule_type mol_frags(frags, 0, 1, charges, mults);
            frag_system_type corr_frags(mol_frags);
            REQUIRE(sys_frags == corr_frags);
        }
    }

    SECTION("Crashes for charged system") {
        auto mol = testing::water(1);
        mol.set_charge(1);
        chem_system_type charged_water(std::move(mol));
        using except_t = std::runtime_error;
        REQUIRE_THROWS_AS(mod.run_as<frag_sys_pt>(charged_water), except_t);
    }
}
