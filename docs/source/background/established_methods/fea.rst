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

.. _fea:

###############################
Fragment Energy Assembler (FEA)
###############################

.. |fea_frag| replace:: :ref:`fea_frag_method`
.. |dclc_cap| replace:: :ref:`DCLC_capping_method`

As a follow up to the EC-MFCC method, :cite:t:`Li2005b` proposed the FEA
approach. This approach uses |fea_frag| combined with hydrogen
caps (excatly which capping algorithm is used is not stated; we assume it is
the |dclc_cap| method like prior work from this group). 

An interesting aspect of :cite:t:`Li2005b` is how the energy associated with the
FEA is actually computed. Since the fragments in the FEA method intersect, a
normal MBE is not strictly possible. However, the FEA method uses a modified
form of the usual SCF equations so that the MBE is still applicable. More 
specifically, the densities of the fragments, dimers,
etc. are computed as normal; however, when the densities are used to compute
the energy, the summations are restricted to AOs and nuclei in the pseudoatom 
which generated the fragment. 

+-------------------+-------------+---------------+------------+---------------+
| Name              | Fragments   | Embedding     | Caps       | Screening     |
+===================+=============+===============+============+===============+
| FEA               | |fea_frag|  | N/A           | |dclc_cap| | N/A           |
+-------------------+-------------+---------------+------------+---------------+