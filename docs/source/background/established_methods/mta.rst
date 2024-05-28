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
Molecular Tailoring Approach (MTA)
##################################

**********************
MTA Method Development
**********************

In the original MTA approach, :cite:t:`Gadre1994` sought a means of reducing the
cost of constructing the SCF density matrix. To do this the system of interest
was fragmented into overlapping fragments and the density matrix of each 
fragment is computed. Pieces of the fragment density matrices are then combined
to form an approximation to the supersystem's density matrix. How one should
choose the pieces for use in the supersystem density matrix is not well defined
at this point in the development of MTA. Initial results focused on zeolite and
peptides using small basis sets. Interestingly because the supersystem density
is not converged, comparisons are made against the supersystem's density matrix 
and electrostatic potential, as opposed to the usual absolute energy. 

In a follow-up study :cite:t:`Babu2003` proposed the
:ref:`mta03_fragmentation` method and with it the MTA 03 variant of MTA. Like in
the original MTA study:cite:`Gadre1994`, the density matrix of the supersystem 
is assembled from the density matrices of the fragments. Unlike, in the original 
manuscript an algorithm for doing so is provided. Applications focused on three 
systems: 5,7,8-trimethyltocol, zeolite, and a peptide using small basis SCF. 
Results primarily focused on comparing the electorstatic potential computed by
MTA to that of the supersystem.

The next development :cite:`Ganesh2006` in MTA, came from realizing the IEP 
could be used to compute the energy, and energy derivatives, of a fragmented 
system. Initial applications focused on replicating the energy of 
medium-sized organic molecules using small-basis HF, MP2, and B3LYP. Also
considered were geometry optimizations, and vibrational frequencies. This study
is also one of the earliest applications of :ref:`mta06_fragmentation` and with
it the MTA 06 variant of MTA.

.. |E_SCF_HB| replace:: :math:`E_{SCF/High}`
.. |E_MTA_MP2_HB| replace:: :math:`E_{MTA-MP2/High}`
.. |E_MP2_SB| replace:: :math:`E_{MP2/Low|}`
.. |E_MTA_MP2_SB| replace:: :math:`E_{MP2/Low|}`

For benzene clusters, :cite:t:`Mahadevi_2010` note that a 1-body MTA
expansion still neglects some many-body interactions. They suggested a screening 
method which amounts to manually adding back in two-, three-, etc. body 
interactions which do not appear in the 1-body MTA expansion. For larger
benzene clusters (hexamers, for example) these higher-body corrections can be
more than a kcal/mol. Conceptually this correction is very similar to 
:ref:`smf_screening_05`. The accompanying numerical results demonstrated that 
BSSE was quite prevelant in the benzene tetramers. Despite this fact, results 
for larger clusters did not correct for BSSE.

:cite:t:`Furtado2012` noted that up to this point in MTA development, errors 
(relative to the supersystem calcualtion) resulting from MTA tend to be basis
set independent. They also note that when applying MTA to a correlated method 
the majority of the error comes from the SCF part of the energy. On the basis
of these observations, :cite:t:`Furtado2012` propsed the "grafting" correction
to MTA. Grafting involves:

#. Compute the SCF energy of the supersystem with a large basis set, |E_SCF_HB|.
#. Using MTA compute the MP2 correlation energy with the same large basis set,
   |E_MTA_MP2_HB|.
#. Compute the MP2 energy of the supersystem with a small basis set, |E_MP2_SB|.
#. Using MTA compute the MP2 correlation energy with the same small basis set,
   |E_MTA_MP2_SB|.

The final energy is then estimated as |E_SCF_HB| plus |E_MTA_MP2_HB| plus a 
correction (the difference between |E_MP2_SB| and |E_MTA_MP2_SB|) which accounts
for the error in the fragmentation. Alternatively, one may view the energy as
|E_SCF_HB| plus |E_MP2_SB| plus a basis set correction (the difference between 
|E_MTA_MP2_HB| and |E_MTA_MP2_SB|). Either way grafting amounts to a multi-level
fragment-based method. To demonstrate grafting :cite:t:`Furtado2012` considered
MP2 energies of water clusters; compared to supersystem MP2/aug-cc-pVDZ energies
the grafting procedure resulted in errors on the order of 0.3 mH.

