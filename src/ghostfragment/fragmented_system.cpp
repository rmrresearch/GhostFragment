#include "detail_/fragmented_system_pimpl.hpp"
#include <ghostfragment/fragmented_system.hpp>

namespace ghostfragment {
namespace {

template<typename... Args>
auto make_pimpl(Args&&... args) {
    using pimpl_type = detail_::FragmentedSystemPIMPL;
    return std::make_unique<pimpl_type>(std::forward<Args>(args)...);
}
} // namespace

//------------------------------------------------------------------------------
//                          CTors, Assignment, DTor
//------------------------------------------------------------------------------

FragmentedSystem::FragmentedSystem() noexcept = default;

FragmentedSystem::FragmentedSystem(pimpl_pointer pimpl) noexcept :
  m_pimpl_(std::move(pimpl)) {}

FragmentedSystem::FragmentedSystem(const FragmentedSystem& other) :
  m_pimpl_(other.m_pimpl_ ? make_pimpl(*other.m_pimpl_) : nullptr) {}

FragmentedSystem::FragmentedSystem(FragmentedSystem&& other) noexcept = default;

FragmentedSystem& FragmentedSystem::operator=(const FragmentedSystem& rhs) {
    if(&rhs == this) return *this;
    return *this = std::move(FragmentedSystem(rhs));
}

FragmentedSystem& FragmentedSystem::operator=(FragmentedSystem&& rhs) noexcept {
    if(&rhs == this) return *this;
    m_pimpl_ = std::move(rhs.m_pimpl_);
    return *this;
}

FragmentedSystem::~FragmentedSystem() noexcept = default;

//------------------------------------------------------------------------------
//                               Accessors
//------------------------------------------------------------------------------

FragmentedSystem::size_type FragmentedSystem::nfrags() const noexcept {
    if(m_pimpl_) return m_pimpl_->m_frags.size();
    return size_type{0};
}

FragmentedSystem::const_fragment_set_reference FragmentedSystem::frags() const {
    return pimpl_().m_frags;
}

FragmentedSystem::const_fragment_reference FragmentedSystem::fragment(
  size_type i) const {
    const auto n = nfrags();
    if(i >= n)
        throw std::out_of_range("Fragment with index " + std::to_string(i) +
                                " is out of range [0, " + std::to_string(n) +
                                ").");

    return pimpl_().m_frags.at(i);
}

FragmentedSystem::const_capped_reference FragmentedSystem::caps(
  const_fragment_reference f) const {
    return pimpl_().m_frag2caps.at(f);
}

FragmentedSystem::ao_set_type FragmentedSystem::ao_basis_set(
  const_fragment_reference f) const {
    return pimpl_().ao_basis_set(f);
}

FragmentedSystem::size_type FragmentedSystem::n_electrons(
  const_fragment_reference f) const {
    return pimpl_().n_electrons(f);
}

//------------------------------------------------------------------------------
//                                    Utility
//------------------------------------------------------------------------------

bool FragmentedSystem::operator==(const FragmentedSystem& rhs) const noexcept {
    if(m_pimpl_ && rhs.m_pimpl_)
        return *m_pimpl_ == *rhs.m_pimpl_;
    else if(!m_pimpl_ && !rhs.m_pimpl_)
        return true;
    return false;
}

void FragmentedSystem::hash(pluginplay::Hasher& h) const {
    if(m_pimpl_)
        h(*m_pimpl_);
    else
        h(nullptr);
}

//------------------------------------------------------------------------------
//                             Private Members
//------------------------------------------------------------------------------

FragmentedSystem::pimpl_reference FragmentedSystem::pimpl_() {
    if(m_pimpl_) return *m_pimpl_;

    throw std::runtime_error("Instance has no state. Was it default "
                             "constructed or moved from?");
}

FragmentedSystem::const_pimpl_reference FragmentedSystem::pimpl_() const {
    if(m_pimpl_) return *m_pimpl_;

    throw std::runtime_error("Instance has no state. Was it default "
                             "constructed or moved from?");
}

} // namespace ghostfragment
