.. _gf_fragmented_nuclei_driver_design:

##################################################
Designing GhostFragment's FragmentedNuclei Driver
##################################################

************************************
What is the FragmentedNuclei Driver?
************************************

The ``FragmentedNuclei`` driver is responsible for dividing the nuclei of a
molecular system into fragments. The resulting fragments will then be further
processed by the ``FragmentedMolecule`` driver.

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
   to vary the most among existing fragment methods. Many existing fragment-
   based methods differ only in how the initial fragments are formed.

******************************
FragmentedNuclei Driver Design
******************************

.. _fig_gf_fragmented_nuclei_driver:

.. figure:: assets/fragmented_nuclei_driver.png
   :align: center

   The architecture of the ``FragmentedNuclei`` Driver. 

:numref:`fig_gf_fragmented_nuclei_driver` shows the main pieces of the
``FragmentedNuclei`` driver. While the input to the driver may reasonably be
expected to be a ``Nuclei`` object, the actual input to the driver is a
``Molecule`` object. This is because the driver may conceivably need the charge
of the system to assign connectivity