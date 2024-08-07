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

###########################
tests/ghostfragment/testing
###########################

This directory contains infrastructure for validating GhostFragment. All
functions are defined in the ``testing`` namespace. For convenient reference we
collect the unit testing functions here.

**********************
Basic Input Generation
**********************

These functions generate "supersystem" quantities and are typically used as
inputs to traditional methods or to the modules which create fragmented
quantities.

#. ``type::ao_basis_set sto3g(const type::nuclei_set&)``

   - Function is defined in ``sto3g.hpp``
   - Contains a function which will generate the STO-3G basis set for the
     provided molecule (only knows a limited number of parameters)'
   - Unit tested in ``sto3g.cpp``

#. ``type::nuclei_set water(std::size_t)``

   - Function is defined in ``water.hpp``
   - Will generate a water "cluster" of the specified size (0 is an acceptable
     size).
   - The "cluster" is just the specified number of water molecules in a line
     along the Z-axis (and is thus not suitable for real simulations of water)
   - Unit tested in ``water.cpp``

#. ``simde::type::connectivity_table water_connectivity(std::size_t)``

   - Function is defined in ``connectivity.hpp``
   - Returns the connectivity table for water clusters generated via
     the ``water`` function.
   - Unit tested in ``connectivity.hpp``

***************************
Fragmented Input Generation
***************************

These functions help generate fragmented inputs (fragments, n-mers, caps, etc.).

#. ``type::fragmented_molecule fragmented_water(std::size_t)``

   - Defined in ``fragment.hpp``
   - Fragments a water cluster generated by the ``water`` function so that there
     is one water molecule per fragment.
   - Unit tested in ``fragment.cpp``

#. ``type::fragmented_molecule fragmented_water_needing_caps(std::size_t)``

   - Defined in ``fragment.hpp``
   - Fragments water cluster generated by the ``water`` function so that the
     oxygen and first hydrogen atoms are in one fragment and the second hydrogen
     atom is in another fragment.
   - Unit tested in ``fragment.cpp``

#. ``Caps caps_for_water(std::size_t N)``

   - Defined in ``caps.hpp``
   - Returns the full set of caps needed to cap a water cluster fragmented with
     a call to ``fragmented_water(N)``
   - Unit tested in ``caps.cpp``

#. ``pt::CappedFragmentsTraits::result_type capped_water(std::size_t N)``

   - Defined in ``caps.hpp``
   - Returns the map from fragments to caps for a water cluster of size ``N``
   - Unit tested in ``caps.cpp``

#. ``Caps caps_for_water_needing_caps(std::size_t N)``

   - Defined in ``caps.hpp``
   - Returns the caps needed for a water cluster fragmented with a call to
     ``fragmented_water_needing_caps(N)``
   - Unit tested in ``caps.cpp``

#. ``capped_water_needing_caps(std::size_t N)``

   - Defined in ``caps.hpp``
   - Returns the map from fragments to caps for a water cluster fragmented with
     ``fragmented_water_needing_caps(N)``
   - Unit tested in ``caps.cpp``

#. ``atom_to_ao(type::nuclei_set)``

   - Defined in ``aos.hpp``
   - Determines the AO basis set for the incoming set of nuclei and then creates
     a map from atom index to AO center.
   - Unit tested in ``aos.cpp``
