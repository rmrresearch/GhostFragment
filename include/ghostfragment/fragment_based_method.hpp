#pragma once
#include <ghostfragment/nmer_system.hpp>

namespace ghostfragment {
namespace detail_ {

class FragmentBasedMethodPIMPL;

}

class Interaction;

/**  @brief Class to connect all the pieces of a fragment-based method
 *
 *
 */
class FragmentBasedMethod {
public:
    using pimpl_type                  = detail_::FragmentBasedMethodPIMPL;
    using pimpl_pointer               = std::unique_ptr<pimpl_type>;
    using nmer_system                 = NMerSystem;
    using const_nmer_reference        = NMerSystem::const_nmer_reference;
    using interaction_type            = Interaction;
    using const_interaction_reference = const interaction_type&;

    explicit FragmentBasedMethod(pimpl_pointer pimpl = nullptr) noexcept;
    explicit FragmentBasedMethod(nmer_system nmers);
    ~FragmentBasedMethod() noexcept;

private:
    pimpl_pointer m_pimpl_;
};

} // namespace ghostfragment