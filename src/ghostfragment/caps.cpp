#include <ghostfragment/caps.hpp>

namespace ghostfragment {

bool Caps::count(const_reference cap) const noexcept {
    for(const auto& x : m_caps_)
        if(x == cap) return true;
    return false;
}

void Caps::add_cap(value_type cap, size_type idx_replaced) {
    m_caps_.push_back(cap);
    m_atom_replaced_.emplace_back(idx_replaced);
}

Caps::const_reference Caps::operator[](size_type i) const noexcept {
    return m_caps_[i];
}

Caps::const_reference Caps::at(size_type i) const {
    assert_offset_(i);
    return m_caps_.at(i);
}

Caps::size_type Caps::replaced_atom(size_type i) const {
    assert_offset_(i);
    return m_atom_replaced_.at(i);
}

void Caps::hash(type::Hasher& h) const { h(m_caps_, m_atom_replaced_); }

bool Caps::operator==(const Caps& rhs) const noexcept {
    return std::tie(m_caps_, m_atom_replaced_) ==
           std::tie(rhs.m_caps_, rhs.m_atom_replaced_);
}

void Caps::assert_offset_(size_type i) const {
    if(i >= size())
        throw std::out_of_range(std::to_string(i) + " is not in the range [0," +
                                std::to_string(size()) + ")");
}

} // namespace ghostfragment
