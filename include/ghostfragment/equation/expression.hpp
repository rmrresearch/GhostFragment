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
    using size_type                   = std::size_t;
    using pimpl_type                  = detail_::ExpressionPIMPL;
    using pimpl_pointer               = std::unique_ptr<pimpl_type>;
    using interaction_type            = Interaction;
    using const_interaction_reference = const interaction_type&;

    explicit Expression() noexcept;
    explicit Expression(pimpl_pointer pimpl) noexcept;
    Expression(const Expression& other);
    Expression(Expression&& other) noexcept;
    Expression& operator=(const Expression& other);
    Expression& operator=(Expression&& other) noexcept;
    ~Expression() noexcept;

    size_type size() const noexcept;

    void emplace_back(interaction_type interaction);

    const_interaction_reference at(size_type i) const;

    bool empty() const noexcept;

    void swap(Expression& other) noexcept;

    bool operator==(const Expression& rhs) const noexcept;

    bool operator!=(const Expression& rhs) const noexcept;

private:
    bool has_pimpl_() const noexcept;

    void bounds_check_(size_type i) const;
    pimpl_pointer m_pimpl_;
};

} // namespace ghostfragment::equation