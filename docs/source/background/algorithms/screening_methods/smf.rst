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

####################
SMF Screening Method
####################

.. |d| replace:: :math:`d`
.. |fij| replace:: :math:`f_{ij}`
.. |F| replace:: :math:`\mathbb{F}`
.. |Fp| replace:: :math:`\mathbb{F}'`
.. |Fi| replace:: :math:`f_i`
.. |Fj| replace:: :math:`f_j`

.. _smf_screening_05:

****************
SMF Screening 05
****************

SMF as introduced by :cite:t:`Deev2005` can be thought of as a one-body GMBE.
In turn, there are interactions which are neglected by this expansion. Letting
|F| be the set of fragments used for the one-body expansion. "cite:t:`Deev2005`
suggest creating an auxiliary set of fragments |Fp|, such that if |Fi| and |Fj| 
are disjoint fragments in |Fp|, then their union, |fij|, must not appear in any 
fragment in |F|. Given such an |Fp|, then subtracting the energies of |Fi| and 
|Fj| from the energy of |fij| yields a two-body correction. 

In their arcticle :cite:t:`Deev2005` specifically stated that |Fp| should be
created by editing the fragments which result from a level one 
:ref:`smf_fragmentation_05` fragmentation method. The editing process is what
ensures the fragments in |Fp| are disjoint and that their union does not appear
in |F|. The exact editing process appears to be somewhat ad hoc.

