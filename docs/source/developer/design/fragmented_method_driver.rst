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

.. _gf_fragmented_method_driver_design:

########################
Fragmented Method Driver
########################

*************************************
What is the Fragmented Method Driver?
*************************************

The 

***************************************
Fragmented Method Driver Considerations
***************************************

Multiple APIs
=============

**Consideration**: We will want APIs for multiple supersystem properties. Each
property will in general need different inputs and will provide different
outputs. While it will be possible to define some drivers in terms of other
drivers. Unifying all drivers into a single API will be difficult.

- ``TotalEnergy``. Takes a ``ChemicalSystem`` returns the energy.
- ``AOEnergy``. Takes a ``ChemicalSystem`` and an ``AOBasisSet`` returns the
  energy.