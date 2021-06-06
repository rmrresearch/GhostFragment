#include "../test_ghostfragment.hpp"

TEST_CASE("CovRadii Module") {
    using pt            = ghostfragment::pt::connectivity;
    using molecule_type = property_types::type::molecule;
    using atom_type     = typename molecule_type::value_type;
    using cart_type     = typename atom_type::coord_type;
    using ct_type       = property_types::type::connectivity_table;

    auto mm   = testing::initialize();
    auto& mod = mm.at("Covalent Radius");

    const auto sigma_h = 0.585815;
    const auto sigma_o = 1.247219;

    SECTION("Default tau") {
        atom_type h0{"H", 1ul, cart_type{0.0, 0.0, 0.0}};
        SECTION("Two H atoms") {
            SECTION("Less than tau * sigma") {
                cart_type r1{0.0, 0.0, 0.9 * (sigma_h + sigma_h)};
                molecule_type h2(h0, atom_type{"H", 1ul, r1});

                auto [ct] = mod.run_as<pt>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("At tau * sigma") {
                cart_type r1{0.0, 0.0, 1.1 * (sigma_h + sigma_h)};
                molecule_type h2(h0, atom_type{"H", 1ul, r1});

                auto [ct] = mod.run_as<pt>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("Longer than tau * sigma") {
                cart_type r1{0.0, 0.0, 2.0 * (sigma_h + sigma_h)};
                molecule_type h2(h0, atom_type{"H", 1ul, r1});

                auto [ct] = mod.run_as<pt>(h2);
                ct_type corr(2);
                REQUIRE(ct == corr);
            }
        }
    }

    SECTION("Non-default tau") {
        mod.change_input("tau", 1.0);
        atom_type h0{"H", 1ul, cart_type{0.0, 0.0, 0.0}};
        SECTION("Two H atoms") {
            SECTION("Less than tau * sigma") {
                cart_type r1{0.0, 0.0, 0.9 * (sigma_h + sigma_h)};
                molecule_type h2(h0, atom_type{"H", 1ul, r1});

                auto [ct] = mod.run_as<pt>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("At tau * sigma") {
                cart_type r1{0.0, 0.0, 2.0 * (sigma_h + sigma_h)};
                molecule_type h2(h0, atom_type{"H", 1ul, r1});

                auto [ct] = mod.run_as<pt>(h2);
                ct_type corr(2);
                corr.add_bond(0, 1);
                REQUIRE(ct == corr);
            }

            SECTION("Longer than tau * sigma") {
                cart_type r1{0.0, 0.0, 3.0 * (sigma_h + sigma_h)};
                molecule_type h2(h0, atom_type{"H", 1ul, r1});

                auto [ct] = mod.run_as<pt>(h2);
                ct_type corr(2);
                REQUIRE(ct == corr);
            }
        }
    }

    SECTION("Water monomer") {
        cart_type rO{0.00000000000000, -0.07579039945857, 0.00000000000000};
        cart_type rH0{0.86681456860648, 0.60144316994806, 0.00000000000000};
        cart_type rH1{-0.86681456860648, 0.60144316994806, 0.00000000000000};
        atom_type O{"O", 8ul, rO};
        atom_type H0{"H", 1ul, rH0};
        atom_type H1{"H", 1ul, rH1};
        molecule_type h2o(O, H0, H1);

        auto [ct] = mod.run_as<pt>(h2o);
        ct_type corr(3);
        corr.add_bond(0, 1);
        corr.add_bond(0, 2);
        REQUIRE(ct == corr);
    }
}