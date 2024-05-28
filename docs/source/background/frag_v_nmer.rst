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

########################################
Difference between fragments and n-mers?
########################################

.. |n| replace:: :math:`n`

There is a lot of terminology pertaining to the subsystems, *i.e.* monomers,
fragments, overlaps, |n|-mers, etc. At the same time, there is also the
realization that all of the methods boil down to running a series of
computations and then combining those results to approximate the results of
the target system. Natural questions then are: "Do we even need to discern
among these terms?", "Can we just ignore the origin of the subystems and treat
them in a unified manner?"

**************
The Hypothesis
**************

TODO: citations

Given a set of subsystems, we can use the inclusion-exclusion principle to 
determine the additional overlaps, and the weights of those overlaps, needed
to approximate the supersystem property. Notably, it does not matter if the
provided subsystems are:

- disjoint fragments,
- non-disjoint fragments,
- |n|-mers formed from disjoint fragments,
- |n|-mers formed from non-disjoint fragments,
- a mix of non-disjoint fragments and their overlaps,
- a mix of |n|-mers formed from disjoint fragments and the overlaps of 
  those |n|-mers, or
- a mix of |n|-mers formed from non-disjoint fragments and the overlaps of
  those |n|-mers.

***********************
Practical Distincitions
***********************

- Atoms in fragments are usually spatially close together
- n-mers may have spatially distant atoms
 