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


.. _distance_based_cp:

#################
Distance-Based CP
#################

.. |i| replace:: :math:`i`
.. |Ei| replace:: :math:`E_i`
.. |Eip| replace:: :math:`E_i'`
.. |EBsse| replace:: :math:`E_{BSSE}`

:cite:t:`Dong2009` proposed a simple procedure for computing BSSE corrections of
fragment-based methods:

1. Compute the energy of each fragment. Let |Ei| be the energy of the |i|-th
   fragment.
2. For each fragment create a new system which is the fragment plus any ghost
   atoms within some threshold (:cite:`Dong2009` suggested 4 Angstroms). Let
   |Eip| be the energy of the |i|-th fragment plus the included ghost atoms.
3. Compute a BSSE correction to |Ei| as |Eip| minus |Ei|.

.. note::
   :cite:t:`Dong2009` Suggest only including 50% of the BSSE correction.
