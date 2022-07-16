#pragma once
#include <ghostfragment/equation/interaction.hpp>
#include <memory>

namespace ghostfragment::equation {
namespace detail_ {

class ExpressionPIMPL;

}

/**  @brief Class to connect all the pieces of a fragment-based method
 *
 *
 */
class Expression {
public:
    using pimpl_type                  = detail_::ExpressionPIMPL;
    using pimpl_pointer               = std::unique_ptr<pimpl_type>;
    using interaction_type            = Interaction;
    using const_interaction_reference = const interaction_type&;

    explicit Expression(pimpl_pointer pimpl = nullptr) noexcept;
    ~Expression() noexcept;

private:
    pimpl_pointer m_pimpl_;
};

} // namespace ghostfragment::equation