#pragma once
#include <ghostfragment/term.hpp>

namespace ghostfragment {

class Interaction {
public:
    using size_type            = std::size_t;
    using term_type            = Term;
    using const_term_reference = const term_type&;
};

} // namespace ghostfragment