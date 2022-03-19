#pragma once
#include <ghostfragment/types.hpp>

namespace ghostfragment {

class Caps {
private:
    using cap_set_type = type::nuclei_set;

public:
    /// A type like chemist::Atom
    using value_type = cap_set_type::value_type;

    /// Type of a read-only reference to a cap
    using const_reference = const value_type&;

    /// An unsigned integer type
    using size_type = cap_set_type::size_type;

    size_type size() const noexcept { return m_caps_.size(); }

    bool count(const_reference cap) const;

    void add_cap(value_type cap, size_type idx_replaced);

    const_reference operator[](size_type i) const { return m_caps_[i]; }

    const_reference at(size_type i) const { return m_caps_.at(i); }

    size_type replaced_atom(size_type i) const {
        return m_atom_replaced_.at(i);
    }

    bool operator==(const Caps& rhs) const noexcept;

    void hash(type::Hasher& h) const;

private:
    cap_set_type m_caps_;
    std::vector<size_type> m_atom_replaced_;
};

inline bool operator!=(const Caps& lhs, const Caps& rhs) noexcept {
    return !(lhs == rhs);
}

inline bool Caps::count(const_reference cap) const {
    for(const auto& x : m_caps_)
        if(x == cap) return true;
    return false;
}

inline void Caps::add_cap(value_type cap, size_type idx_replaced) {
    m_caps_.push_back(cap);
    m_atom_replaced_.emplace_back(idx_replaced);
}

inline void Caps::hash(type::Hasher& h) const { h(m_caps_, m_atom_replaced_); }

inline bool Caps::operator==(const Caps& rhs) const noexcept {
    return std::tie(m_caps_, m_atom_replaced_) ==
           std::tie(rhs.m_caps_, rhs.m_atom_replaced_);
}

} // namespace ghostfragment