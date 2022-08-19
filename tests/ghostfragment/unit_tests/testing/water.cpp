#include "water.hpp"
#include <catch2/catch.hpp>

using namespace testing;

/* Unit tests our function for creating water "clusters". We simply test it
 * against the correct hard-coded answers for up to a tetramer. It's assumed
 * that if it works that much, it'll keep working...
 */

TEST_CASE("water") {
    using molecule_type = ghostfragment::type::nuclei_set;
    using atom_type     = typename molecule_type::value_type;
    using cart_type     = typename atom_type::coord_type;
    const unsigned long OZ{8}, HZ{1};
    const double Ox{0.00000000000000}, Oy{-0.07579039945857};
    const double Hx{0.86681456860648}, Hy{0.60144316994806};

    SECTION("Zero waters") {
        molecule_type corr;
        REQUIRE(corr == water(0));
    }

    SECTION("One water") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 0.0}});
        REQUIRE(corr == water(1));
    }

    SECTION("Two waters") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 0.0}});
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 3.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 3.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 3.0}});
        REQUIRE(corr == water(2));
    }

    SECTION("Three waters") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 0.0}});
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 3.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 3.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 3.0}});
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 6.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 6.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 6.0}});
        REQUIRE(corr == water(3));
    }

    SECTION("Four waters") {
        molecule_type corr;
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 0.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 0.0}});
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 3.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 3.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 3.0}});
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 6.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 6.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 6.0}});
        corr.push_back(atom_type{"O", OZ, cart_type{Ox, Oy, 9.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{Hx, Hy, 9.0}});
        corr.push_back(atom_type{"H", HZ, cart_type{-Hx, Hy, 9.0}});
        REQUIRE(corr == water(4));
    }
}
