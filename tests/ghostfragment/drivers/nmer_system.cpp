#include "../test_ghostfragment.hpp"

using namespace ghostfragment;
using namespace testing;

using nmers_pt        = pt::NMers;
using capped_nmers_pt = pt::CappedNMers;
using mod_pt          = pt::NMerSystem;
using traits_type     = pt::NMerSystemTraits;

TEST_CASE("NMerSystem Module") {
    auto mm  = initialize();
    auto mod = mm.at("NMerSystem Driver");

    auto monomer = fragmented_water(1);
    auto mono2ao = water_ao_pairs(1);

    using input_type  = traits_type::input_type;
    using vector_type = input_type::vector_type;

    input_type frags(monomer, mono2ao, vector_type{8, 1, 1});
    auto nmers = make_nmers(monomer, 1);

    auto& f2n = pluginplay::make_lambda<nmers_pt>([=](auto&& frags_in) {
        REQUIRE(frags_in == frags);
        return nmers;
    });

    using capped_nmers_t = pt::CappedNMersTraits::result_type;
    decltype(monomer) caps(nmers.object());
    auto empty_set = caps.new_subset();
    capped_nmers_t capped_nmers;
    capped_nmers.emplace(monomer[0], empty_set);

    auto& n2capped = pluginplay::make_lambda<nmers_pt>([=](auto&& nmers_in) {
        REQUIRE(nmers_in == nmers);
        return capped_nmers;
    });

    using result_type = traits_type::result_type;
    result_type corr(frags, capped_nmers);

    mod.change_submod("Fragments to NMers", f2n);
    mod.change_submod("NMers to Capped NMers", n2capped);

    auto& [nmer_system] = mod.run_as<mod_pt>(frags);
    REQURIE(nmer_system == corr);
}