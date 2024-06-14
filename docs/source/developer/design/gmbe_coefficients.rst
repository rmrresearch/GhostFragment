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

#################
GMBE Coefficients
#################

Computing the coefficients of the GMBE is in general an NP hard problem as it
requires looking at the powerset of fragments. Having an efficient algorithm for
working out the coefficients is important.

:cite:t:`Hua2010` prposed one that needs to be summarized here. 