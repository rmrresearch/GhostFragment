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

.. _DCLC:

###########################################
Divide and Conquer Local Correlation (DCLC)
###########################################

DCLC was developed by :cite:t:`Li2004` as an extension of the :ref:`MFCC` method 
to beyond protein-molecule interactions. The DCLC method uses the 
:ref:`DCLC_fragmentation_method` combined with the :ref:`DCLC_capping_method`.
They propose using the mean deviation of Mulliken charges as a metric for
assessing the fragment quality. Initial applications focused only on replicating
the supersystem correlation energy.