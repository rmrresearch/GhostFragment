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

##################################
Systematic Molecular Fragmentation
##################################

SMF was introduced by :cite:t:`Deev2005` as a generalization of MFCC. At its 
core, SMF introduces a fragmentation method, and a capping method. Initial
applications focused on hydrocarbons, using a relatively wide assortment of 
levels of theory. Absolute energies, energy barriers, bond-lengths, bond angles,
and vibrational frequencies were computed and compared to the supersystem 
counterparts.

In a follow-up paper :cite:t:`Collins2006` presented the original SMF Algorithm
in more detail. New this time were the :ref:`ring_repair_variation` and an 
approximate treatment of the non-bonded interactions between distant fragments. 
To test the new SMF algorithm, structures were taken from the Cambridge 
Structural Database. Compared to the initial study the resulting molecules were 
chemically more diverse. Absolute energies and isomerazation eneriges were 
computed and compared to the respective supersystem values. Results used the SCF
and MP2 methods combined with small and medium size basis sets.