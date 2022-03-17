.. _mfcc_frag_method:

#########################
MFCC Fragmentation Method
#########################

.. |pi| replace:: :math:`P_I`
.. |I| replace:: :math:`I`

While the original MFCC fragmentation method was defined in terms of amino acids
it's straightforward to generalize it to arbitrary molecules. Using our 
terminology:

#. Form pseudoatoms, letting |pi| be the |I|-th pseudoatom
#. The |I|-th fragment consists of |pi| and the atoms bonded to it.

The original application of this fragmentation method defined each amino acid of
the proteins to be a pseudoatom, which in turn amounted to fragmenting the
peptide bonds. This amounts to adding a :math:`-NH_2` cap to the :math:`\alpha` 
carbon of the bond and a  :math:`-RCH2` group to the nitrogen of the peptide 
bond (R being the side chain of the amino acid the cap is replacing).