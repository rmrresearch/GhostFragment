##################
FMO Capping Method
##################

In FMO calculations caps in the traditional sense are not used.

.. |I| replace:: :math:`I`

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

*************
FMO00 Capping
*************

A new capping method was proposed in a subsequent paper :cite:t:`Nakano_2000`,
here denoted FMO00. In this method, for a bond :math:`a-b`, the bonding 
electrons are assigned to one of the two atoms in the bond, say |a|. For 
clarity, we refer to the fragment which gets atom |a| as |A|, and that which 
gets |b| as |B|. |B|'s initial density is computed using the normal AO basis set 
for |B|, with the usual equations. However, |A|'s initial density is computed 
using |A|'s usual basis set augmented with the valence orbitals from |b|. To 
extract the valence orbitals of |b|, a modified version of |A|'s Fock operator 
is used:

.. math::

   \widehat{F}'_A = \widehat{F}_A  + 
                    \sum_{c\in b} \gamma_c\left\mid \mu_c\middle\rangle
                           \middle\langle\mu_c\right\mid


where :math:`widehat{F}_A` is the original Fock operator, :math:`c` runs over
the core orbitals of |b|, :math:`\gamma_c` is a large positive coefficient (
default value is between 10$^6$ and 10$^8$), and
:math:`\mu_c` is the :math:`c`-th atomic core orbital of |b|.