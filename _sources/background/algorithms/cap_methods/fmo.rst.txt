##################
FMO Capping Method
##################

.. note::

   The information in this section is my interpretation of the cited references.
   In many cases the descriptions of the algorithms provided in the literature
   are somewhat vague. Thus what is in this section may not accurately reflect 
   how the underlying implementations actually work. Please feel free to
   contribute and make this section more accurate.

In FMO calculations caps in the traditional sense are not used.

.. |I| replace:: :math:`I`

.. _fmo99_capping:

*************
FMO99 Capping
*************

The initial FMO capping method :cite:t:`Kitaura1999`, here labeled as FMO99, 
assigned electrons unevenly to the fragments (*i.e.*, one of the fragments gets 
both of the bonding electrons). From this assignment, an initial density for 
fragment |I| is obtained by:

#. Defining a reference system (no guidance on how to do this was provided)
#. Localizing the molecular orbitals of the reference system to the atoms in |I|

   - The relevant atoms must have the same geometry in both the reference system
     and the target system

#. Discarding contributions to the molecular orbitals from atoms outside |I|
#. Renormalizing the molecular orbitals
#. Use the renormalized MOs to form a n-electron density (n depending on how
   the electrons are assigned)

.. |a| replace:: :math:`a`
.. |A| replace:: :math:`A`
.. |b| replace:: :math:`b`
.. |B| replace:: :math:`B`

.. _fmo00_capping:

*************
FMO00 Capping
*************

.. note::

   The language describing the FMO00 method :cite:t:`Nakano_2000` uses is: 
   "core" and "valence" orbitals; however, based on subsequent publications, 
   such as :cite:t:`Fedorov2004a`, I believe what they are actually referring to
   would typically be termed "occupied" and "virtual" orbitals, respectively. 
   The language in this section reflects this assumption.

A new capping method was proposed in a subsequent paper :cite:t:`Nakano_2000`,
here denoted FMO00. In this method, for a bond :math:`a-b`, the bonding 
electrons are assigned to one of the two atoms in the bond, say |a|. For 
clarity, we refer to the fragment which gets atom |a| as |A|, and that which 
gets |b| as |B|. |B|'s initial density is computed using the normal AO basis set 
for |B|, with the usual equations. However, |A|'s initial density is computed 
using |A|'s usual basis set augmented with the virtual orbitals from |b|. To 
extract the virtual orbitals of |b|, a modified version of |A|'s Fock operator 
is used:

.. math::

   \widehat{F}'_A = \widehat{F}_A  + 
                    \sum_{i\in b} \gamma_i\Ket{i}\Bra{i}


where :math:`widehat{F}_A` is the original Fock operator, :math:`i` runs over
the occupied orbitals of |b|, :math:`\gamma_i` is a large positive coefficient (
default value is between 10$^6$ and 10$^8$), and :math:`\Ket{i}` is the 
:math:`i`-th occupied orbital of |b|. In practice orbital :math:`\Ket{i}` is 
only decribed by the AOs on the |b|, which is to say, that after localizing 
:math:`\ket{i}` only the matrix elements :math:`C_{\mu i}` where :math:`\mu` is
on |b| are kept.

.. _fmo04_capping:

*************
FMO04 Capping
*************

In describing a three-body FMO method :cite:t:`Fedorov2004a`, a new capping 
method was pitched which is effectively a combination of :ref:`fmo99_capping`
and :ref:`fmo00_capping`. In this study all severed bonds were carbon-carbon 
bonds. Thus the decision was made to use the occupied orbitals of a methane 
molecule instead of the actual occupied orbitals. The methane orbitals were 
split so that one atom, call it |a|, gets one of the :math:`sp^3` orbitals 
(specifically the :math:`sp^3` orbital along the bond) and the other atom, call 
it |b|, gets the remaining four occupied orbitals. For a given bond, the 
decision of which atom is |a| versus which atom is |b| was made so that |a| went 
to the fragment with the smaller ordinal number (presumably the ordinal number 
was assigned based on user input, but this point was not clarified).