
.. _fea_frag_method:

########################
FEA Fragmentation Method
########################

.. |I| replace:: :math:I`
.. |Pi| replace:: :math:`P_I`
.. |R| replace:: :math:`R`

Introduced by :cite:t:`Li2005b` as an extension of the 
:ref:`DCLC_fragmentation_method` method.
The FEA fragmentation algorithm is quite simple:

#. Divide the system into pseudoatoms
#. Let |PI| be the |I|-th pseudoatom, fragment |I| consists of |PI| and all
   pseudoatoms that are within some distance |R| of |PI|

   - How the distance is measured is not discussed.
   - A value of 2.5 Angstroms is recommended for |R|

The difference between the FEA fragmentation algorithm and the DCLC 
fragmentation method is that the former uses distances, whereas the latter uses
connectivity.