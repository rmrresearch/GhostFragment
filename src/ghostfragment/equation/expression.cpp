/*
 * Copyright 2024 GhostFragment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// #include "detail_/expression_pimpl.hpp"

// namespace ghostfragment::equation {

// // -- Ctors, Assignment Operators, Dtor

// Expression::Expression() noexcept = default;

// Expression::Expression(pimpl_pointer pimpl) noexcept :
//   m_pimpl_(std::move(pimpl)) {}

// Expression::Expression(const Expression& other) :
//   m_pimpl_(!other.empty() ? other.m_pimpl_->clone() : nullptr) {}

// Expression::Expression(Expression&& other) noexcept = default;

// Expression& Expression::operator=(const Expression& rhs) {
//     if(this != &rhs) { Expression(rhs).swap(*this); }
//     return *this;
// }

// Expression& Expression::operator=(Expression&& rhs) noexcept = default;

// Expression::~Expression() noexcept = default;

// // -- Getters

// Expression::size_type Expression::size() const noexcept {
//     return !empty() ? m_pimpl_->m_terms.size() : 0;
// }

// Expression::const_term_reference Expression::at(size_type i) const {
//     assert_bounds_(i);
//     return m_pimpl_->m_terms[i];
// }

// // -- Setters

// void Expression::add_term(term_type term) {
//     if(!m_pimpl_) std::make_unique<pimpl_type>().swap(m_pimpl_);
//     m_pimpl_->m_terms.emplace_back(std::move(term));
// }

// // -- Utility

// bool Expression::empty() const noexcept { return
// !static_cast<bool>(m_pimpl_); }

// void Expression::swap(Expression& other) noexcept {
//     m_pimpl_.swap(other.m_pimpl_);
// }

// bool Expression::operator==(const Expression& rhs) const noexcept {
//     // Check if one is empty and other isn't
//     if(empty() != rhs.empty()) return false;

//     // Both are either empty or not empty, return if empty
//     if(empty()) return true;

//     return std::tie(m_pimpl_->m_terms) == std::tie(rhs.m_pimpl_->m_terms);
// }

// // -- Private Methods

// void Expression::assert_bounds_(size_type i) const {
//     if(i < size()) return;

//     throw std::out_of_range("Offset " + std::to_string(i) +
//                             " is not in the range [0, " +
//                             std::to_string(size()) + ").");
// }

// } // namespace ghostfragment::equation
