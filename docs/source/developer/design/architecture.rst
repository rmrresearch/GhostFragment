.. Copyright 2025 GhostFragment
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

.. _gf_architecture:

##########################
GhostFragment Architecture
##########################

The current architecture of GhostFragment is shown in :numref:`fig_gf_arch`.

.. _fig_gf_arch:

.. figure:: assets/overview2.png
   :alt: Architecture diagram of GhostFragment.
   :figclass: align-center
   :width: 80%

   GhostFragment is designed as a series of nested drivers.

Briefly, the top-level driver is the :ref:`gf_fragmented_method_driver`, which
is designed to be a drop-in replacement for the supersystem calculation it is
approximating. The Fragmented Method Driver does not define how the system is
fragmented, instead it relies on a :ref:`gf_fragmented_chemical_system_driver`
to create the fragments. The Fragmented Chemical System Driver, focuses on the
``Molecule`` and ``ChemicalSystem`` abstractions, relying on a
:ref:`gf_fragmented_nuclei_driver` to handle the fragmentation of the
``Nuclei`` object.

************************
Fragmented Method Driver
************************

Full design details are at: :ref:`gf_fragmented_method_driver_design`.

The Fragmented Method Driver wraps the process of computing a property of the
input ``ChemicalSystem`` by fragmenting the system and "stitching" together
the properties of the fragments. Given a chemical system, and any additional 
inputs needed for computing the target property, the Fragmented Method Driver 
will:

1. Partition the chemical system into fragments by calling a Fragmented Chemical
   System Driver.
2. Map each fragment to one or more quantum chemistry calculations. Each
   calculation is defined by a set of input parameters.
3. Run the calculations arising from the previous step.
4. Use the results from the previous step to approximate the target property.


********************************
Fragmented ChemicalSystem Driver
********************************

The Fragmented ChemicalSystem driver wraps the process of turning a
``ChemicalSystem`` object into a ``FragmentedChemicalSystem`` object. Given a 
chemical system, the Fragmented ChemicalSystem driver will:

1. Partition the nuclei into fragments. Resulting in a ``FragmentedNuclei``
   object.
2. Assign electrons and multiplicities to each fragment. The result is a
   ``FragmentedMolecule`` object.
3. Add fields (e.g., point charges) to each fragment as needed. The result is
   a ``FragmentedChemicalSystem`` object.

- Motivation for separating ``FragmentedChemicalSystemDriver`` from
  ``FragmentedNucleiDriver``: Most methods differ in how they fragment the 
  nuclei. Thus the ``FragmentedNucleiDriver`` is more method-specific. The
  remainder of the `FragmentedChemicalSystemDriver`` is largely applicable to
  most methods.

************************
Fragmented Nuclei Driver
************************

Full design details are at: :ref:`gf_fragmented_nuclei_driver_design`.

The FragmentedNuclei driver wraps the process of turning a ``Nuclei`` object
into a ``FragmentedNuclei`` object. Given a set of nuclei, the FragmentedNuclei 
Driver will:

1. Determine the :ref:`pseudoatom`, which are the smallest, indivisible units 
   of the system for the purposes of fragmenting. 
2. Determine the connectivity of the pseduoatoms. Together the pseudoatoms and
   their connectivity define a graph representation of the system.
3. Break the graph into subgraphs. Resulting in a set of, in general, 
   non-disjoint fragments.
4. Determine the intersections of the fragments, if any.
5. Cap the broken bonds in both the fragments and the intersections. The
   result is a ``FragmentedNuclei`` object.

