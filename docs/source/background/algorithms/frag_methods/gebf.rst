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

##########################
GEBF Fragmentation Methods
##########################

.. |zeta| replace:: :math:`\zeta`
.. |i| replace:: :math:`i`
.. |eta| replace:: :math:`\eta`
.. |etam1| replace:: :math:`\left(\eta -1\right)`

.. _gebf07_fragmentation_method:

***************************
GEBF07 Fragmentation Method
***************************

With the original GEBF fragmentation method, :cite:t:`Li2007` presented a
fragmentation method. Using our terminology, this method is to:

#. Define pseudoatoms

   - In the orignal presentation no general criteria was specified; however, it
     is assumed that for molecular clusters pseudoatoms are individual 
     molecules.

#. For each pseudoatom, define a fragment which is the pseudoatom and all
   pseudoatoms close to it.

   - The original method uses two criteria for "close", one for covalent systems
     and one for molecular clusters.
   - For covalent systems two pseudoatoms are close if they are bonded either
     covalentally or with a hydrogen bond
   - For clusters pseudoatoms within some distance |zeta| are considered close
     (default is 3 Angstroms)

#. Remove fragments which are subsets of other fragments

#. Determine intersections

Of note an algorithm for assigning multiplicities to intersections was also
presented namely:

- Assume largest fragment contains :math:`n` pseudoatoms.
- Look for a set of :math:`n-1` pseudoatoms which appears in more than one
  fragment. The multiplicity of this intersection is :math:`1-k`, where :math`k`
  is the number of fragments it appears in.
- Repeat the previous step for sets of :math`n-2, n-3, \ldots, 1` pseudoatoms 

.. _gebf08_fragmentation_method:

***************************
GEBF08 Fragmentation Method
***************************

:cite:t:`Hua_2008` introduced a new fragmentation method for the GEBF method:

1. Define |eta|, the maximum number of pseudoatoms in a fragment.
2. Form pseudoatoms.
3. For each pseudoatom combine it with the |etam1| closest pseudoatoms to form
   a fragment.

.. _gebf10_fragmentation_method:

***************************
GEBF10 Fragmentation Method
***************************

.. |Pi| replace:: :math:`P_i`
.. |Pj| replace:: :math:`P_j`
.. |Fi| replace:: :math:`F_i`
.. |Fj| replace:: :math:`F_j`

:cite:t:`Hua2010` introduced a new fragmention method for the GEBF method. The
first steps are just the GEBF07 method (minus the distinction between molecular
clusters and covalent systems):

#. Define a distance threshold |zeta|
#. Determine pseudoatoms, the |i|-th pseudoatom is denoted |Pi|
#. The |i|-th fragment, |Fi|, include |Pi| and all pseudoatoms within |zeta| of
   it.

The remainder of the algorithm amounts to "extension rules" which extend the
fragments:

4. For each fragment check for incomplete rings. If the fragment contains an
   incomplete ring, complete it by adding the pseudoatoms spanning the rest
   of the ring. If the resulting structure still has incomplete rings repeat
   this step one more time. Do not repeat the step beyond the second time.
#. For each fragment consider pseudoatoms with dangling bonds. Say |Pi| has 
   dangling bonds, then if |Pi| contains three or more heavy atoms, or if |Pi| 
   was added by the previous step ignore it. If |Pi| was not ignored then add to
   the fragment each pseudoatom bonded to |Pi|. If |Pi| contains only 1 heavy 
   atom then for each pseudoatom bonded to |Pi|, |Pj|, additionaly add the
   pseudoatoms bonded to |Pj|.

At this point caps are added (:cite:t:`Hua2010` use 
:ref:`standard_distance_capping`).

.. _gebf12_fragmentation_method:

***************************
GEBF12 Fragmentation Method
***************************

:cite:t:`Hua2012` built on the GEBF10 Fragmentation method to create the GEBF12
fragmentation method.

#. Create fragments subject to the :ref:`gebf10_fragmentation_method`.
#. Find the pairs of pseudoatoms, |Pi| and |Pj|, separated by a distance less
   than :math:`2\zeta`.
#. For each pair from step 2, determine if a pair from step 1 contains the
   pair, if not create a new fragment which contains the |Pi| and |Pj| and
   all other pseudoatoms which are within |zeta| of the geometric center of
   |Pi| and |Pj|.
#. Apply extension rules (see :ref:`gebf10_fragmentation_method`) to each 
   fragment formed in step 3. 

.. _gebf14_fragmenation_method:

***************************
GEBF14 Fragmentation Method
***************************

:cite:t:`Wang2014` combined the GEBF08 and GEBF12 fragmenation methods to create
the GEBF14 method. In their presentation, :cite:t:`Wang2014` did not discuss the
extension rules; however, because the application was water clusters, the
extension rules were not relevant. For clarity the GEBF14 procedure is:

#. Define a distance threshold |zeta|
#. Define a maximum number of pseudoatoms |eta|.
#. Determine pseudoatoms, the |i|-th pseudoatom is denoted |Pi|
#. The |i|-th fragment, |Fi|, include |Pi| and all pseudoatoms within |zeta| of
   it. If more than |eta| pseudoatoms fall within a radius of |zeta| only the
   |eta| closest to |Pi| are included.
#. Presumably extension rules are applied here.
#. Find the pairs of pseudoatoms, |Pi| and |Pj|, separated by a distance less
   than :math:`2\zeta`.
#. For each pair from step 2, determine if a pair from step 1 contains the
   pair, if not create a new fragment which contains the |Pi| and |Pj| and
   all other pseudoatoms which are within |zeta| of the geometric center of
   |Pi| and |Pj|. If more than |eta| pseudoatoms fall within a radius of |zeta| 
   only the |eta| closest to the geometric center of |Pi| and |Pj| are included.
#. Apply extension rules (see :ref:`gebf10_fragmentation_method`) to each 
   fragment formed in step 3. 

.. _gebf19_fragmentation_method:

***************************
GEBF19 Fragmentation Method
***************************

:cite:t:`Li_2019` proposed a new fragmentation method designed to produce
smaller fragments then GEBF14 when applied to host/guest complexes.

#. Define a distance threshold |zeta|
#. Define a mximum number of pseudoatoms |eta|.
#. Determine pseudoatoms, the |i|-th pseudoatom is denoted |Pi|.
#. For |Pi| form a fragment, |Fi|, which contains |Pi| and all pseudoatoms that
   are within |zeta| of |Pi|. |Pi| is considered colored in |Fi|.
#. For each fragment |Fi| with more pseudoatoms than |eta|, create new fragments
   for each un-colored pseudoatom |Pj| in |Fi|. The fragment resulting from
   |Pj| is |Fj| and includes |Pj|, the colored pseudoatoms, and the un-colored
   pseudoatoms in |Fi| which are within |zeta| of |Pj|. |Pj| is considered c
   olored in |Fj|. Discard |Fi|.
#. Repeat the previous step until no fragments contain more pseudoatoms than
   |eta| or all pseudoatoms have been colored.
