#pragma once
#include <chemist/molecule/molecule.hpp>
#include <chemist/nucleus/fragmented_nuclei.hpp>
#include <ghostfragment/connectivity/hydrocarbon/hydrocarbon.h>

namespace testing {

/// Fragments a hydrocarbon system (fragments are M carbons
/// with M-1 carbon overlap with adjacent fragments,
/// hydrocarbon is N carbons long)
inline auto hydrocarbon_fragmented_nuclei(std::size_t N, std::size_t M) {
    auto hydrocarbon_n = hydrocarbon(N);
    chemist::FragmentedNuclei frags(hydrocarbon_n.nuclei());
    // Define fragment to add to fragmented nuclei
    std::vector<std::size_t> frag {};
    for(std::size_t i = 0; i < N - (M+1); ++i){
        frag = {};
        for(std::size_t j = i; j < i + M; ++j){
            frag.push_back(j);
            if(j == 0){
                frag.push_back(N);
            }
            if(j == N - 1){
                frag.push_back(2*j + 3 + N);
            }
            frag.push_back(2*j + 1 + N);
            frag.push_back(2*j + 2 + N);
        }
        frags.add_fragment(frag.begin(), frag.end());
    }
    return frags;
}

} // namespace testing