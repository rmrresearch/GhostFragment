##########################################
Molecular Tailoring Approach Fragmentation
##########################################

.. |G0| replace:: :math:`G_0`
.. |Gi| replace:: :math:`G_i`
.. |Gi1| replace:: :math:`G_{i+1}`
.. |Li| replace:: :math:`L_i`
.. |Ni| replace:: :math:`N_i`
.. |i| replace:: :math:`i`

*******************
MTA03 Fragmentation
*******************

In the context of MTA, the first fragmentation method presented was introduced
by :cite:t:`Babu2003`. Using our terminology:

#. Generate pseudoatoms (some recommendations were given including :math:`pi`
   bonds, aromatic rings, and functional groups).
#. Assign edges to the pseudoatoms. Let this graph be |G0|.
#. Let |Li| be the set of leaf pseudoatoms in |Gi|. For each pseudoatom in
   |Li|, create a new pseudoatom which contains the original pseudoatom and 
   the pseudoatom it is attached to. The graph resulting from compressing each
   pseudoatom in |Li| is |Gi1|
#. If there are no leaf pseudoatoms in |Gi|, form |Gi1| by removing an edge (the
   original algorithm specifies that it is the first edge contained in the 
   connectivity matrix).
#. Repeat the previous two steps until only isolated pseudoatoms remain.
#. Determine the actual number of atoms in each leaf pseudoatom. Let |Ni| be the 
   number in the :math:`i`-th pseudoatom. 
#. Compare |Ni| to a user-defined range. If |Ni| is in the range than the 
   the |i|-th pseudoatom is a fragment and is removed from the graph.
#. If pseudoatoms remain in the graph, the pseudoatoms are expanded once and the
   previous two steps are repeated with the resulting graph.
#. Expansion terminates when either: all atoms are assigned to fragments, or the 
   original pseudoatoms are recovered.
#. In the event that the original pseudoatoms are recovered the resulting graph
   becomes |G0| and the algorithm returns to step 2.
#. After all atoms are assigned to fragments identify all edges which have been
   severed.
#. For each severed edge grow the graph uniformally from the nodes of the edge
   until the resulting graph is in the target range.

The resulting set of fragments is then postprocessed. This includes:

- Capping severed valencies with hydrogen bonds
- Merging fragments which differ by only a few atoms
- If weak bonds are included as edges, groups of four or less atoms connected to
  a larger fragment via a weak bond are removed from the fragment.
- Close contacts between capping hydrogens are corrected by either removing a
  few more atoms, or by adding more atoms to make the region complete.

.. note::

   Unlike the body of the fragmentation algorithm, the postprocessing steps are
   not described in detail and are thus open to some interpretation.
   

