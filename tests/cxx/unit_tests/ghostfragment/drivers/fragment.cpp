// #include "../test_ghostfragment.hpp"

// using namespace ghostfragment;
// using namespace testing;

// using frags_pt       = simde::FragmentedMolecule;
// using graph_pt       = pt::MolecularGraph;
// using graph2frags_pt = pt::MolecularGraphToFragments;

// using frags_type = type::fragmented_molecule;
// using graph_type = MolecularGraph;
// using conns_type = graph_type::connectivity_type;
// using mol_type   = typename frags_type::superset_type;
// namespace {

// auto make_patom_module(const mol_type& mol, const frags_type& rv) {
//     return pluginplay::make_lambda<frags_pt>([=](auto&& mol_in) {
//         REQUIRE(mol_in == mol);
//         return rv;
//     });
// }

// auto make_graph_module(const frags_type& patoms, const graph_type& g) {
//     return pluginplay::make_lambda<graph_pt>([=](auto&& patom_in) {
//         REQUIRE(patom_in == patoms);
//         return g;
//     });
// }

// auto make_g2frag_module(const graph_type& g, const frags_type& rv) {
//     return pluginplay::make_lambda<graph2frags_pt>([=](auto&& graph_in) {
//         REQUIRE(graph_in == g);
//         return rv;
//     });
// }

// } // namespace

// /* Testing strategy:
//  *
//  * The FragmentDriver module is purely a driver. If we assume the modules it
//  * calls work correctly, the only thing we need to test is that the data flow.
//  * This is done with some facade modules, which verify they receive the correct
//  * inputs, and by verifying that the correct result is returned from the module.
//  */

// TEST_CASE("Fragment Driver") {
//     auto mm   = initialize();
//     auto& mod = mm.at("Fragment Driver");

//     // Factor out so change_submod fits on one line
//     const auto g2f_key = "Molecular graph to fragments";

//     // For water molecules the patoms are the same as the correct answer
//     SECTION("One molecule") {
//         auto mol = water(1);
//         frags_type corr(mol, {{0, 1, 2}});
//         graph_type graph(corr, conns_type(1));

//         mod.change_submod("Pseudoatoms", make_patom_module(mol, corr));
//         mod.change_submod("Molecular graph", make_graph_module(corr, graph));
//         mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
//         const auto& [frags] = mod.run_as<frags_pt>(mol);
//         REQUIRE(corr == frags);
//     }

//     SECTION("Two molecules") {
//         auto mol = water(2);
//         frags_type corr(mol, {{0, 1, 2}, {3, 4, 5}});
//         graph_type graph(corr, conns_type(2));

//         mod.change_submod("Pseudoatoms", make_patom_module(mol, corr));
//         mod.change_submod("Molecular graph", make_graph_module(corr, graph));
//         mod.change_submod(g2f_key, make_g2frag_module(graph, corr));
//         const auto& [frags] = mod.run_as<frags_pt>(mol);
//         REQUIRE(corr == frags);
//     }
// }
