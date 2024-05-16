// #pragma once
// #include <simde/simde.hpp>

// namespace ghostfragment::capping {

// DECLARE_MODULE(SingleAtom);
// DECLARE_MODULE(DCLC);
// DECLARE_MODULE(WeightedDistance);

// inline void load_modules(pluginplay::ModuleManager& mm) {
//     mm.add_module<SingleAtom>("Atomic Capping");
//     mm.add_module<DCLC>("DCLC Capping");
//     mm.add_module<WeightedDistance>("Weighted Distance");
// }

// inline void set_defaults(pluginplay::ModuleManager& mm) {
//     mm.change_submod("Atomic Capping", "Connectivity", "Covalent Radius");
//     mm.change_submod("Weighted Distance", "Broken Bonds", "Broken Bonds");
//     mm.change_submod("DCLC Capping", "Connectivity", "Covalent Radius");
// }

// double average_bond_length(const chemist::Nuclei& m,
// const chemist::topology::ConnectivityTable& connections,
// std::size_t z_x, std::size_t z_c);

// } // namespace ghostfragment::capping
