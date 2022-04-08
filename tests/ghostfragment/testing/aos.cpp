#include "aos.hpp"
#include "water.hpp"
#include <catch2/catch.hpp>

using namespace testing;

TEST_CASE("atom_to_ao") {
    using pimpl_type = ghostfragment::detail_::FragmentedSystemPIMPL;
    using a2ao_type  = pimpl_type::idx2ao_map_type;

    a2ao_type corr;

    SECTION("Zero waters") { REQUIRE(corr == atom_to_ao(water(0))); }

    SECTION("One water") {
        auto mol = water(1);
        ghostfragment::type::fragmented_aos ao_sets(sto3g(mol));

        auto ao0 = ao_sets.new_subset();
        ao0.insert(0);

        auto ao1 = ao_sets.new_subset();
        ao1.insert(1);

        auto ao2 = ao_sets.new_subset();
        ao2.insert(2);

        corr.emplace_back(ao0);
        corr.emplace_back(ao1);
        corr.emplace_back(ao2);
        REQUIRE(corr == atom_to_ao(mol));
    }

    SECTION("Two waters") {
        auto mol = water(2);
        ghostfragment::type::fragmented_aos ao_sets(sto3g(mol));

        auto ao0 = ao_sets.new_subset();
        ao0.insert(0);

        auto ao1 = ao_sets.new_subset();
        ao1.insert(1);

        auto ao2 = ao_sets.new_subset();
        ao2.insert(2);

        auto ao3 = ao_sets.new_subset();
        ao3.insert(3);

        auto ao4 = ao_sets.new_subset();
        ao4.insert(4);

        auto ao5 = ao_sets.new_subset();
        ao5.insert(5);

        corr.emplace_back(ao0);
        corr.emplace_back(ao1);
        corr.emplace_back(ao2);
        corr.emplace_back(ao3);
        corr.emplace_back(ao4);
        corr.emplace_back(ao5);
        REQUIRE(corr == atom_to_ao(mol));
    }

    SECTION("Three waters") {
        auto mol = water(3);
        ghostfragment::type::fragmented_aos ao_sets(sto3g(mol));

        auto ao0 = ao_sets.new_subset();
        ao0.insert(0);

        auto ao1 = ao_sets.new_subset();
        ao1.insert(1);

        auto ao2 = ao_sets.new_subset();
        ao2.insert(2);

        auto ao3 = ao_sets.new_subset();
        ao3.insert(3);

        auto ao4 = ao_sets.new_subset();
        ao4.insert(4);

        auto ao5 = ao_sets.new_subset();
        ao5.insert(5);

        auto ao6 = ao_sets.new_subset();
        ao6.insert(6);

        auto ao7 = ao_sets.new_subset();
        ao7.insert(7);

        auto ao8 = ao_sets.new_subset();
        ao8.insert(8);

        corr.emplace_back(ao0);
        corr.emplace_back(ao1);
        corr.emplace_back(ao2);
        corr.emplace_back(ao3);
        corr.emplace_back(ao4);
        corr.emplace_back(ao5);
        corr.emplace_back(ao6);
        corr.emplace_back(ao7);
        corr.emplace_back(ao8);
        REQUIRE(corr == atom_to_ao(mol));
    }
}
