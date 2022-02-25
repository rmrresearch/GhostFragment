#include "ghostfragment/nmer_system.hpp"

namespace ghostfragment {
namespace detail_ {

class NMerSystemPIMPL {
public:
    using parent_type       = NMerSystem;
    using capped_nmers      = typename parent_type::capped_nmers;
    using fragment_set_type = typename parent_type::fragmented_system_type;

    NMerSystemPIMPL(capped_nmers nmers, fragment_set_type frags) :
      m_nmers_(std::move(nmers)), m_frags_(std::move(frags)) {}

private:
    capped_nmers m_nmers_;
    fragment_set_type m_frags_;
};

} // namespace detail_

namespace {

template<typename... Args>
auto make_pimpl(Args&&... args) {
    return std::make_unique<detail_::NMerSystemPIMPL>(
      std::forward<Args>(args)...);
}

} // namespace

NMerSystem::NMerSystem() noexcept = default;

NMerSystem::NMerSystem(fragmented_system_type frags, capped_nmers nmers) :
  NMerSystem(make_pimpl(std::move(frags), std::move(nmers))) {}

NMerSystem::NMerSystem(pimpl_pointer pimpl) noexcept :
  m_pimpl_(std::move(pimpl)) {}

NMerSystem::~NMerSystem() noexcept = default;

} // namespace ghostfragment
