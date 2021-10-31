// #include "../test_ghostfragment.hpp"

// namespace {

// auto frag_ao_mod(const simde::type::molecule& mol,
//                  const simde::type::ao_basis_set& aos) {
//     return pluginplay::make_lambda<simde::FragmentedNucleiAO>(
//       [&](auto&& mol_ao_pair) {
//           REQUIRE(std::get<0>(mol_ao_pair) == mol);
//           REQUIRE(std::get<1>(mol_ao_pair) == aos);
//           return testing::water_ao_pairs(mol.size() / 3);
//       });
// }

// } // namespace

// TEST_CASE("SystemAO") {
//     auto mm   = testing::initialize();
//     auto& mod = mm.at("System-AO Fragmenter");
//     using pt  = ghostfragment::pt::FragmentedSystemAO;

//     for(std::size_t n = 0; n < 6; ++n) {
//         const auto water_n       = testing::water(n);
//         const auto aos_n         = testing::sto3g(water_n).basis_set();
//         const auto water_ao_pair = std::make_tuple(water_n, aos_n);
//         const auto nelecs        = 10 * n;

//         SECTION("Water " + std::to_string(n)) {
//             auto new_submod = frag_ao_mod(water_n, aos_n);
//             mod.change_submod("Nuclei-AO Fragmenter", new_submod);
//             const auto& [nes, frags] = mod.run_as<pt>(nelecs, water_ao_pair);
//             std::vector<std::size_t> corr_nes(n, 10);
//             REQUIRE(nes == corr_nes);
//             REQUIRE(frags == testing::water_ao_pairs(n));
//         }
//     }

//     SECTION("Errs if charged species") {
//         const auto water = testing::water(1);
//         const auto aos   = testing::sto3g(water).basis_set();
//         const auto pair  = std::make_tuple(water, aos);

//         mod.change_submod("Nuclei-AO Fragmenter", frag_ao_mod(water, aos));
//         REQUIRE_THROWS_AS(mod.run_as<pt>(4ul, pair), std::runtime_error);
//     }
// }
