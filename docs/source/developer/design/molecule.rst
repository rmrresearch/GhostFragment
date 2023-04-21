######################################
Designing the FragmentedMolecule Class
######################################

***************************************
FragmentedMolecule Class Considerations
***************************************

.. _fs_molecule:

Molecule class.
   Chemist defines the ``Molecule`` class. 

Caps.
  
Charge and multiplicity.


Ignored Considerations
======================

.. |phi_set| replace:: :math:`\left\lbrace\phi_i\right\rbrace`

AO Basis Set.
   It is almost always assumed that if |phi_set| is the atomic basis set
   for atom :math:`i` in the :ref:`supersystem`, then |phi_set| is also the
   atomic basis set for atom :math:`i` in each fragment. In other words, the
   molecular basis set is fragmented in the same way as the :ref:`supersystem`.
   Thus if we know how to generate |phi_set| for any given atom, it is trivial
   to assemble the molecular basis set for a given fragment. This is one reason
   why we do not worry about storing the AO basis set in the 
   ``FragmentedMolecule`` class. Another reason is to parallel the un-fragmented
   hierarchy where ``Molecule`` and ``AOBasisSet`` are separate classes.


    