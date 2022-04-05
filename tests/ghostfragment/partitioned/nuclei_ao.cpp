#include "../test_ghostfragment.hpp"

using namespace ghostfragment::pt;

namespace {
// Module assuming atoms [3*i, 3 * i + 3) are the atoms in fragment i
auto frag_mod(const simde::type::molecule& mol) {
    chemist::set_theory::FamilyOfSets<simde::type::molecule> rv(mol);
    auto new_set = rv.new_subset();
    for(std::size_t i = 0, j = 1; i < mol.size(); ++i, ++j) {
        new_set.insert(i);
        if(j == 3) {
            rv.insert(new_set);
            new_set = rv.new_subset();
            j       = 0; // set it to 0 b/c loop will increment it to 1
        }
    }
    return rv;
}

// Module assuming atom i's AOs are center i
auto ao2center_mod(const simde::type::molecule& mol,
                   const simde::type::ao_basis_set& bs) {
    using return_type = simde::atom_to_center_return_type;
    using subset_type = typename return_type::value_type;

    return pluginplay::make_lambda<simde::AtomToAO>(
      [=](auto&& mol_in, auto&& aos_in) {
          REQUIRE(mol_in == mol);
          REQUIRE(aos_in == bs);
          return_type rv(mol.size());
          for(std::size_t i = 0; i < mol.size(); ++i) {
              rv[i] = subset_type{i};
          }
          return rv;
      });
}
} // namespace

TEST_CASE("NucleiAO") {
    auto mm  = testing::initialize();
    auto mod = mm.at("Nuclei-AO Fragmenter");

    using return_type = typename Frag2AOTraits::result_type;

    for(std::size_t nwaters = 0; nwaters < 4; ++nwaters) {
        SECTION(std::to_string(nwaters) + " waters") {
            auto mol   = testing::water(nwaters);
            auto bs    = testing::sto3g(mol);
            auto frags = frag_mod(mol);

            mod.change_submod("Atom to Center", ao2center_mod(mol, bs));
            auto [rv] = mod.run_as<Frag2AO>(frags, bs);

            REQUIRE(rv.size() == nwaters);
            for(const auto& [key, value] : rv) {
                for(const auto& keyi : key) { REQUIRE(value.count(bs[keyi])); }
            }
        }
    }
}
