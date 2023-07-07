.. _gf_fragmented_nuclei_driver_design:

##################################################
Designing GhostFragment's FragmentedNuclei Driver
##################################################

************************************
What is the FragmentedNuclei Driver?
************************************

**************************************
FragmentedNuclei Driver Considerations
**************************************

.. _fnd_hierarchy_base:

Hierarchy base
   The ``FragmentedNuclei`` driver is assumed to be the base driver of 
   the ``FragmentedNuclei``, ``FragmentedMolecule``, and ``FragmentedSystem``
   hierarchy.

.. _fnd_psudoatoms:

Pseudoatoms
   As the base of the hierarchy, the ``FragmentedNuclei`` driver's first task
   is to determine the set of :ref:`pseudoatom` s which will be used to form
   fragments.

.. _fnd_connectivity:

Connectivity
   The majority of fragmentation algorithms need not just a set of pseudoatoms,
   but also the connectivity of those pseudoatoms.

.. _fnd_generality:

Generality
   The ``FragmentedNuclei`` driver is envisioned as being the piece which needs
   to vary the most among existing fragment methods.

******************************
FragmentedNuclei Driver Design
******************************

.. _fig_gf_fragmented_nuclei_driver:

.. figure:: assets/fragmented_nuclei_driver.png
   :align: center

   The architecture of the ``FragmentedNuclei`` Driver. 