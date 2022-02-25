#include "ghostfragment/fragmented_system.hpp"
#include "ghostfragment/types.hpp"

namespace ghostfragment {
namespace detail_ {

// This PIMPL just stores the input in the same form that it comes into
// FragmentedSystem
struct FragmentedSystemPIMPL {
    using parent_type           = FragmentedSystem;
    using fragment_set_type     = parent_type::fragment_set_type;
    using atom_to_ao_basis_type = parent_type::nucleus_to_ao_basis_type;
    using atom2nelectron_type   = parent_type::atom2nelectron_type;

    FragmentedSystemPIMPL(fragment_set_type frags, atom_to_ao_basis_type f2ao,
                          atom2nelectron_type a2e) :
      m_frags(std::move(frags)),
      m_atom2aos(std::move(f2ao)),
      m_atom2ne(std::move(a2e)) {}

    bool operator==(const FragmentedSystemPIMPL& rhs) const noexcept {
        return std::tie(m_frags, m_atom2aos, m_atom2ne) ==
               std::tie(rhs.m_frags, rhs.m_atom2aos, rhs.m_atom2ne);
    }

    void hash(type::Hasher& h) const { h(m_frags, m_atom2aos, m_atom2ne); }

    fragment_set_type m_frags;

    atom_to_ao_basis_type m_atom2aos;

    atom2nelectron_type m_atom2ne;
};

} // namespace detail_

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

FragmentedSystem::FragmentedSystem(fragment_set_type frags,
                                   nucleus_to_ao_basis_type atom2aos,
                                   atom2nelectron_type atom2ne) :
  m_pimpl_(
    make_pimpl(std::move(frags), std::move(atom2aos), std::move(atom2ne))) {}

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

FragmentedSystem::const_fragment_reference FragmentedSystem::fragment(
  size_type i) const {
    const auto n = nfrags();
    if(i >= n)
        throw std::out_of_range("Fragment with index " + std::to_string(i) +
                                " is out of range [0, " + std::to_string(n) +
                                ").");

    return m_pimpl_->m_frags.at(i);
}

FragmentedSystem::fragment_basis_type FragmentedSystem::ao_basis_set(
  const_fragment_reference f) const {
    assert_frag_(f);
    const auto& atoms2aos = m_pimpl_->m_atom2aos;

    // TODO: revist when Chemist#284 is handled
    if(atoms2aos.empty())
        throw std::runtime_error("No AOs have been assigned!!!!");
    const auto& mol     = f.object();
    const auto& all_aos = atoms2aos.begin()->second.object();

    type::fragmented_aos temp(all_aos);
    auto rv = temp.new_subset();

    for(const auto& x : f) {
        auto atom_set = m_pimpl_->m_frags.new_subset();
        atom_set.insert(x);
        rv += atoms2aos.at(atom_set);
    }
    return rv;
}

FragmentedSystem::size_type FragmentedSystem::n_electrons(
  const_fragment_reference f) const {
    assert_frag_(f);

    size_type n = 0;
    for(const auto& atom_idx : f) { n += m_pimpl_->m_atom2ne[atom_idx]; }
    return n;
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
    if(m_pimpl_) h(*m_pimpl_);
    h(nullptr);
}

//------------------------------------------------------------------------------
//                             Private Members
//------------------------------------------------------------------------------

void FragmentedSystem::assert_frag_(const_fragment_reference f) const {
    if(m_pimpl_) {
        for(const auto& x : m_pimpl_->m_frags)
            if(x == f) return;
    }
    throw std::out_of_range("Provided fragment is not part of this fragmented "
                            "system");
}

} // namespace ghostfragment
