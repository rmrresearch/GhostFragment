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

.. _ee_mbe_a:

EE-MB-A
========

One of two charge embedding schemes proposed by :cite:t:`Dahlke2006` for the 
EE-MB method. 

#. Compute charges for the supersystem
#. Let |Qi| be the charge of atom :math:`i`, |Ai|
#. For each |n|-mer, loop over atoms in the supersystem. If |Ai| is not in the
   |n|-mer, place |Qi| at the location of |Ai|

.. _ee_mbe_b:

EE-MB-B
=======

The second embedding scheme proposed by :cite:t:`Dahlke2006`. 

#. Compute charges for each monomer
#. Let |Qi| be the charge of atom :math:`i`, |Ai|
#. For each |n|-mer, loop over atoms in the supersystem. If |Ai| is not in the
   |n|-mer, place |Qi| at the location of |Ai|


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
#. Repeat the previous step until convergence.

Variations
==========

For disjoint fragments the above is straightforward; however, when the fragments
intersect there is some ambiguity as to what the charge of an atom is since it
can appear in multiple fragments. In the context of GEBF :cite:`Li2007` this
ambiguity is resolved by taking the point charges from the fragment which 
resulted from the pseudoatom which contains the atom. This assumes that the GEBF 
fragmentation method has been used.

****************************
Point Charge Recommendations
****************************

In the context of GEBF applied to a medium sized water cluster (the cluster 
contained 22 normal water molecules, 5 hydroxide anions, and 5 hyrodnium 
cations) at the HF/6-311G(d) and MP2/6-311G(d) levels of theory, 
:cite:t:`Li2007` considered how different point charge choices affected how well
GEBF replicated the supersystem calculation. Their results indicate that charges 
derived from a natural population analysis outperformed both Mulliken and 
electrostatic potential derived charges. All three charge schemes were better
than no embedding at all. This study also notes that one iteration was
sufficient to converge the charges. This study also considered water clusters 
and peptides, noting that not including charges leads to large errors (on the
order of 50 mH) relative to the supersystem result.



