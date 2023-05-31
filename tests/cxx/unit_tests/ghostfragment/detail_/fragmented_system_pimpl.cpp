// #include "../test_ghostfragment.hpp"
// #include <catch2/catch.hpp>
// #include <ghostfragment/detail_/fragmented_system_pimpl.hpp>

// using namespace ghostfragment::detail_;

// TEST_CASE("FragmentedSystemPIPML") {
//     FragmentedSystemPIMPL defaulted;

//     const std::size_t N = 2;
//     auto non_defaulted  = testing::fragmented_water_system_pimpl(N);
//     const auto& frag0   = non_defaulted->m_frags[0];
//     const auto& frag1   = non_defaulted->m_frags[1];

//     SECTION("ao_basis_set") {
//         const auto& atom2aos = non_defaulted->m_atom2aos;

//         auto corr0 = atom2aos[0] + atom2aos[1] + atom2aos[2];
//         REQUIRE(non_defaulted->ao_basis_set(frag0) == corr0);

//         auto corr1 = atom2aos[3] + atom2aos[4] + atom2aos[5];
//         REQUIRE(non_defaulted->ao_basis_set(frag1) == corr1);
//     }

//     SECTION("n_electrons") {
//         REQUIRE(non_defaulted->n_electrons(frag0) == 10);
//         REQUIRE(non_defaulted->n_electrons(frag1) == 10);
//     }

//     SECTION("operator==") {
//         auto other = testing::fragmented_water_system_pimpl(N);

//         REQUIRE(*non_defaulted == *other);

//         SECTION("Different fragments") {
//             other->m_frags = testing::fragmented_water_needing_caps(N);
//             REQUIRE_FALSE(*non_defaulted == *other);
//         }

//         SECTION("Different caps") {
//             other->m_frag2caps = testing::capped_water_needing_caps(N);
//             REQUIRE_FALSE(*non_defaulted == *other);
//         }

//         SECTION("Different atom-to-AO mapping") {
//             other->m_atom2aos.clear();
//             REQUIRE_FALSE(*non_defaulted == *other);
//         }

//         SECTION("Different cap-to-AO mapping") {
//             other->m_cap2aos = other->m_atom2aos;
//             REQUIRE_FALSE(*non_defaulted == *other);
//         }

//         SECTION("Different atom-to-ne mapping") {
//             other->m_atom2ne[0] = 1;
//             REQUIRE_FALSE(*non_defaulted == *other);
//         }

//         SECTION("Different cap-to-ne mapping") {
//             other->m_cap2ne = other->m_atom2ne;
//             REQUIRE_FALSE(*non_defaulted == *other);
//         }
//     }
// }
