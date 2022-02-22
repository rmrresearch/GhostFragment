#pragma once
#include "ghostfragment/types.hpp"

namespace ghostfragment {

/** @brief Class describing a term in the fragment-based method.
 *
 *  Ultimately each fragment-based method comes down to combining a series of
 *  calculations to approximate the supersystem. There are a plethora of ways to
 *  write the resulting equations. For example, a traditional two-body MBE can
 *  be written as:
 *
 *  @f[
 *  E = \sum_{I} E_I + \sum_{I<J}\left(E_{IJ} - E_{I} -E_{J}\right)
 *  @f]
 *
 *  or it can be written as:
 *
 *  @f[
 *  E = \sum_{I<J} E_{IJ} - (N - 2) \sum_{I} E_I
 *  @f]
 *
 *  while these two expressions result in the same energy (modulo the usual
 *  floating point arithmetic caveats) and the same set of unique caclculations,
 *  users may have reasons for favoring one expression format over the other.
 *  For example, the former expression is easier to screen because one simply
 *  neglects the parenthetical term when a pair IJ has been screened out. On
 *  the contrary, the coefficients of the latter expression require the
 *  summation over pairs to include IJ even if the pair IJ has been screened (in
 *  such a case @f$E_{IJ}@f$ is replaced by @f$E_{I} + E_{J}@f$). The situation
 *  gets notable more complicated when ghost atoms and embedding fields are
 *  involved.
 *
 *  To work around this, GhostFragment introduces the concept of a term.
 *  A term wraps a series of inputs and the coefficients to combine them.
 */
class Interaction {
public:
    using nmer_type = typename type::nmers::value_type;

    using const_nmer_reference = const nmer_type&;

    using coefficent_type = double;
};

} // namespace ghostfragment
