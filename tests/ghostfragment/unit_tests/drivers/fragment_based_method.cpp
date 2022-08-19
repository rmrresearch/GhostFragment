#include "../test_ghostfragment.hpp"
#include <simde/energy/ao_energy.hpp>

/* Testing Strategy:
 *
 * This tests the main driver for GhostFragment. The main driver dispatches
 * to four submodules which respectively: fragment, make n-mers, make the
 * expression, and finally run the calculations. We assume those submodules
 * are independently tested and known to work. Thus for the purposes of this
 * test we need to make sure the driver calls those submodules with the
 * correct inputs, and properly handles the results. To that end we create
 * four lambda modules:
 *
 * - frag_mod checks that the inputs to the FragmentBasedMethod driver are
 *   forwarded to it correctly and then returns a set of fragments
 * - nmer_mod makes sure it's given the set of fragments from frag_mod and then
 *   returns a set of n-mers
 * - expr_mod checks that it's given set of n-mers from nmer_mod and then
 *   creates an expression which depends on the number of fragments and the
 *   value of n
 * - egy_mod checks that its given one of the systems expr_mod makes and then
 *   computes a double based on the index of that system
 *
 * For a system with n fragments truncated at order m the energy computed by
 * the driver (using the facade modules) should be:
 *
 *  E = -m \sum_{i=1}^n i
 *    = -m n(n + 1)/2
 *
 * The driver module has one parameter, the truncation order of the MBE. By
 * looping over truncation orders we test that it is picked up correctly.
 */

using namespace ghostfragment;
using namespace testing;

using my_pt         = simde::AOEnergy;
using frag_sys_pt   = pt::FragmentedSystem;
using nmer_sys_pt   = pt::NMerSystem;
using expression_pt = pt::Expression;

// Checks that we pass in the correct system/AO pair, returns a set of fragments
auto frag_mod(std::size_t n_waters) {
    return pluginplay::make_lambda<frag_sys_pt>([=](auto&& mol_in,
                                                    auto&& aos_in) {
        simde::type::chemical_system s(testing::water(n_waters), 10 * n_waters);
        REQUIRE(mol_in == s);
        REQUIRE(aos_in == testing::sto3g(s.molecule()));
        return testing::fragmented_water_system(n_waters);
    });
}

auto nmer_mod(std::size_t n_waters, std::size_t m) {
    return pluginplay::make_lambda<nmer_sys_pt>(
      [=](auto&& frags_in, auto&& m_in) {
          REQUIRE(frags_in == testing::fragmented_water_system(n_waters));
          REQUIRE(m_in == m);
          return testing::water_nmer_system(n_waters, m);
      });
}

auto expr_mod(std::size_t n_waters, std::size_t m) {
    using ghostfragment::equation::make_term;
    return pluginplay::make_lambda<expression_pt>([=](auto&& nmer_in) {
        REQUIRE(nmer_in == testing::water_nmer_system(n_waters, m));
        ghostfragment::pt::ExpressionTraits::result_type rv;
        auto frags = testing::water_nmer_system(n_waters, 1);
        for(std::size_t i = 0; i < n_waters; ++i) {
            const auto& w = frags.nmer(i);
            rv.add_term(make_term(w, frags.ao_basis_set(w), 10, m * 1.0));
        }
        return rv;
    });
}

auto egy_mod(std::size_t n_waters, std::size_t m) {
    using ghostfragment::equation::make_term;
    return pluginplay::make_lambda<my_pt>([=](auto&& aos_in, auto&& mol_in) {
        auto frags = testing::water_nmer_system(n_waters, 1);
        double egy = 0.0;
        for(std::size_t i = 0; i < n_waters; ++i) {
            const auto& w = frags.nmer(i);
            auto water    = make_term(w, frags.ao_basis_set(w), 10, m * 1.0);
            if(water.molecule() == mol_in.molecule()) {
                REQUIRE(aos_in.basis_set() == water.ao_basis_set());
                egy = (i + 1) * -1.0;
            }
        }
        REQUIRE(egy != 0.0);
        return egy;
    });
}

TEST_CASE("FragmentBasedMethod") {
    auto mm   = initialize();
    auto& mod = mm.at("Fragment Based Method");

    // = -m n(n + 1)/2
    for(std::size_t n = 1; n <= 4; ++n) {
        for(std::size_t m = 1; m <= n; ++m) {
            std::string name =
              std::to_string(n) + " water(s) " + std::to_string(m) + "body";
            SECTION(name) {
                const std::size_t n_waters = n;
                auto mol                   = testing::water(n_waters);
                simde::type::chemical_system sys(mol, n_waters * 10);
                auto aos = chemist::orbital_space::AOSpace(testing::sto3g(mol));

                mod.change_submod("Fragment Maker", frag_mod(n_waters));
                mod.change_submod("N-Mer Maker", nmer_mod(n_waters, m));
                mod.change_submod("Expression generator",
                                  expr_mod(n_waters, m));
                mod.change_submod("energy method", egy_mod(n_waters, m));
                unsigned int mu(m);

                mod.change_input("GMBE truncation order", mu);
                auto [e] = mod.run_as<my_pt>(aos, sys);

                double corr = -double(m * n * n + m * n) / 2.0;
                REQUIRE(e == corr);
            }
        }
    }
}
