.. _gf_fragmented_system_driver_design:

#################################################
Designing GhostFragment's FragmentedSystem Driver
#################################################

.. |n| replace:: :math:`n`

The purpose of this page is to capture the design process of GhostFragment's
FragmentedSystem Driver.

**********************************
What is a FragmentedSystem Driver?
**********************************

In our design, the FragmentedSystem driver is charged with going from the
input chemical system, to the final set of (sub-) chemical systems. 

**************************************
FragmentedSystem Driver Considerations
**************************************

.. _fsd_accuracy:

Accuracy
   From :ref:`gf_input_driver_design` we know the ``FragmentedSystem`` driver
   is responsible for creating the final set of subsystems and must be able to
   determine those subsystems in a manner which accounts for all important
   interactions.

.. _fsd_hierarchical:

Hierarchical
   The ChemicalSystem class is a hierarchical class. The ``FragmentedSystem``
   class is also hierarchical. Being able to create a hierachical driver allows
   us to mirror the hierarchical structure found in both the inputs and the
   results.

   - Ultimately fragments are defined by the nuclei. Exactly how the fragments
     are formed is decoupled from the process of creating a ``FragmentedSystem``
     by having the inputs be an already created ``FragmentedNuclei`` object.

.. _fsd_embedding:

Embedding.
   From :ref:`fsd_hierarchical` we note that the field component of the
   ``ChemicalSystem`` class is the new component relative to the ``Molecule``
   class. The ``FragmentedSystem`` driver should then be responsible for
   assigning fields to each subsystem in a ``FragmentedMolecule`` instance.
   

******************************
FragmentedSystem Driver Design
******************************

.. _fig_gf_fragmented_system_driver:

.. figure:: assets/fragmented_system_driver.png
   :align: center

   High-level overivew of the components of the ``FragmentedSystem`` driver.

:numref:`fig_gf_fragmented_system_driver` shows the high-level design of the
Fragmentedsystem driver. Because of :ref:`fsd_hierarchical` the first step of 
the driver is to form a ``FragmentedMolecule`` (the class one rung lower in
the ``FragmentedSystem`` hierarchy) from the input ``FragmentedNuclei`` and
supersystem. The next step of the driver is to determine a field for each 
fragment in the ``FragmentedMolecule``, which in turn addresses consideration 
:ref:`fsd_embedding`.

At this stage, consideration :ref:`fsd_accuracy` is primarily punted to the
``FragmentedMolecule`` driver, although the field driver is able to recover
some of the electorstatic and potentially polarization effects missed by the
fragments.
