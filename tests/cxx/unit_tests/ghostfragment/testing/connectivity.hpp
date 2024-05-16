// #pragma once
// #include <simde/simde.hpp>

// namespace testing {

// /// Creates a connectivity table for a water cluster. It's assumed that each
// /// water is order O, H, H
// inline auto water_connectivity(std::size_t N) {
//     simde::type::connectivity_table connects(3 * N);
//     for(std::size_t water_i = 0; water_i < N; ++water_i) {
//         std::size_t start = 3 * water_i;     // Index of oxygen for water_i
//         connects.add_bond(start, start + 1); // start + 1 is 1st hydrogen
//         connects.add_bond(start, start + 2); // start + 2 is 2nd hydrogen
//     }
//     return connects;
// }

// } // namespace testing
