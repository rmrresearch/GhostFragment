#include "../test_ghostfragment.hpp"

using frags_type = ghostfragment::type::fragmented_molecule;
using nmers_type = ghostfragment::type::nmers;
using molecule   = ghostfragment::type::molecule;
using my_pt      = ghostfragment::pt::nmer_maker;

TEST_CASE("NMers") {
    auto mm   = testing::initialize();
    auto& mod = mm.at("All nmers");

    auto [H, He, O] = testing::some_atoms();

    // Here n is the order of nmers we are making and N is the total number
    // of fragments
    SECTION("N = 1") {
        molecule water(H, H, O);
        frags_type frags(water, {{0ul, 1ul, 2ul}});
        SECTION("n = 1") {
            nmers_type corr(frags, {{0ul}});
            mod.change_input("n", 1ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 2") {
            mod.change_input("n", 2ul);
            REQUIRE_THROWS_AS(mod.run_as<my_pt>(frags), std::runtime_error);
        }
    }

    SECTION("Disjoint N = 2") {
        molecule water(H, H, O, H, H, O);
        frags_type frags(water, {{0ul, 1ul, 2ul}, {3ul, 4ul, 5ul}});
        SECTION("n = 1") {
            nmers_type corr(frags, {{0ul}, {1ul}});
            mod.change_input("n", 1ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 2") {
            nmers_type corr(frags, {{0ul}, {1ul}, {0ul, 1ul}});
            mod.change_input("n", 2ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 3") {
            mod.change_input("n", 3ul);
            REQUIRE_THROWS_AS(mod.run_as<my_pt>(frags), std::runtime_error);
        }
    }

    SECTION("Non-disjoint N = 2") {
        molecule water(He, He, He);
        frags_type frags(water, {{0ul, 1ul}, {1ul, 2ul}});
        SECTION("n = 1") {
            nmers_type corr(frags, {{0ul}, {1ul}});
            mod.change_input("n", 1ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 2") {
            nmers_type corr(frags, {{0ul}, {1ul}, {0ul, 1ul}});
            mod.change_input("n", 2ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 3") {
            mod.change_input("n", 3ul);
            REQUIRE_THROWS_AS(mod.run_as<my_pt>(frags), std::runtime_error);
        }
    }

    SECTION("Disjoint N = 3") {
        molecule water(H, H, O, H, H, O, H, H, O);
        frags_type frags(water,
                         {{0ul, 1ul, 2ul}, {3ul, 4ul, 5ul}, {6ul, 7ul, 8ul}});
        SECTION("n = 1") {
            nmers_type corr(frags, {{0ul}, {1ul}, {2ul}});
            mod.change_input("n", 1ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 2") {
            nmers_type corr(
              frags, {{0ul}, {1ul}, {2ul}, {0ul, 1ul}, {0ul, 2ul}, {1ul, 2ul}});
            mod.change_input("n", 2ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 3") {
            nmers_type corr(frags, {{0ul},
                                    {1ul},
                                    {2ul},
                                    {0ul, 1ul},
                                    {0ul, 2ul},
                                    {1ul, 2ul},
                                    {0ul, 1ul, 2ul}});
            mod.change_input("n", 3ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 4") {
            mod.change_input("n", 4ul);
            REQUIRE_THROWS_AS(mod.run_as<my_pt>(frags), std::runtime_error);
        }
    }

    SECTION("Non-disjoint N = 3") {
        molecule water(He, He, He);
        frags_type frags(water, {{0ul, 1ul}, {0ul, 2ul}, {1ul, 2ul}});
        SECTION("n = 1") {
            nmers_type corr(frags, {{0ul}, {1ul}, {2ul}});
            mod.change_input("n", 1ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 2") {
            nmers_type corr(
              frags, {{0ul}, {1ul}, {2ul}, {0ul, 1ul}, {0ul, 2ul}, {1ul, 2ul}});
            mod.change_input("n", 2ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 3") {
            nmers_type corr(frags, {{0ul},
                                    {1ul},
                                    {2ul},
                                    {0ul, 1ul},
                                    {0ul, 2ul},
                                    {1ul, 2ul},
                                    {0ul, 1ul, 2ul}});
            mod.change_input("n", 3ul);
            auto [nmers] = mod.run_as<my_pt>(frags);
            REQUIRE(nmers == corr);
        }

        SECTION("n = 4") {
            mod.change_input("n", 4ul);
            REQUIRE_THROWS_AS(mod.run_as<my_pt>(frags), std::runtime_error);
        }
    }
}