#######################################################
Systematic Molecular Fragmentation Fragmentation Method
#######################################################

.. |i| replace:: :math:`i`
.. |l|  replace:: :math:`\ell`
.. |A0| replace:: :math:`A_0`
.. |A1| replace:: :math:`A_1`
.. |A1p| replace:: :math:`A_1'`
.. |A2| replace:: :math:`A_2`
.. |A2p| replace:: :math:`A_2'`
.. |Al1| replace:: :math:`A_{\ell -1}`
.. |Al1p| replace:: :math:`A_{\ell - 1}'`
.. |Al| replace:: :math:`A_\ell`
.. |Alp| replace:: :math:`A_\ell'`
.. |Bi| replace:: :math:`B_i`
.. |Bl1| replace:: :math:`B_{\ell -1}`
.. |Bl| replace:: :math:`B_{\ell}`
.. |B1| replace:: :math:`B_1`
.. |B2| replace:: :math:`B_2`
.. |B3| replace:: :math:`B_3`
.. |G|  replace:: :math:`G`
.. |G0| replace:: :math:`G_0`
.. |G1| replace:: :math:`G_1`
.. |G2| replace:: :math:`G_2`
.. |G3| replace:: :math:`G_3`
.. |G4| replace:: :math:`G_4`
.. |G5| replace:: :math:`G_5`
.. |G6| replace:: :math:`G_6`
.. |G7| replace:: :math:`G_7`
.. |F| replace:: :math:`F`
.. |Fi| replace:: :math`F_i`
.. |Fp| replace:: :math`F'`

********************
SMF Fragmentation 05
********************

:cite:t:`Deev2005` introduced a means of fragmenting large covalently bonded
molecules. As originally presented, the SMF fragmentation method was used to
define the fragments, intersections, and energy expansion coefficients. The
procedure is parameterized by a non-zero integer |l| and is refered to as a 
level |l| procedure. Using our terminology the level |l| procedure is:

#. Assign pseudoatoms
#. Establish connectivity, the result is the graph |G0|
#. Find the pseudoatom in |G0| which has the highest degree and that is at least
   |l| edges away from two different pseudoatoms. Define this pseudoatom as 
   |A0|. If no such pseudoatom exists, then |G0| is a fragment and not
   considered further.
#. Let |Bi| be the set of pseduoatoms which are |i| edges away from |A0|. 
   Starting from |B1| select the two pseudoatoms of highest degree. Let these
   pseudoatoms be |A1| and |A1p|.
#. From |B2| select the pseudoatom which has the hightest degree and is
   bonded to |A1|. This is atom |A2|. Similarly, from |B2| select the pseudoatom
   which has the highest degree and is bonded to |A1p|. This is atom |A2p|.
#. Repeat the above for pseudoatoms in |B3| through |Bl1|.
#. Finally from |Bl| select the pseudoatom with the **lowest** degree that is
   bonded to pseudo atom |Al1|; this is atom |Al|. Similarly, |Alp| is the 
   pseudoatom in |Bl| that is bonded to pseudoatom |Al1p|. The result is a 
   path of 2|l| edges that is centered on |A0|.
#. Break the |Al1|-|Al| bond. The resulting graphs are |G1| and |G2|.
#. Break the |Al1p| - |Alp| bond. The resulting graphs are |G3| and |G4|.
#. Break both the |Al1|-|Al| and |Al1p|-|Alp| bonds. The resulting graphs are
   |G5|, |G6|, and |G7|.
#. Let |G| be the set of graphs which is in either the set "|G1|, |G2|, |G3|, 
   |G4|" or the set "|G5|, |G6|, |G7|" (*i.e.* ignore graphs which appear in
   both sets), repeat steps 3-11 for each graph in |G|
#. The previous step terminates when none of the graphs generated in step 11 
   survive step 3 of the next cycle. The resulting set of fragments is |F|.

The original presentation contains a few other details we have omitted, namely:

- How to calculate the coefficients of the fragments; we instead opt to use the
  IEP.  
- Restrictions on what size rings can be broken for a given |l|. The motivation
  for these rules stems from their capping method choice. To be more general we
  instead adopt the view that if a ring shouldn't be broken, it should be 
  protected as a pseudoatom.

*********************
Ring Repair Variation
*********************

In a subsequent paper :cite:t:`Collins2006` ammended the original SMF
fragmentation method to include what they term the "ring repair rule". This
amounts to performing the following steps after the orginal SMF fragmentation
method:

#. For each fragment |Fi| in |F|, consider pairs of pseudoatoms |A0| and |A1|
#. If |A0| and |A1| are both bonded to another pseudoatom |A2|, and |A2| is not 
   in |Fi|, add |A2| to |Fi|
#. If |A0| is bonded to a pseudoatom |A2|, which is not in |Fi|, and |A3| is 
   bonded to a different pseudoatom |A3|, which is also not in |Fi|, then add
   |A2| and |A3| to |Fi| if |A2| and |A3| are bonded.
#. If either of the previous two steps modifies a fragment repeat the original
   SMF fragmentation method with the new set.
