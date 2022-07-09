#pragma once
#include <ghostfragment/fragment_based_method.hpp>
#include <ghostfragment/interaction.hpp>

namespace ghostfragment::detail_ {

struct FragmentBasedMethodPIMPL {
    using parent_type      = FragmentBasedMethod;
    using nmer_system      = parent_type::nmer_system;
    using interaction_type = parent_type::interaction_type;
    using const_interaction_reference =
      parent_type::const_interaction_reference;

    FragmentBasedMethodPIMPL(nmer_system nmers);

    std::shared_ptr<nmer_system> m_nmers;
    std::vector<interaction_type> m_interactions;
};

inline FragmentBasedMethodPIMPL::FragmentBasedMethodPIMPL(nmer_system nmers) :
  m_nmers(std::make_shared<nmer_system>(std::move(nmers))) {}

} // namespace ghostfragment::detail_