:cite:t:`Isegawa_2013` combined the electrostatic embedding of the EE-MB method
with the MTA. It is perhaps worth noting this MTA development is somewhat 
unconventional in that it has not been made by the Gadre group. The study 
considers how four parameters: size of fragments, fragment boundaries, type of
background charge, and type of cap atom affect the approximation. Admittedly the
description of the method is very hard to follow and it is not exactly clear 
what the final method is. It is perhaps worth noting that this study proposes 
that one can simply truncate the IEP early (they specificlly state they will 
only consider at most intersections involving two  ragments). In genernal this 
leads to unacceptable errors. For example, consider a system of four 
non-interacting hydrogen atoms. Arbitrarily labeling the atoms 0, 1, 2, and 3 we
choose to create three fragments: 012, 013, and 123. Applying the IEP:

.. math::

   E = E_{012} + E_{013} + E_{123} - E_{01} - E_{12} - E_{13} + E_{1}

The first three terms are the energies of the fragments, the next three are the
pair-wise intersections, and the last term is the one ternary intersection. Even 
with non-interacting systems we can't neglect the ternary interaction as it is 
an error of half a hartree (*i.e.*, the energy of a hydrogen atom). In the case 
of :cite:t:`Isegawa_2013`'s study, the approximation works because it's not 
actually an approximation. More specifically their fragmentation scheme is such
that the higher-order intersections always cancel out.

***********
MTA Summary
***********

Like many fragment-based methods, there is no "*the MTA method*" as the 
definition of the method has changed over the years without modifying the name. 
The following table summarizes the variants of MTA, which have appeared. Note
that the names of the variants are our names, and were not present in the
original manuscripts.

.. |Frag3| replace:: :ref:`mta03_fragmentation`
.. |Frag6| replace:: :ref:`mta06_fragmentation`
.. |Hcap| replace:: :ref:`standard_distance_capping`
.. |Sc10| replace:: :ref:`smf_screening_05`

+--------+-----------+-----------+--------+-----------+
| Name   | Fragments | Embedding | Caps   | Screening |
+========+===========+===========+========+===========+
| MTA 03 | |Frag3|   | N/A       | |Hcap| | N/A       |
+--------+-----------+-----------+--------+-----------+
| MTA 06 | |Frag6|   | N/A       | |Hcap| | N/A       |
+--------+-----------+-----------+--------+-----------+
| MTA 10 | Manual    | N/A       |  N/A   | |Sc10|    |
+--------+-----------+-----------+--------+-----------+

In this table "manual" fragmentation refers to the fact that the user specified
the fragments. Based on the presentation of MTA in the literature it is
reasonable to assume that the authors of MTA really consider the IEP to be the
key ingrediant of what distinguishes MTA from other fragment methods.

*****************
Other MTA Results
*****************

:cite:t:`Babu2004` used the MTA 03 variant of MTA (and possibly an early version
of the MTA 06 variant, but the description in the paper is too vague for me to
be certain) to approximate the density matrix of an ibuprofen crystal with the 
HF/STO-3G and HF/6-31G(d,p) levels of theory. Comparisons between the 
supersystem density matrices were made at the HF/STO-3G level of theory.

:cite:t:`Gadre2006a` provided additional details about the 
:ref:`mta06_fragmentation` procedure and saw the MTA 06 variant of MTA be 
applied to additional studies of organic molecules. Calulations used the HF 
and B3LYP methods with the 6-31G(d) and 6-31G(d, p) basis sets.
Absolute energies, gradients, optimized geometries, and molecular electorstatic
potential surfaces were compared to the supersystem results.

