.. Copyright 2025 GhostFragment
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

####
VMFC
####

.. |IJ| replace:: :math:`I,J`
.. |IJK| replace:: :math:`I,J,K`

Let :math:`E_{X}\left(Y\right)` denote the energy of system :math:`X` computed 
using basis set :math:`Y`. So the energy of dimer |IJ| computed with the 
trimer basis set |IJK| would be denoted  :math:`E_{I,J}\left(I,J,K\right)`.

************
Monomer Case
************

.. |I| replace:: :math:`I`
.. |EI_I| replace:: :math:`E_{I}\left(I\right)`


The monomer case is trivial. We label the fragment |I| and it has total energy
|EI_I|. There is no many-body interaction for the monomer.

**********
Dimer Case
**********

.. |J| replace:: :math:`J`
.. |EIJ_IJ| replace:: :math:`E_{I,J}\left(I,J\right)`
.. |EI_IJ| replace:: :math:`E_{I}\left(I,J\right)`
.. |EJ_IJ| replace:: :math:`E_{J}\left(I,J\right)`
.. |deIJ_IJ| replace:: :math:`\Delta E_{I,J}\left(I,J\right)`
.. |deIJ| replace:: :math:`\Delta E_{I,J}`

The dimer |IJ| has total energy |EIJ_IJ|. In the dimer basis set, monomer |I|
has energy |EI_IJ| and monomer |J| has energy |EJ_IJ|. The BSSE-free two-body
interaction of dimer |IJ| is given by:

.. math::

   \newcommand{\egy}[2]{E_{#1}\left(#2\right)}
   \newcommand{\degy}[2]{\Delta\egy{#1}{#2}}

   \degy{I,J}{I,J} = \egy{I,J}{I,J} -\egy{I}{I,J} - \egy{J}{I,J}

The BSSE-contaminated two-body interaction, |deIJ|, is given by:

.. math::

   \newcommand{\dbsseEgy}[1]{\Delta E_{#1}}

   \dbsseEgy{I,J} = \egy{I,J}{I,J} - \egy{I}{I} -\egy{J}{J}

Allowing us to define the BSSE as:

.. math::

   \dbsseEgy{I,J} - \degy{I,J}{I,J} =  
                                    &= \egy{I}{I,J} - \egy{I}{I}\\
                                    &= \egy{J}{I,J} - \egy{J}{I,J}

***********
Trimer Case
***********

.. |EIJK_IJK| replace:: :math:`E_{I,J,K}\left(I,J,K\right)`
.. |EI_IJK| replace:: :math:`E_{I}\left(I,J,K\right)`
.. |EJ_IJK| replace:: :math:`E_{J}\left(I,J,K\right)`
.. |EK_IJK| replace:: :math:`E_{K}\left(I,J,K\right)`
.. |EIJ_IJK| replace:: :math:`E_{I,J}\left(I,J,K\right)`
.. |EIK_IJK| replace:: :math:`E_{I,K}\left(I,J,K\right)`
.. |EJK_IJK| replace:: :math:`E_{J,K}\left(I,J,K\right)`
.. |deIJK_IJK| replace:: :math:`\Delta E_{I,J,K}\left(I,J,K\right)`
.. |EIJK_int| replace:: :math:`E^{\text{int}}_{I,J,K}\left(I,J,K\right)`

The trimer |IJK| has total energy |EIJK_IJK|. The BSSE-free three-body
interaction, |deIJK_IJK|, is obtained by:

.. math::

   \degy{I,J,K}{I,J,K} = \egy{I,J,K}{I,J,K} - \degy{I,J}{I,J,K} -
                         \degy{I,K}{I,J,K} - \degy{J,K}{I,J,K} -
                         \egy{I}{I,J,K} - \egy{J}{I,J,K} -\egy{K}{I,J,K}

That is, using the trimer basis set for all terms, we removed from the energy of
the trimer, the three two-body interactions, and the energies of the three
monomers. The BSSE-free two-body interactions are obtained using the dimer
formula, i.e.:

.. math:

    \degy{I,J}{I,J} &= \egy{I,J}{I,J} -\egy{I}{I,J} - \egy{J}{I,J}\\
    \degy{I,K}{I,K} &= \egy{I,K}{I,K} -\egy{I}{I,K} - \egy{K}{I,K}\\
    \degy{J,K}{J,K} &= \egy{J,K}{J,K} -\egy{J}{J,K} - \egy{K}{J,K}

Thus the total interaction energy, |EIJK_int|, is:

.. math:
   
   \newcommand{\intE}[2]{E^{\text{int}}_{#1}\left(#2\right)}
   \newcommand{\dbsse}[2]{\Delta\epsilon_{#1}\left(#2\right)}

   \intE{I,J,K}{I,J,K} =& \degy{I,J}{I,J} + \degy{I,K}{I,K} + \degy{J,K}{J,K} +
                          \degy{I,J,K}{I,J,K}\\  
                       =& \egy{I,J,K} - 
                          \left[\degy{I,J}{I,J,K} - \degy{I,J}{I,J}\right] -
                          \left[\degy{I,K}{I,J,K} - \degy{I,K}{I,K}\right] -
                          \left[\degy{J,K}{I,J,K} - \degy{J,K}{J,K}\right] -
                          \egy{I}{I,J,K} - \egy{J}{I,J,K} -\egy{K}{I,J,K}
