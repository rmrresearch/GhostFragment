// #include "../test_ghostfragment.hpp"

// using return_type = simde::atom_to_center_return_type;
// using set_type    = typename return_type::value_type;

// TEST_CASE("AO2Atom") {
//     auto mm  = testing::initialize();
//     auto mod = mm.at("AO Center to Atom Mapper");

//     for(std::size_t nwaters = 1; nwaters < 4; ++nwaters) {
//         SECTION(std::to_string(nwaters) + " waters") {
//             auto water       = testing::water(nwaters);
//             auto bs          = testing::sto3g(water);
//             const auto& [rv] = mod.run_as<simde::AtomToAO>(water, bs);

//             // Our testing funtions add the centers in order; so atom i's AOs
//             // are the i-th set of AOs
//             return_type corr(3 * nwaters);
//             for(std::size_t j = 0; j < 3 * nwaters; ++j) corr[j] = set_type{j};
//             REQUIRE(corr == rv);
//         }
//     }
// }
