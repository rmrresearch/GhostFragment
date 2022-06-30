.. _DCLC_fragmentation_method:

#########################################################
Divide and Conquer Local Correlation Fragmentation Method
#########################################################

.. |P| replace:: :math:`P`

:cite:t:`Li2004` presented the DCLC fragmentation method. Using our terminology
this method works by:

#. Form pseudoatoms
#. Establish pseudoatom connectivity
#. For each pseudoatom |P|, create a fragment which is comprised of |P| and
   the pseudoatoms bonded to |P|. 

The original manuscript also derives a corresponding energy equation; however, the
equation is just a 1-body GMBE which uses the fact that intersections are at
most pairwise.