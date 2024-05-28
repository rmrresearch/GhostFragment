.. Copyright 2024 GhostFragment
..
.. Licensed under the Apache License, Version 2.0 (the "License");
.. you may not use this file except in compliance with the License.
.. You may obtain a copy of the License at
..
.. http://www.apache.org/licenses/LICENSE-2.0
..
.. Unless required by applicable law or agreed to in writing, software
.. distributed under the License is distributed on an "AS IS" BASIS,
.. WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
.. See the License for the specific language governing permissions and
.. limitations under the License.

.. _gf_designing_fragmented_molecule_driver:

#######################################
Designing the FragmentedMolecule Driver
#######################################

.. |n| replace:: :math:`n`

This page captures the design process of the ``FragmentedMolecule`` driver
component of GhostFragment.

**************************************
What is the FragmentedMolecule Driver?
**************************************

The first step of the :ref:`gf_fragmented_system_driver_design` required
creating a ``FragmentedMolecule`` object. The responsibility for creating that
object was punted to the ``FragmentedMolecule`` driver. The 
``FragmentedMolecule`` driver is responsible for taking a ``ChemicalSystem`` as
input and returning a ``FragmentedMolecule`` object.

****************************************
FragmentedMolecule Driver Considerations
****************************************

Accuracy
   :ref:`gf_fragmented_system_driver_design` punted most of the responsibility 
   for ensuring the set of fragments captures all important interactions to
   the ``FragmentedMolecule`` driver. At this stage this primarily will entail
   ensuring that severed bonds are dealt with correctly.

.. _fmd_hierarchical:

Hierarchical
   Like the ``FragmentedSystem`` driver we again want the ``FragmentedMolecule``
   driver to be designed in a hierchical manner that mirrors the hierarchy of
   the ``ChemicalSystem`` and ``FragmentedSystem`` classes. For the 
   ``FragmentedMolecule`` driver this means turning a ``FragmentedNuclei``
   object into a ``FragmentedMolecule``.

.. _fmd_capping:

Capping
   Severing a covalent bond leads to very large perturbations. The severed
   bond must be dealt with in some manner. 

   - Capping must be done before charges/multiplicities can be assigned.
   - By doing the capping at the ``Molecule``-level we are able to distinguish
     between the "real" atoms (those which are also part of the supersystem)
     and the caps, since the former live in the ``FragmentedNuclei`` object and
     the latter live in the ``FragmentedMolecule`` object.

.. _fmd_charge_mult:

Charge and multiplicity
   Relative to the ``Nuclei`` class the ``Molecule`` class adds the charge and
   multiplicity. The ``FragmentedMolecule`` class is similar in that it adds
   to the ``FragmentedNuclei`` class a set of charges and multiplicities,
   namely the charge and multiplicity of each fragment.

.. _fmd_nmers:

|n|-mers
   From the perspective of the GMBE, there is no real destinction between 
   fragments and |n|-mers. Ultimately, the coefficients we need for the final
   energy expression simply depend on the overlaps of the final subsystems we
   want to run computations on. The ``FragmentedMolecule`` driver should be
   designed so that the the ``FragmentedNuclei`` which enter into it could be
   either fragments or |n|-mers.

********************************
FragmentedMolecule Driver Design
********************************

.. _fig_gf_fragmented_molecule_driver:

.. figure:: assets/fragmented_molecule_driver.png
   :align: center

   The architecture of the ``FragmentedMolecule`` Driver. 

:ref:`fig_gf_fragmented_molecule_driver` shows the architecture of the
``FragmentedMolecule`` driver. Following from consideration 
:ref:`fmd_hierarchical`, the inputs to the driver is a ``FragmentedNuclei`` 
object. The input fragments will in general
contain broken bonds. As stated in consideration :ref:`fmd_capping` we need
to address the broken bonds before we can accurately assign charges and
multiplicities to the fragments. Once we have capped fragments, the final
step in creating a ``FragmentedMolecule`` object is to assign the charges and
multiplicities to the fragments, satisfying :ref:`fmd_charge_mult`.