#pragma once
#include <chemist/fragmenting/fragmented_nuclei.hpp>
#include <utility>

namespace ghostfragment::fragmenting {

struct IntersectionTraits {
    using input_type = chemist::fragmenting::FragmentedNuclei<chemist::Nuclei>;

    using result_type = input_type;
};

typename IntersectionTraits::result_type intersections(
  typename IntersectionTraits::input_type fragmented_system);

} // namespace ghostfragment::fragmenting
