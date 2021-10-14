######################
Point Charge Embedding
######################

.. |Ai| replace:: :math:`A_i`
.. |Fi| replace:: :math:`F_i`

*************
Non-Iterative
*************



*********
Iterative
*********

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



