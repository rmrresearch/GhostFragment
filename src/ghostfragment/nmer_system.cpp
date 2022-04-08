#include <ghostfragment/nmer_system.hpp>

namespace ghostfragment {
namespace detail_ {

class NMerSystemPIMPL {
public:
    using parent_type       = NMerSystem;
    using nmers_type        = typename parent_type::nmer_set_type;
    using fragment_set_type = typename parent_type::fragmented_system_type;
    using const_fragmented_system_reference =
      typename parent_type::const_fragmented_system_reference;

    NMerSystemPIMPL(nmers_type nmers, fragment_set_type frags) :
      m_nmers(std::move(nmers)), m_frags(std::move(frags)) {}

    nmers_type m_nmers;

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

NMerSystem::NMerSystem(fragmented_system_type frags, nmer_set_type nmers) :
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
    return *std::next(itr, i);
}

bool NMerSystem::count(const_nmer_reference nmer) const noexcept {
    if(!m_pimpl_) return false;
    for(const auto& nmer_i : pimpl_().m_nmers)
        if(nmer_i == nmer) return true;
    return false;
}

NMerSystem::const_fragmented_system_reference NMerSystem::fragments() const {
    return pimpl_().m_frags;
}

NMerSystem::ao_set_type NMerSystem::ao_basis_set(
  NMerSystem::const_nmer_reference nmer) const {
    pimpl_();
    assert_nmer_(nmer);
    if(nmer.size() == 0) throw std::runtime_error("TODO: N==0 not coded");

    auto itr = nmer.begin();
    auto rv  = ao_basis_set(fragments().fragment(*itr));
    ++itr;
    for(; itr != nmer.end(); ++itr) {
        rv += ao_basis_set(fragments().fragment(*itr));
    }

    return rv;
}

NMerSystem::ao_set_type NMerSystem::ao_basis_set(
  NMerSystem::const_fragment_reference frag) const {
    return fragments().ao_basis_set(frag);
}

NMerSystem::size_type NMerSystem::n_electrons(
  NMerSystem::const_nmer_reference nmer) const {
    pimpl_();
    assert_nmer_(nmer);
    size_type rv = 0;

    for(const auto frag_i : nmer) {
        rv += n_electrons(fragments().fragment(frag_i));
    }

    return rv;
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

void NMerSystem::assert_nmer_(const_nmer_reference nmer) const {
    if(count(nmer)) return;
    throw std::out_of_range("N-mer is not in current instance");
}

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
