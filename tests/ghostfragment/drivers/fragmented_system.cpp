#include "../test_ghostfragment.hpp"

using namespace ghostfragment;
using namespace testing;

using frag_pt    = simde::FragmentedMolecule;
using atom2ao_pt = simde::AtomToAO;
using mod_pt     = pt::FragmentedSystem;

/* Testing Strategy:
 *
 * The driver routine is pretty straightforward. All we really need to do is
 * ensure that the driver calls the submodules with the appropriate inputs and
 * that it correctly assigns electrons to atoms.
 */
TEST_CASE("FragmentedSystem Module") {
    auto mm = initialize();

    auto mol = water(1);
    auto bs  = sto3g(mol).basis_set();
    simde::type::chemical_system sys(mol);

    auto monomer = testing::fragmented_water(1);
    auto mono2ao = testing::water_ao_pairs(1);

    // Create and set default submods
    auto fragmenter_mod = pluginplay::make_lambda<frag_pt>([=](auto&& mol_in) {
        REQUIRE(mol_in == mol);
        return monomer;
    });

    auto atom2ao_mod =
      pluginplay::make_lambda<atom2ao_pt>([=](auto&& mol_in, auto&& bs_in) {
          REQUIRE(mol_in == mol);
          REQUIRE(bs_in == bs);
          using return_type = simde::atom_to_center_return_type;
          using set_type    = typename return_type::value_type;
          return_type corr(mol_in.size());
          for(std::size_t j = 0; j < mol_in.size(); ++j) corr[j] = set_type{j};
          return corr;
      });

    auto& mod = mm.at("FragmentedSystem Driver");
    mod.change_submod("Fragmenter", fragmenter_mod);
    mod.change_submod("Atom to AO Mapper", atom2ao_mod);

    SECTION("Standard usage") {
        const auto& [frags] = mod.run_as<mod_pt>(sys, bs);

        using vector_type = FragmentedSystem::atom2nelectron_type;
        using size_type   = vector_type::value_type;

        FragmentedSystem corr(monomer, mono2ao, vector_type{8, 1, 1});
        REQUIRE(frags == corr);
    }

    SECTION("Crashes for charged system") {
        simde::type::chemical_system charged_water(mol, 11);
        REQUIRE_THROWS_AS(mod.run_as<mod_pt>(charged_water, bs),
                          std::runtime_error);
    }
}
