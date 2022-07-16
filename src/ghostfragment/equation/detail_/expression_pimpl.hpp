#pragma once
#include <ghostfragment/equation/expression.hpp>

namespace ghostfragment::equation::detail_ {

struct ExpressionPIMPL {
    using parent_type      = Expression;
    using interaction_type = parent_type::interaction_type;
    using const_interaction_reference =
      parent_type::const_interaction_reference;

    std::vector<interaction_type> m_interactions;
};

} // namespace ghostfragment::equation::detail_