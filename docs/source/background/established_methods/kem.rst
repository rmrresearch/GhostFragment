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

.. _kem:

##########################
Kernel Energy Method (KEM)
##########################

.. |h_cap|  replace:: :ref:`simple_replacement`

KEM was introduced by :cite:t:`Huang2005`. The original study looks at peptides
and chooses each fragment to be one amino acid. The severed bonds are then
capped with |h_cap| capping scheme (this conclusion is based on the fact that 
the manuscript states that hydrogen atoms are added to cap the severed bonds, 
but provides no additional details). The manuscript starts by testing a 
screening method where only chemically bonded dimers are considered. Compared to
supersystem energies, this screening method results in larger errors (10s to 
100s of kcal/mol). Using larger fragments reduces the error (how the larger 
fragments  were formed is not clear), as does considering all dimers.

+-------------------+-------------+---------------+------------+---------------+
| Name              | Fragments   | Embedding     | Caps       | Screening     |
+===================+=============+===============+============+===============+
| KEM               | N/A         | N/A           | |h_cap|    | N/A           |
+-------------------+-------------+---------------+------------+---------------+