#include <ghostfragment/nmer_system.hpp>

namespace ghostfragment {
namespace detail_ {

class NMerSystemPIMPL {
public:
    using parent_type       = NMerSystem;
    using capped_nmers      = typename parent_type::capped_nmers;
    using fragment_set_type = typename parent_type::fragmented_system_type;
    using const_fragmented_system_reference =
      typename parent_type::const_fragmented_system_reference;

    NMerSystemPIMPL(capped_nmers nmers, fragment_set_type frags) :
      m_nmers(std::move(nmers)), m_frags(std::move(frags)) {}

    capped_nmers m_nmers;

    fragment_set_type m_frags;
};

} // namespace detail_

namespace {

template<typename... Args>
auto make_pimpl(Args&&... args) {
    return std::make_unique<detail_::NMerSystemPIMPL>(
      std::forward<Args>(args)...);
}

template<typename NMerType>
auto flatten(NMerType&& nmer) {
    const auto& frags = nmer.object();
    auto atom_set     = frags.new_subset();
    for(auto x : nmer) {
        for(auto atom : frags[x]) atom_set.insert(atom);
    }
    return atom_set;
}

} // namespace

// -- CTors and DTors ----------------------------------------------------------

NMerSystem::NMerSystem() noexcept = default;

NMerSystem::NMerSystem(fragmented_system_type frags, capped_nmers nmers) :
  NMerSystem(make_pimpl(std::move(nmers), std::move(frags))) {}

NMerSystem::NMerSystem(pimpl_pointer pimpl) noexcept :
  m_pimpl_(std::move(pimpl)) {}

NMerSystem::NMerSystem(const NMerSystem& other) :
  NMerSystem(other.m_pimpl_ ? make_pimpl(*other.m_pimpl_) : nullptr) {}

NMerSystem::NMerSystem(NMerSystem&& other) noexcept = default;

NMerSystem& NMerSystem::operator=(const NMerSystem& other) {
    if(this != &other) NMerSystem(other).m_pimpl_.swap(m_pimpl_);
    return *this;
}

NMerSystem& NMerSystem::operator=(NMerSystem&& other) noexcept = default;

NMerSystem::~NMerSystem() noexcept = default;

// -- Accessors ----------------------------------------------------------------

NMerSystem::size_type NMerSystem::size() const noexcept {
    if(!m_pimpl_) return 0;
    return pimpl_().m_nmers.size();
}

NMerSystem::const_nmer_reference NMerSystem::nmer(size_type i) const {
    if(i >= size())
        throw std::out_of_range("N-Mer offset must be in range [0, " +
                                std::to_string(size()) + ").");

    auto itr = pimpl_().m_nmers.begin();
    return std::next(itr, i)->first;
}

NMerSystem::const_fragmented_system_reference NMerSystem::fragments() const {
    return pimpl_().m_frags;
}

NMerSystem::ao_set_type NMerSystem::ao_basis_set(
  NMerSystem::const_nmer_reference nmer) const {
    return ao_basis_set(flatten(nmer));
}

NMerSystem::ao_set_type NMerSystem::ao_basis_set(
  NMerSystem::const_fragment_reference frag) const {
    return fragments().ao_basis_set(frag);
}

NMerSystem::size_type NMerSystem::n_electrons(
  NMerSystem::const_nmer_reference nmer) const {
    return n_electrons(flatten(nmer));
}

NMerSystem::size_type NMerSystem::n_electrons(
  NMerSystem::const_fragment_reference frag) const {
    return fragments().n_electrons(frag);
}

// -- Utilities ----------------------------------------------------------------

bool NMerSystem::operator==(const NMerSystem& rhs) const noexcept {
    if(!m_pimpl_ != !rhs.m_pimpl_)
        return false; // One has a PIMPL other doesn't
    else if(!m_pimpl_)
        return true; // Both don't have a PIMPL
    return std::tie(m_pimpl_->m_nmers, m_pimpl_->m_frags) ==
           std::tie(rhs.m_pimpl_->m_nmers, rhs.m_pimpl_->m_frags);
}

void NMerSystem::hash(type::Hasher& h) const {
    if(!m_pimpl_) return;
    h(m_pimpl_->m_nmers, m_pimpl_->m_frags);
}

// -- Private Methods ----------------------------------------------------------

NMerSystem::pimpl_reference NMerSystem::pimpl_() {
    if(m_pimpl_) return *m_pimpl_;
    throw std::runtime_error(
      "Instance has no state. Was it default initialized "
      "or moved from?");
}

NMerSystem::const_pimpl_reference NMerSystem::pimpl_() const {
    if(m_pimpl_) return *m_pimpl_;
    throw std::runtime_error(
      "Instance has no state. Was it default initialized "
      "or moved from?");
}

} // namespace ghostfragment
