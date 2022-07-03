#include "detail_/fragment_based_method_pimpl.hpp"

namespace ghostfragment {

FragmentBasedMethod::FragmentBasedMethod(pimpl_pointer pimpl) noexcept :
  m_pimpl_(std::move(pimpl)) {}

FragmentBasedMethod::FragmentBasedMethod(nmer_system nmers) :
  FragmentBasedMethod(std::make_unique<pimpl_type>(std::move(nmers))) {}

FragmentBasedMethod::~FragmentBasedMethod() noexcept = default;

} // namespace ghostfragment