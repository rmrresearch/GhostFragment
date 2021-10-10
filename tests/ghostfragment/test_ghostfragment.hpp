#pragma once
#include "ghostfragment/ghostfragment.hpp"
#include <catch2/catch.hpp>
#include <simde/simde.hpp>

namespace testing {

inline auto initialize() {
    pluginplay::ModuleManager mm;
    ghostfragment::load_modules(mm);
    return mm;
}

inline auto some_atoms() {
    using molecule = simde::type::molecule;
    using atom     = typename molecule::value_type;
    atom H{"H", 1ul};
    atom He{"He", 2ul};
    atom O{"O", 8ul};
    return std::make_tuple(H, He, O);
}

inline auto water() {
    using molecule_type = simde::type::molecule;
    using atom_type     = typename molecule_type::value_type;
    using cart_type     = typename atom_type::coord_type;
    cart_type rO{0.00000000000000, -0.07579039945857, 0.00000000000000};
    cart_type rH0{0.86681456860648, 0.60144316994806, 0.00000000000000};
    cart_type rH1{-0.86681456860648, 0.60144316994806, 0.00000000000000};
    atom_type O{"O", 8ul, rO};
    atom_type H0{"H", 1ul, rH0};
    atom_type H1{"H", 1ul, rH1};
    return molecule_type{O, H0, H1};
}

inline auto sto3g(const simde::type::molecule& mol) {
    using vector_t = std::vector<double>;
    using namespace libchemist;

    // Taken from hard-coded basis sets in NWX
    // O
    vector_t c0_o{0.15432897, 0.53532814, 0.44463454};
    vector_t a0_o{130.7093200, 23.8088610, 6.4436083};
    vector_t c1{-0.09996723, 0.39951283, 0.70011547};
    vector_t c2{0.15591627, 0.60768372, 0.39195739};
    vector_t a1{5.0331513, 1.1695961, 0.3803890};

    // H
    vector_t c0{0.1543289673, 0.5353281423, 0.4446345422};
    vector_t a0{3.425250914, 0.6239137298, 0.1688554040};

    AOBasisSet<double> bs;
    for(const auto& atom_i : mol) {
        Center<double> c;
        for(std::size_t i = 0; i < 3; ++i) c.coord(i) = atom_i.coords()[i];
        if(atom_i.Z() == 1) {
            c.add_shell(ShellType::pure, 0, c0, a0);
        } else if(atom_i.Z() == 8) {
            c.add_shell(ShellType::pure, 0, c0_o, a0_o);
            c.add_shell(ShellType::pure, 0, c1, a1);
            c.add_shell(ShellType::pure, 1, c2, a1);
        } else {
            throw std::out_of_range("No data for atomic number");
        }
        bs.add_center(c);
    }
    return simde::type::ao_space{bs};
}

} // namespace testing