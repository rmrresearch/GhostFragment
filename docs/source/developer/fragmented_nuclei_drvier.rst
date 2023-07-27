.. _gf_designing_the_fragmented_nuclei_driver:

######################################
Designing the Fragmented Nuclei Driver
######################################

**************************************
FragmentedNuclei Driver Considerations
**************************************

.. fd_pseudoatoms:

Pseudoatoms
   No matter how the system is decomposed there is always some most
   fundamental units called :ref:`pseudoatom`. The first step of the
   fragmentation process is to create pseudoatoms.

Molecular graph
   While not strictly needed for all fragmentation algorithms, many require
   us to know the connectivity of the system. Even when connectivity is not
   needed, it is still helpful from an algorithmic perspective. We are
   interested primarily in connectivity among pseudoatoms, with two
   pseudoatoms being connected if a covalent bond exists between them.

   - Non-covalent bonds are best treated elsewhere, since severing an 
     :ref:`edge` will end up implying the need for a cap.