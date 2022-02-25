#include "ghostfragment/fragmented_system.hpp"
#include "ghostfragment/types.hpp"

namespace ghostfragment {
namespace detail_ {

// This PIMPL just stores the input in the same form that it comes into
// FragmentedSystem
struct FragmentedSystemPIMPL {
    using parent_type = FragmentedSystem;

    using fragment_set_type        = parent_type::fragment_set_type;
    using fragment_type            = parent_type::fragment_type;
    using const_fragment_reference = parent_type::const_fragment_reference;

    using nucleus_to_ao_set_type = parent_type::nucleus_to_ao_basis_type;
    using ao_set_type            = parent_type::ao_set_type;

    using size_type = parent_type::size_type;

    using atom2nelectron_type = parent_type::atom2nelectron_type;

    FragmentedSystemPIMPL(fragment_set_type frags, nucleus_to_ao_set_type f2ao,
                          atom2nelectron_type a2e) :
      m_frags(std::move(frags)),
      m_atom2aos(std::move(f2ao)),
      m_atom2ne(std::move(a2e)) {}

    bool operator==(const FragmentedSystemPIMPL& rhs) const noexcept {
        return std::tie(m_frags, m_atom2aos, m_atom2ne) ==
               std::tie(rhs.m_frags, rhs.m_atom2aos, rhs.m_atom2ne);
    }

    void hash(type::Hasher& h) const { h(m_frags, m_atom2aos, m_atom2ne); }

    // Wraps process of going from an atom index to a "fragment"
    fragment_type atom2frag(size_type i) const {
        auto rv = m_frags.new_subset();
        rv.insert(i);
        return rv;
    }

    ao_set_type ao_basis_set(const_fragment_reference f) const {
        // TODO: revist when Chemist#284 is handled
        if(m_atom2aos.empty())
            throw std::out_of_range("No AOs have been assigned!!!!");

        const auto& mol_in = f.object();
        const auto& mol    = m_atom2aos.begin()->first.object();
        if(mol_in != mol)
            throw std::out_of_range("Atoms don't belong to this supersystem");

        const auto& all_aos = m_atom2aos.begin()->second.object();

        type::fragmented_aos temp(all_aos);
        auto rv = temp.new_subset();

        for(const auto& x : f) rv += m_atom2aos.at(atom2frag(x));
        return rv;
    }

    size_type n_electrons(const_fragment_reference f) const {
        if(f.object() != m_frags.object())
            throw std::out_of_range("Atoms don't belong to this superset");

        size_type n = 0;
        for(const auto& atom_idx : f) { n += m_atom2ne.at(atom_idx); }
        return n;
    }

    fragment_set_type m_frags;

    nucleus_to_ao_set_type m_atom2aos;

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

    return pimpl_().m_frags.at(i);
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
