#pragma once
#include <ghostfragment/fragment_based_method.hpp>

namespace ghostfragment {

class Term {
private:
    using fbm_type = FragmentBasedMethod;

public:
    using const_nmer_reference = fbm_type::const_nmer_reference;
    using coefficient_type     = double;

private:
};

} // namespace ghostfragment