// #include "detail_/term_pimpl.hpp"

// namespace ghostfragment::equation {

// Term::Term() noexcept = default;

// Term::Term(pimpl_pointer pimpl) noexcept : m_pimpl_(std::move(pimpl)) {}

// Term::Term(const Term& other) :
//   m_pimpl_(other.m_pimpl_ ? other.m_pimpl_->clone() : nullptr) {}

// Term::Term(Term&& other) noexcept = default;

// Term& Term::operator=(const Term& rhs) {
//     if(this != &rhs) { Term(rhs).swap(*this); }
//     return *this;
// }

// Term& Term::operator=(Term&& rhs) noexcept = default;

// Term::~Term() noexcept = default;

// Term::molecule_type Term::molecule() const {
//     assert_pimpl_();
//     return m_pimpl_->molecule();
// }

// Term::size_type Term::n_electrons() const noexcept {
//     return empty() ? 0 : m_pimpl_->m_n_electrons;
// }

// Term::chemical_system_type Term::chemical_system() const {
//     auto mol       = molecule();
//     const auto n_e = n_electrons();
//     return chemical_system_type(std::move(mol), n_e);
// }

// Term::ao_basis_set_type Term::ao_basis_set() const {
//     assert_pimpl_();
//     return m_pimpl_->ao_basis_set();
// }

// Term::coefficient_type Term::coefficient() const {
//     assert_pimpl_();
//     return m_pimpl_->m_coef;
// }

// // -- Utility Methods

// bool Term::empty() const noexcept { return !static_cast<bool>(m_pimpl_); }

// void Term::swap(Term& other) noexcept { m_pimpl_.swap(other.m_pimpl_); }

// bool Term::operator==(const Term& rhs) const noexcept {
//     // Check if one is empty and the other isn't
//     if(empty() != rhs.empty()) return false;

//     // Either both filled, or both emtpy, return if latter
//     if(empty()) return true;

//     return *m_pimpl_ == *rhs.m_pimpl_;
// }

// // -- Private Methods

// void Term::assert_pimpl_() const {
//     if(!empty()) return;
//     throw std::runtime_error("Term is empty. Did you default construct it or "
//                              "move from it?");
// }

// // -- Related Methods

// std::ostream& operator<<(std::ostream& os, const Term& t) {
//     if(t.empty()) return os << "{empty}";
//     return os << t.molecule() << std::endl << t.coefficient();
// }

// } // namespace ghostfragment::equation
