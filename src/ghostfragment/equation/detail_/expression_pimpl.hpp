#pragma once
#include <ghostfragment/equation/expression.hpp>

namespace ghostfragment::equation::detail_ {

struct ExpressionPIMPL {
    using parent_type      = Expression;
    using pimpl_pointer    = parent_type::pimpl_pointer;
    using interaction_type = parent_type::interaction_type;
    using const_interaction_reference =
      parent_type::const_interaction_reference;

    pimpl_pointer clone() const {
        return std::make_unique<ExpressionPIMPL>(*this);
    }

    std::vector<interaction_type> m_interactions;
};

} // namespace ghostfragment::equation::detail_