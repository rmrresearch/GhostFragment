#pragma once
#include <ghostfragment/interaction.hpp>

namespace ghostfragment::detail_ {

struct InteractionPIMPL {
    using parent_type    = Interaction;
    using term_type      = parent_type::term_type;
    using term_container = std::vector<term_type>;
    using pimpl_pointer  = parent_type::pimpl_pointer;

    pimpl_pointer clone() const {
        return std::make_unique<InteractionPIMPL>(*this);
    }

    term_container m_terms;
};

} // namespace ghostfragment::detail_