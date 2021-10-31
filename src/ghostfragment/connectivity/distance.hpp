#include <cmath> // for std::sqrt
#include <simde/simde.hpp>

namespace ghostfragment::detail_ {

inline auto atomic_distance(const simde::type::atom& ai,
                            const simde::type::atom& aj) {
    using size_type = typename simde::type::atom::size_type;
    double dr       = 0.0;
    for(size_type q = 0; q < 3; ++q) {
        const auto dq = ai[q] - aj[q];
        dr += dq * dq;
    }
    return std::sqrt(dr);
}

} // namespace ghostfragment::detail_