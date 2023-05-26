// #include "detail_/term_pimpl.hpp"
// #include <ghostfragment/equation/equation.hpp>

// namespace ghostfragment::equation {

// Term make_term(typename type::nmer_set::value_type nmer,
//                typename type::fragmented_ao_set::value_type aos,
//                std::size_t n_electrons, Term::coefficient_type coef) {
//     using pimpl_type = detail_::TermPIMPL;

//     auto p = std::make_unique<pimpl_type>(std::move(nmer), std::move(aos),
//                                           n_electrons, coef);

//     return Term(std::move(p));
// }

// } // namespace ghostfragment::equation
