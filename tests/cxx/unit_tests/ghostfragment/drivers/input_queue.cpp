#include "../test_ghostfragment.hpp"
#include "hydrocarbon/hydrocarbon.h"
#include <ghostfragment/property_types/property_types.hpp>
#include <ghostfragment/property_types/fragmented_nuclei.hpp>
#include <ghostfragment/property_types/fragmented_molecule.hpp>

using namespace ghostfragment;
using namespace testing;

using my_pt    = pt::InputQueue;
using frags_pt = pt::FragmentedNuclei;
using mol_pt   = pt::FragmentedMolecule;

using system_type  = chemist::ChemicalSystem;
using frags_type   = chemist::FragmentedNuclei;
using fragmol_type = chemist::FragmentedMolecule;
using mol_type     = chemist::Molecule;
using pair_type   = std::pair<chemist::ChemicalSystem, double>;
using return_type = std::vector<pair_type>;

namespace { 

auto make_frag_module(const system_type& mol, const frags_type& rv) {
    return pluginplay::make_lambda<frags_pt>([=](auto&& mol_in) {
        REQUIRE(mol_in == mol);
        return rv;
    });
}

auto make_mol_module(const frags_type& mol_1, const frags_type& mol_2, 
const fragmol_type& rv_1, const fragmol_type& rv_2) {
    return pluginplay::make_lambda<mol_pt>([=](auto&& mol_in) {
        if(mol_in == mol_1) {
            return rv_1;
        }
        else {
            return rv_2;
        }
    });
}

} // namespace

/* Testing strategy:
 *
 * InputQueue is mainly a driver. Aside from the finding of intersections,
 * the rest of its behavior is determined by submodules. We thus employ lambda
 * functions as surrogates for these modules to test InputQueue itself.
 */

TEST_CASE("Input Queue") {
    auto mm   = initialize();
    auto& mod = mm.at("Input Queue");

    SECTION("Empty System") {
        system_type system;
        return_type corr;

        mod.change_submod("Fragmentation", make_frag_module(system, frags_type()));
        mod.change_submod("FragtoMol", make_mol_module(frags_type(),
        frags_type(), fragmol_type(), fragmol_type()));
        const auto& rv = mod.run_as<my_pt>(system);
        REQUIRE(corr == rv);
    }

    SECTION("Single Atom") {
        chemist::Molecule mol;
        mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
        system_type system(mol);

        frags_type frags(mol.nuclei());
        frags.add_fragment({0});

        fragmol_type fragmol(frags);
        
        return_type corr;
        corr.push_back(pair_type(system, 1));

        mod.change_submod("Fragmentation", make_frag_module(system, frags));
        mod.change_submod("FragtoMol", make_mol_module(frags, frags, fragmol, fragmol));
        const auto& rv = mod.run_as<my_pt>(system);
        REQUIRE(corr == rv);
    }

    // SECTION("Methane") {
    //     auto methane = hydrocarbon(1);
    //     system_type system(methane);
    //     frags_type corr(methane.nuclei());
    //     corr.add_fragment({0, 1, 2, 3, 4});
    //     graph_type graph(corr, {});

    //     mod.change_submod("Pseudoatoms", make_patom_module(system, corr));
    //     mod.change_submod("Molecular graph", make_graph_module(corr, graph));
    //     mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
    //     const auto& rv = mod.run_as<frags_pt>(system);
    //     REQUIRE(corr == rv);
    // }

    // SECTION("Ethane") {
    //     auto ethane = hydrocarbon(2);
    //     system_type system(ethane);
    //     frags_type corr(ethane.nuclei());
    //     corr.add_fragment({0, 2, 3, 4});
    //     corr.add_fragment({1, 5, 6, 7});
    //     conns_type c(2);
    //     c.add_bond(0, 1);
    //     graph_type graph(corr, c);

    //     mod.change_submod("Pseudoatoms", make_patom_module(system, corr));
    //     mod.change_submod("Molecular graph", make_graph_module(corr, graph));
    //     mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
    //     const auto& rv = mod.run_as<frags_pt>(system);
    //     REQUIRE(corr == rv);
    // }
}