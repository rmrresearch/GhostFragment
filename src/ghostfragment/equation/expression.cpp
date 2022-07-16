#include "detail_/expression_pimpl.hpp"

namespace ghostfragment::equation {

Expression::Expression(pimpl_pointer pimpl) noexcept :
  m_pimpl_(std::move(pimpl)) {}

Expression::~Expression() noexcept = default;

} // namespace ghostfragment::equation