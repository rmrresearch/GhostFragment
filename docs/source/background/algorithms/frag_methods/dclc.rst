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

.. _DCLC_fragmentation_method:

#########################################################
Divide and Conquer Local Correlation Fragmentation Method
#########################################################

.. |P| replace:: :math:`P`

:cite:t:`Li2004` presented the DCLC fragmentation method. Using our terminology
this method works by:

#. Form pseudoatoms
#. Establish pseudoatom connectivity
#. For each pseudoatom |P|, create a fragment which is comprised of |P| and
   the pseudoatoms bonded to |P|. 

The original manuscript also derives a corresponding energy equation; however, the
equation is just a 1-body GMBE which uses the fact that intersections are at
most pairwise.