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

.. _efa_mfcc:

###########################################
Electrostatic Field Adapted MFCC (EFA-MFCC)
###########################################

.. |dclc_frag| replace:: :ref:`DCLC fragmentation<DCLC_fragmentation_method>`
.. |dclc_cap| replace:: :ref:`DCLC_capping_method`
.. |mfcc_embed| replace:: :ref:`ec_mfcc_charges`
 
In an effort to extend the DCLC and EC-MFCC methods to charged systems, 
:cite:t:`Jiang2006` introduced the electrostatic field-adapted MFCC (EFA-MFCC)
method. EFA-MFCC is DCLC with electrostatic embedding via |mfcc_embed| (N.B. 
aside from details on how the fragments are formed, the manuscript is actually a
bit sparse on the details of the EFA-MFCC method and this is our best guess as
to how the EFA-MFCC method waas implemented).  
 
+-------------------+-------------+---------------+------------+---------------+
| Name              | Fragments   | Embedding     | Caps       | Screening     |
+===================+=============+===============+============+===============+
| EFA-MFCC          | |dclc_frag| | |mfcc_embed|  | |dclc_cap| | N/A           |
+-------------------+----------------------------------------------------------+