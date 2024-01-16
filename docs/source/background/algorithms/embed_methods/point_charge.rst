######################
Point Charge Embedding
######################

.. |Ai| replace:: :math:`A_i`
.. |Qi| replace:: :math:`Q_i`
.. |Fi| replace:: :math:`F_i`
.. |n|  replace:: :math:`n`

*************
Non-Iterative
*************

.. _ec_mfcc_charges:

EC-MFCC Charges
===============

Introduced by :cite:t:`Jiang2006`. The description is a bit vague, but the idea
seems to be to only put charges on the most electronegative/electropositive 
atoms. In the original presentation proteins with charged termini were
fragmented. When a terminus did not show up in the fragment it was replaced by
a point charge. How this would generalize to other systems is not immediately
clear.

.. _ee_mb_a:

EE-MB-A
========

One of two charge embedding schemes proposed by :cite:t:`Dahlke2006` for the 
EE-MB method. 

#. Compute charges for the supersystem
#. Let |Qi| be the charge of atom :math:`i`, |Ai|
#. For each |n|-mer, loop over atoms in the supersystem. If |Ai| is not in the
   |n|-mer, place |Qi| at the location of |Ai|

.. _ee_mb_b:

EE-MB-B
=======

The second embedding scheme proposed by :cite:t:`Dahlke2006`. 

#. Compute charges for each monomer
#. Let |Qi| be the charge of atom :math:`i`, |Ai|
#. For each |n|-mer, loop over atoms in the supersystem. If |Ai| is not in the
   |n|-mer, place |Qi| at the location of |Ai|

.. _iterative_point_charge_embedding:

********************************
Iterative Point Charge Embedding
********************************

Iterative point charge embedding requires the use of point charges that in some
shape or form respond to changes in the electronic structure. Typically this
means one:

#. Compute point charges for each fragment in vacuum
#. Recompute the point charges for each fragment. This time instead of 
   neglecting atoms outside the fragment, replace them with their computed point
   charge.
#. Repeat the previous step until convergence or for a set number of iterations

Variations
==========

For disjoint fragments the above is straightforward; however, when the fragments
intersect there is some ambiguity as to what the charge of an atom is since it
can appear in multiple fragments. In the context of GEBF :cite:`Li2007` this
ambiguity is resolved by taking the point charges from the fragment which 
resulted from the pseudoatom which contains the atom. This assumes that the GEBF 
fragmentation method has been used.

.. _screened_charge_model:

*********************
Screened Charge Model
*********************

.. |Qis| replace:: :math:`q_i^*\left(r_i\right)`
.. |ri| replace:: :math:`r_i`
.. |i| replace:: :math:`i``
.. |zi| replace:: :math:`Z_i`
.. |Zei| replace:: :math:`\zeta_{z_i}`

In the context of the EE-MB method, :cite:t:`Tempkin_2011` introduced a screened
point charge. For the |i|-th atom, |Ai|, the screened charge at a distance |ri|
from |Ai|, |Qis|, is given by:

.. math::
   \newcommand{\zi}{Z_i}
   \newcommand{\Zei}{\zeta_{\zi}}
   \newcommand{\ri}{r_i}
   \newcommand{\fi}{f\left(\Zei\ri\right)}

   Q_i^*(\ri) = Q_i + m \fi\exp\left(-2\Zei\ri\right)
   
where:

- |Qi| is the unscreened charge of |Ai|
- :math:`m` is the number of electrons in the orbital
- |zi| is the atomic number of |Ai|
- |Zei| is the exponent of the Slater orbital, and
- :math:`f` is a polynomial that depends on the principal quantum number of |Ai|

N.B. the details of the polynomial, as well as values for |Zei| are given in
:cite:`Wang2010`.
