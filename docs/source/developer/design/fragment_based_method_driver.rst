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

.. _gf_fragment_based_method_driver_design:

############################
Fragment Based Method Driver
############################

*****************************************
What is the Fragment Based Method Driver?
*****************************************

A fragment-based method approximates a property (usually the energy) of a large 
chemical system by dividing the system into smaller subsystems (fragments), and
using the properties of those fragments to approximate the property of the full
system. The Fragmented Based Method Driver is charged with wrapping this process
for the user.

Each fragment based method Driver is assumed to consist of the same four
general steps:

1. Fragment the chemical system into smaller subsystems.
2. From the set of fragments, determine what sub-calculations must be run.
3. Run the sub-calculations.
4. Use the results of the sub-calculations to approximate the target property.

While all the drivers may have the same general steps, the details of each step
can in general vary widely. For example, :term:`BSSE`-corrected fragment based
methods will in general need to run each fragment in multiple basis sets,
whereas non-BSSE corrected methods will usually just run each fragment in its
own basis set. Similarly, fragment based methods which need to assemble
tensor properties (e.g., dipole moments, gradients, or Hessians) will need to
include extra logic to map the tensor components from the fragments to the full
system.

***************************************
Fragmented Method Driver Considerations
***************************************

Multiple Properties
===================

**Consideration**: We will want APIs for multiple supersystem properties. Each
property will in general need different inputs and will provide different
outputs. Unifying all properties into a single API will be difficult. Examples
of properties we will target include:

- ``TotalEnergy``. Takes a ``ChemicalSystem`` returns the energy.
- ``AOEnergy``. Takes a ``ChemicalSystem`` and an ``AOBasisSet`` returns the
  energy.
- Derivatives with respect to nuclear coordinates (gradients, Hessians, etc) of
  the above properties.

**Solution**: Each property will have its own Fragmented Method Driver API. To
the extent possible the implementation will rely on class and function templates
to write general code. Key steps will be modularized to allow code reuse between
different properties.

Flavors
=======

**Considerations**: The set of fragments does not alone dictate the set of
calculations that must be run. For example, if we are :term:`BSSE`-correcting, 
the property we will need the fragments to be computed in multiple basis sets.
For lack of a better term we will call the mapping from a set of fragments to a
set of calculations to run the "flavor" of the fragment-based method. Some
examples of flavors include:

- Generalized Many-Body Expansion (GMBE). This is the simplest approach where
  each fragment is computed in its own basis set and weights of the calculations
  are determined by using the inclusion-exclusion principle.
- Site-Site Functional Counterpoise (SSFC). Each fragment is computed in the
  supersystem basis set.
- Valiron-Mayer Functional Counterpoise (VMFC). Each fragment is computed in a
  every combination of basis sets, up to some truncation order.

**Solution**: This consideration is the reason that Step 2, forming an input
queue, is a PluginPlay module. By having Step 2 be a module, developers can
simply swap out flavors without having to rewrite the entire driver.

Engines
=======

**Considerations**: Different users may want to use different quantum chemistry
packages to run the calculations.

**********************************
Fragment Based Method Architecture
**********************************

.. _fig_fbm_driver_architecture:

.. figure:: assets/fragment_based_method_driver.png
   :alt: Architecture diagram of the fragment based method driver.
   :figclass: align-center
   :width: 80%

   The Fragment Based Method Driver consists of four steps. The second and
   third steps can be satisfied by a number of interchangeable modules.