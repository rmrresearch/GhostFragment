#include "ghostfragment/connectivity_table/connectivity_table_pimpl.hpp"
#include <catch2/catch.hpp>

using namespace ghostfragment::detail_;

using size_type = typename ConnectivityTablePIMPL::size_type;

TEST_CASE("ConnectivityTablePIMPL") {
    ConnectivityTablePIMPL defaulted;

    SECTION("Typedefs") {
        using ct_t = ghostfragment::ConnectivityTable;
        // Make sure the PIMPL uses the same type as the main class
        STATIC_REQUIRE(std::is_same_v<size_type, typename ct_t::size_type>);
    }

    SECTION("Default CTor") {
        REQUIRE(defaulted.natoms() == 0);
        REQUIRE(defaulted.nbonds() == 0);
    }

    SECTION("Allocating CTor") {
        for(size_type i = 0; i < 10; ++i) {
            SECTION(std::to_string(i) + " atoms") {
                ConnectivityTablePIMPL p(i);
                REQUIRE(p.natoms() == i);
                REQUIRE(p.nbonds() == 0);
            }
        }
    }

    ConnectivityTablePIMPL p0;
    ConnectivityTablePIMPL p1(1);
    ConnectivityTablePIMPL p2(2);
    ConnectivityTablePIMPL p3(3);

    SECTION("add_bond") {
        SECTION("Throws if atom is out of bounds") {
            REQUIRE_THROWS_AS(p0.add_bond(0, 0), std::out_of_range);
            REQUIRE_THROWS_AS(p1.add_bond(0, 1), std::out_of_range);
            REQUIRE_THROWS_AS(p2.add_bond(3, 1), std::out_of_range);
            REQUIRE_THROWS_AS(p3.add_bond(4, 4), std::out_of_range);
        }

        SECTION("Can't add self bond") {
            REQUIRE_THROWS_AS(p1.add_bond(0, 0), std::out_of_range);
        }

        SECTION("Add bond to two-atom system") {
            REQUIRE(p2.nbonds() == 0);
            REQUIRE_FALSE(p2.are_bonded(0, 1));

            p2.add_bond(0, 1);

            REQUIRE(p2.nbonds() == 1);
            REQUIRE(p2.are_bonded(0, 1));
        }

        SECTION("Add bonds to three-atom system") {
            REQUIRE(p3.nbonds() == 0);
            REQUIRE_FALSE(p3.are_bonded(0, 2));
            REQUIRE_FALSE(p3.are_bonded(1, 2));

            p3.add_bond(0, 2);

            REQUIRE(p3.nbonds() == 1);
            REQUIRE(p3.are_bonded(0, 2));
            REQUIRE_FALSE(p3.are_bonded(1, 2));

            p3.add_bond(1, 2);
            REQUIRE(p3.nbonds() == 2);
            REQUIRE(p3.are_bonded(0, 2));
            REQUIRE(p3.are_bonded(1, 2));
        }

        SECTION("Adding same bond twice is okay and doesn't change state") {
            REQUIRE(p2.nbonds() == 0);
            REQUIRE_FALSE(p2.are_bonded(0, 1));

            p2.add_bond(0, 1);

            REQUIRE(p2.nbonds() == 1);
            REQUIRE(p2.are_bonded(0, 1));

            p2.add_bond(0, 1);
            REQUIRE(p2.nbonds() == 1);
            REQUIRE(p2.are_bonded(0, 1));
        }
    }
}
