#include "../test_ghostfragment.hpp"
#include <ghostfragment/property_types/fragmented_nuclei.hpp>
#include "hydrocarbon/hydrocarbon.h"

using namespace ghostfragment;
using namespace testing;

using my_pt        = pt::FragmentedNuclei;
using frags_pt     = pt::FragmentedNuclei;
using input_type   = chemist::Nuclei;
using result_type  = chemist::FragmentedNuclei;
using frags_type   = chemist::FragmentedNuclei;

namespace { 

auto make_frag_module(const chemist::Nuclei& mol, const frags_type& rv) {
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
        input_type nukes;
        result_type corr(nukes);
        mod.change_submod("Fragmentation", make_frag_module(nukes, corr));
        result_type frags = mod.run_as<my_pt>(nukes);
        REQUIRE(corr.operator==(frags));
    }

    SECTION("Single Nucleus") {
        chemist::Molecule mol;
        mol.push_back(chemist::Atom("H", 1, 1837.289, 0, 0, 0));
        input_type nukes(mol.nuclei());
        result_type fragments(nukes);
        result_type corr(nukes);
        fragments.add_fragment({0});

        mod.change_submod("Fragmentation", make_frag_module(nukes, fragments));
        result_type frags = mod.run_as<my_pt>(nukes);
        REQUIRE(corr.operator==(frags));
    }

    SECTION("Methane") {
        input_type nukes(hydrocarbon(1).nuclei());
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

        mod.change_submod("Fragmentation", make_frag_module(nukes, fragments));
        result_type frags = mod.run_as<my_pt>(nukes);
        REQUIRE(corr.operator==(frags));
    }
}