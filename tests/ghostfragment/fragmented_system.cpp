#include "ghostfragment/fragmented_system.hpp"
#include "test_ghostfragment.hpp"

using namespace ghostfragment;

/* Testing Strategy:
 *
 * We make four fragmented systems:
 * - defaulted: A default constructed instance
 * - empty: An instance created with all empty containers
 * - netural: Supersystem containing a single neutral water molecule
 * - charged: Supersystem containing two water molecules, first is netural
 *            second is charged
 */

TEST_CASE("FragmentedSystem") {
    auto monomer  = testing::fragmented_water(1);
    auto dimer    = testing::fragmented_water(2);
    auto mono2ao  = testing::water_ao_pairs(1);
    auto dimer2ao = testing::water_ao_pairs(2);

    using vector_type = FragmentedSystem::atom2nelectron_type;
    using size_type   = vector_type::value_type;

    FragmentedSystem defaulted;
    FragmentedSystem empty    = testing::fragmented_water_system(0);
    FragmentedSystem neutral  = testing::fragmented_water_system(1);
    auto dimer_pimpl          = testing::fragmented_water_system_pimpl(2);
    dimer_pimpl->m_atom2ne[3] = 9;
    FragmentedSystem charged(std::move(dimer_pimpl));

    SECTION("Ctors") {
        SECTION("Default") { REQUIRE(defaulted.nfrags() == 0); }

        SECTION("Value") {
            REQUIRE(empty.nfrags() == 0);
            REQUIRE(neutral.nfrags() == 1);
            REQUIRE(charged.nfrags() == 2);
        }

        SECTION("Copy") {
            FragmentedSystem copy1(defaulted);
            REQUIRE(copy1 == defaulted);

            FragmentedSystem copy2(neutral);
            REQUIRE(copy2 == neutral);

            FragmentedSystem copy3(charged);
            REQUIRE(copy3 == charged);
        }

        SECTION("Move") {
            FragmentedSystem copy1(defaulted);
            FragmentedSystem moved1(std::move(defaulted));
            REQUIRE(copy1 == moved1);

            FragmentedSystem copy2(neutral);
            FragmentedSystem moved2(std::move(neutral));
            REQUIRE(copy2 == moved2);

            FragmentedSystem copy3(charged);
            FragmentedSystem moved3(std::move(charged));
            REQUIRE(copy3 == moved3);
        }

        SECTION("Copy Assignment") {
            FragmentedSystem copy;
            auto pcopy = &(copy = defaulted);
            REQUIRE(pcopy == &copy);
            REQUIRE(copy == defaulted);

            pcopy = &(copy = neutral);
            REQUIRE(pcopy == &copy);
            REQUIRE(copy == neutral);

            pcopy = &(copy = charged);
            REQUIRE(pcopy == &copy);
            REQUIRE(copy == charged);
        }

        SECTION("Move Assignment") {
            FragmentedSystem copy1(defaulted);
            FragmentedSystem moved;
            auto pmoved = &(moved = std::move(defaulted));
            REQUIRE(pmoved == &moved);
            REQUIRE(copy1 == moved);

            FragmentedSystem copy2(neutral);
            pmoved = &(moved = std::move(neutral));
            REQUIRE(pmoved == &moved);
            REQUIRE(copy2 == moved);

            FragmentedSystem copy3(charged);
            pmoved = &(moved = std::move(charged));
            REQUIRE(pmoved == &moved);
            REQUIRE(copy3 == moved);
        }
    }

    SECTION("nfrags") {
        REQUIRE(defaulted.nfrags() == 0);

        REQUIRE(empty.nfrags() == 0);

        REQUIRE(neutral.nfrags() == 1);

        REQUIRE(charged.nfrags() == 2);
    }

    SECTION("count") {
        REQUIRE(defaulted.count(monomer[0]) == 0);
        REQUIRE(defaulted.count(dimer[0]) == 0);
        REQUIRE(defaulted.count(dimer[1]) == 0);

        REQUIRE(empty.count(monomer[0]) == 0);
        REQUIRE(empty.count(dimer[0]) == 0);
        REQUIRE(empty.count(dimer[1]) == 0);

        REQUIRE(neutral.count(monomer[0]) == 1);
        REQUIRE(neutral.count(dimer[0]) == 0);
        REQUIRE(neutral.count(dimer[1]) == 0);

        REQUIRE(charged.count(monomer[0]) == 0);
        REQUIRE(charged.count(dimer[0]) == 1);
        REQUIRE(charged.count(dimer[1]) == 1);
    }

    SECTION("frags") {
        REQUIRE_THROWS_AS(defaulted.frags(), std::runtime_error);
        REQUIRE(empty.frags() == testing::fragmented_water(0));
        REQUIRE(neutral.frags() == monomer);
        REQUIRE(charged.frags() == dimer);
    }

    SECTION("fragment") {
        REQUIRE_THROWS_AS(defaulted.fragment(0), std::out_of_range);

        REQUIRE_THROWS_AS(empty.fragment(0), std::out_of_range);

        REQUIRE(neutral.fragment(0) == monomer.at(0));
        REQUIRE_THROWS_AS(neutral.fragment(1), std::out_of_range);

        REQUIRE(charged.fragment(0) == dimer.at(0));
        REQUIRE(charged.fragment(1) == dimer.at(1));
        REQUIRE_THROWS_AS(charged.fragment(2), std::out_of_range);
    }

    SECTION("caps") {
        const auto& w0 = monomer.at(0);
        REQUIRE_THROWS_AS(defaulted.caps(w0), std::runtime_error);
        REQUIRE_THROWS_AS(empty.caps(w0), std::out_of_range);

        REQUIRE(neutral.caps(w0) == testing::caps_for_water(1)[0]);

        auto dimer_caps = testing::caps_for_water(2);
        REQUIRE(charged.caps(dimer.at(0)) == dimer_caps[0]);
        REQUIRE(charged.caps(dimer.at(1)) == dimer_caps[0]);
        REQUIRE_THROWS_AS(charged.caps(w0), std::out_of_range);
    }

    SECTION("ao_basis_set") {
        const auto& w0 = monomer.at(0);
        const auto& w1 = dimer.at(1);

        REQUIRE_THROWS_AS(defaulted.ao_basis_set(w0), std::runtime_error);

        REQUIRE_THROWS_AS(empty.ao_basis_set(w0), std::out_of_range);

        auto O0 = monomer.new_subset();
        auto H0 = monomer.new_subset();
        auto H1 = monomer.new_subset();
        O0.insert(0);
        H0.insert(1);
        H1.insert(2);

        auto w0_basis = mono2ao.at(O0) + mono2ao.at(H0) + mono2ao.at(H1);

        REQUIRE(neutral.ao_basis_set(w0) == w0_basis);
        REQUIRE_THROWS_AS(neutral.ao_basis_set(w1), std::out_of_range);

        O0      = dimer.new_subset();
        H0      = dimer.new_subset();
        H1      = dimer.new_subset();
        auto O1 = dimer.new_subset();
        auto H2 = dimer.new_subset();
        auto H3 = dimer.new_subset();
        O0.insert(0);
        H0.insert(1);
        H1.insert(2);
        O1.insert(3);
        H2.insert(4);
        H3.insert(5);
        w0_basis      = dimer2ao.at(O0) + dimer2ao.at(H0) + dimer2ao.at(H1);
        auto w1_basis = dimer2ao.at(O1) + dimer2ao.at(H2) + dimer2ao.at(H3);

        REQUIRE(charged.ao_basis_set(dimer.at(0)) == w0_basis);
        REQUIRE(charged.ao_basis_set(w1) == w1_basis);

        REQUIRE_THROWS_AS(charged.ao_basis_set(w0), std::out_of_range);
    }

    SECTION("n_electrons") {
        const auto& w0 = monomer.at(0);
        const auto& w1 = dimer.at(1);

        REQUIRE_THROWS_AS(defaulted.n_electrons(w0), std::runtime_error);

        REQUIRE_THROWS_AS(empty.n_electrons(w0), std::out_of_range);

        REQUIRE(neutral.n_electrons(w0) == 10);
        REQUIRE_THROWS_AS(neutral.n_electrons(w1), std::out_of_range);

        REQUIRE(charged.n_electrons(dimer.at(0)) == 10);
        REQUIRE(charged.n_electrons(w1) == 11);

        REQUIRE_THROWS_AS(charged.n_electrons(w0), std::out_of_range);
    }

    SECTION("Comparisons") {
        FragmentedSystem lhs;

        REQUIRE(lhs == defaulted);
        REQUIRE_FALSE(lhs != defaulted);

        REQUIRE(lhs != empty);
        REQUIRE_FALSE(lhs == empty);

        REQUIRE(lhs != neutral);
        REQUIRE_FALSE(lhs == neutral);

        REQUIRE(lhs != charged);
        REQUIRE_FALSE(lhs == charged);
    }

    SECTION("hash") {
        auto lhs = pluginplay::hash_objects(FragmentedSystem{});

        REQUIRE(lhs == pluginplay::hash_objects(defaulted));

        REQUIRE(lhs != pluginplay::hash_objects(empty));

        REQUIRE(lhs != pluginplay::hash_objects(neutral));

        REQUIRE(lhs != pluginplay::hash_objects(charged));
    }
}
