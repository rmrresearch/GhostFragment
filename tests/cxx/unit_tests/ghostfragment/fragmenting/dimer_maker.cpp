#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmented_nuclei.hpp>
#include "hydrocarbon/hydrocarbon.h"

using namespace ghostfragment;
using namespace testing;

using my_pt        = pt::FragmentedNuclei;
using frags_pt     = pt::FragmentedNuclei;
using input_type   = chemist::ChemicalSystem;
using result_type  = chemist::FragmentedNuclei;
using nukes_type   = chemist::Nuclei;
using frags_type   = chemist::FragmentedNuclei;

namespace { 

auto make_frag_module(const input_type& mol, const frags_type& rv) {
    return pluginplay::make_lambda<frags_pt>([=](auto&& mol_in) {
        REQUIRE(mol_in == mol);
        return rv;
    });
}
} // namespace

TEST_CASE("Dimer Maker") {

    auto mm        = initialize();
    auto& mod      = mm.at("Dimer Maker");

    SECTION("Empty Nuclei") {
        input_type system;
        nukes_type nukes;
        result_type corr(nukes);
        mod.change_submod("Fragmentation", make_frag_module(system, corr));
        result_type frags = mod.run_as<my_pt>(system);
        REQUIRE(corr == frags);
    }

    SECTION("Single Nucleus") {
        chemist::Molecule mol;
        mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
        nukes_type nukes(mol.nuclei());
        input_type system(mol);
        result_type fragments(nukes);
        result_type corr(nukes);
        fragments.add_fragment({0});

        mod.change_submod("Fragmentation", make_frag_module(system, fragments));
        result_type frags = mod.run_as<my_pt>(system);
        REQUIRE(corr == frags);
    }

    SECTION("Methane") {
        nukes_type nukes(hydrocarbon(1).nuclei());
        input_type system(hydrocarbon(1));

        result_type fragments(nukes);
        fragments.add_fragment({0, 1});
        fragments.add_fragment({0, 2});
        fragments.add_fragment({0, 3});
        fragments.add_fragment({0, 4});

        result_type corr(nukes);
        corr.add_fragment({0, 1, 2});
        corr.add_fragment({0, 2, 3});
        corr.add_fragment({0, 3, 4});
        corr.add_fragment({0, 1, 3});
        corr.add_fragment({0, 2, 4});
        corr.add_fragment({0, 1, 4});

        mod.change_submod("Fragmentation", make_frag_module(system, fragments));
        result_type frags = mod.run_as<my_pt>(system);
        REQUIRE(corr == frags);
    }

    SECTION("Methane (alternative fragmentation)") {
        nukes_type nukes(hydrocarbon(1).nuclei());
        input_type system(hydrocarbon(1));

        result_type fragments(nukes);
        fragments.add_fragment({0, 1});
        fragments.add_fragment({1, 3});
        fragments.add_fragment({2, 3});
        fragments.add_fragment({0, 4});

        result_type corr(nukes);
        corr.add_fragment({0, 1, 2, 3});
        corr.add_fragment({0, 1, 3, 4});
        corr.add_fragment({0, 2, 3, 4});

        mod.change_submod("Fragmentation", make_frag_module(system, fragments));
        result_type frags = mod.run_as<my_pt>(system);
        REQUIRE(corr == frags);
    }
}