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

.. |X| replace:: :math:`X`
.. |Y| replace:: :math:`Y`
.. |I| replace:: :math:`I`
.. |J| replace:: :math:`J`
.. |K| replace:: :math:`K`
.. |A| replace:: :math:`\mathcal{A}`
.. |S| replace:: :math:`\mathcal{S}`
.. |S2| replace:: :math:`\mathcal{S}^2`
.. |PS| replace:: :math:`\mathcal{P}\left(\mathcal{S}^1\right)`
.. |PkS| replace:: :math:`\mathcal{P}^k\left(\mathcal{S}^1\right)`
.. |m| replace:: :math:`m`
.. |k| replace:: :math:`k`

The starting point for VMFC is the assumption that we have a set of atoms, |A|,
which has been partitioned in to |m| non-empty, disjoint sets. The partitions
are called "fragments" and we define |S| to be the set of fragments. 
Traditionally, the |m| fragments are labeled :math:`I,J,K,\cdots,m`. We define 
:math:`E_{X}\left(Y\right)` as the energy of system |X| computed using the 
molecular basis set for system |Y| where |X| and |Y| will be subsets of the
power set of |S|.

********************
Single Fragment Case
********************

If there is a single fragment the total energy of the system is simply the
energy of the fragment. Labeling the fragment |I|, the total energy of the
system is :math:`E_I\left(I\right)` and the BSSE-free energy of the system is
given by:

.. math::
   \newcommand{\egy}[2]{E_{#1}\left(#2\right)}
   \newcommand{\begy}[1]{\epsilon_{#1}}

   \begy{I} = \egy{I}{I}

*****************
Two Fragment Case
*****************

.. |EIJ_IJ| replace:: :math:`E_{IJ}\left(IJ\right)`
.. |EI_IJ| replace:: :math:`E_{I}\left(IJ\right)`
.. |EJ_IJ| replace:: :math:`E_{J}\left(IJ\right)`
.. |deIJ_IJ| replace:: :math:`\Delta E_{IJ}\left(IJ\right)`
.. |deIJ| replace:: :math:`\Delta E_{IJ}`

The dimer |IJ| has total energy |EIJ_IJ|. In the dimer basis set, monomer |I|
has energy |EI_IJ| and monomer |J| has energy |EJ_IJ|. The BSSE-free two-body
interaction energy of dimer |IJ|, computed using the dimer basis set is 
then given by:

.. math::

   \newcommand{\dbegy}[1]{\Delta\begy{#1}}

   \dbegy{IJ} = \egy{IJ}{IJ} - \egy{I}{IJ} - \egy{J}{IJ}

Computing the interaction energy such that the energy of |I| is computed in
the basis set of |I|, and similarly for |J|, yields:

.. math::

   \newcommand{\degy}[1]{\Delta E_{#1}}

   \degy{IJ} = \egy{IJ}{IJ} - \begy{I} -\begy{J}


The difference in energy yields the BSSE,

.. math::
   
   \newcommand{\bsse}[2]{\theta_{#1}\left(#2\right)}
   \newcommand{\dbsse}[2]{\Delta\bsse{#1}{#2}}

   \dbsse{IJ}{IJ} \equiv
   \degy{IJ} - \dbegy{IJ} &=  \bsse{I}{IJ} + \bsse{J}{IJ}\\
                     \bsse{I}{IJ}   &\equiv \egy{I}{IJ} - \begy{I}\\
                     \bsse{J}{IJ}   &\equiv \egy{J}{IJ} - \begy{J}

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