:cite:t:`Elango_2008` applied the MTA 06 variant of MTA to boric acid 
nanotubes and nanorings. Comparisons to B3LYP/3-21G supersystem energies and 
(partial) geometry optimizations. Additional results with CG-MTA approximated 
B3LYP and MP2 are reported (6-31+G(d,p) basis set). Of note BSSE calculations 
are foregone due to cost and an expectation that they will not change the 
results.

:cite:t:`JovanJoseK.2008` considered optimized structures of lithium clusters
using small basis DFT. Results for larger clusters relied on the MTA 06 variant
of MTA (disclaimer it is possible that the fragments were manually defined,
but it is not clear from the presentation). Several properties were computed for 
each cluster including: the adiabatic ionization potential (which is notable as 
it requires computing the energy of the cationic cluster) and the 
polarizability.

:cite:t:`Rahalkar2008` used the MTA 06 variant of MTA to computatethe Hessian 
matrix at the HF, B3LYP, and MP2 levels of theory (with small basis sets). 
Errors in computed vibrational frequencies were less than a wavenumber.

:cite:t:`Jose2009` used the MTA 06 variant of MTA to study CO2 clusters with
DFT. Optimized geometries and vibrational frequencies were considered. For
vibrational frequencies, CG-MTA matched supersystem calculations to within about
a wavenumber.

:cite:t:`Yeole_2010` applied MTA to conjugated :math:`\pi` systems with small
basis DFT and MP2. Single point energies, gradients, and optimized geometries
were computed and compared to the results of the respective full calculation.
Overall the results were promising as long as relatively large fragments were 
used (fragments had radii of 6+ Angstroms).

:cite:t:`Rahalkar2010` paired the MTA 06 variant of MTA with small basis 
IMS-MP2 and IMS-RI-MP2 (AFAIK IMS is a disk-based MP2 algoritm in the GAMESS 
package). Comparisons of MTA energies to FMO energies were also presented. 
Overall the comparison shows that three-body FMO performs about as well as 
MTA, although it is noted that the error in the FMO results tends to increase 
with basis set size.

:cite:t:`Yeole2012` applied MTA (exactly which variant is unclear, possibly MTA 
10, without screening) to CO2 clusters with the focus of finding local minima. 
MTA was used to approximate single point energies and gradients at the MP2/CBS 
level of theory (extrapolations of MP2/aDZ and MP2/aTZ). No comparisons to full 
system calculations were presented, instead comparisons were made to previously 
published results that leveraged a Lennard-Jones potential.

:cite:t:`Rahalkar2012a` is conceptually similar to :cite:`Yeole2012` except that
instead of CO2 clusters the focus was on acetylene clusters.

:cite:t:`RAHALKAR2012` used the density matrix from the MTA 06 variant of MTA to
build a Fock matrix. Subsequent diagonalization of the Fock matrix yielded MOs.
The study uses relatively small fragments and in turn the results are a mixed
bag. Some HOMO-LUMO gaps are modeled well, others aren't. Of note they consider
several conjugated systems.

:cite:t:`Sahu2013` applied the grafted MTA procedure to additional clusters. Of
note they also introduced the idea of an R-goodness for two-, three-, body
interactions. The manuscript suggests that these higher-body R-goodness 
parameters could be used to influence the fragmentation procedure; however, a
clear description of how to do this is not provided.

***********
MTA Reviews
***********

:cite:t:`Gadre_2010` reviewed applications of MTA geometry optimization, 
frequency calculations, as well as property computations to clusters.

:cite:t:`Rahalkar2011` reviewed the MTA method up to that point. The 
presentation primarily distinguishes MTA from other methods by pointing out that
MTA is capable of geometry optimizations and that MTA has been applied to large
systems. Also of note this review gives a nice explanation of the MTA 06 
fragmentation method. 

:cite:t:`Gadre2014` is a review primarily focusing on understanding the
structure of molecular clusters (from both the experimental and theoeritcal 
perspective); however, there is a bit of disucssion of how fragment-based 
methods, including MTA, have been used to study the problem. 

:cite:t:`Sahu_2014` review MTA primarily in light of its applications to
predicting minima of molecular clusters.