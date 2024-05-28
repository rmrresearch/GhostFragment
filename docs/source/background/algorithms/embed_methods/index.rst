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
Embedding Algorithms
####################

By breaking the system into fragments we neglect interactions among the 
fragments. We can build these interactions back in  by considering higher-order 
truncations of the (G)MBE. Alternatively, we can *ad hoc* try to account for the 
missing interactions. This is where embedding methods come in. Embedding methods
"embed" the fragment (or in general :math:`n`-mer) in a low-level description of
the rest of the system.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   density
   point_charge
