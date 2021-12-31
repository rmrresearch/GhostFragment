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
:ref:`mta03 fragmentation` method and with it the MTA 03 variant of MTA. Like in
the original MTA study:cite:`Gadre1994`, the density matrix of the supersystem 
is assembled from the density matrices of the fragments. Unlike, in the original 
manuscript an algorithm for doing so is provided. Applications focused on three 
systems: 5,7,8-trimethyltocol, zeolite, and a peptide using small basis SCF. 
Results primarily focused on comparing the electorstatic potential computed by
MTA to that of the supersystem.

The next development :cite:`Ganesh2006` in MTA, led to a rebranding as CGMTA (CG
standing for cardinality guided). In this study the energy, and energy 
derivatives, of a fragmented system are computed using the inclusion-exclusion 
principle. Initial applications focused on replicating the energy of 
medium-sized organic molecules using small-basis HF, MP2, and B3LYP. Also
considered were geometry optimizations, and vibrational frequencies. This study
is also one of the earliest applications of :ref:`mta06 fragmentation` and with
it the MTA 06 variant of MTA.

.. |E_SCF_HB| replace:: :math:`E_{SCF/High}`
.. |E_MTA_MP2_HB| replace:: :math:`E_{MTA-MP2/High}`
.. |E_MP2_SB| replace:: :math:`E_{MP2/Low|}`
.. |E_MTA_MP2_SB| replace:: :math:`E_{MP2/Low|}`

For benzene clusters, :cite:t:`Mahadevi_2010` note that a 1-body CG-MTA
expansion still neglects some many-body interactions. They suggested a screening 
method which amounts to manually adding back in two-, three-, etc. body 
interactions which do not appear in the 1-body CG-MTA expansion. For larger
benzene clusters (hexamers, for example) these higher-body corrections can be
more than a kcal/mol. Conceptually this correction is very similar to 
:ref:`SMF Screening 05`. The accompanying numerical results demonstrated that 
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

***********
MTA Summary
***********

Like many fragment-based methods, *the MTA/CG-MTA method* is not a well defined
concept, as the definition of the method has changed over the years. The 
following table summarizes the variants of MTA/CG-MTA, which have appeared. Note
that the names of the variants are our names, and were not present in the
original manuscripts.

.. |Frag3| replace:: :ref:`mta03 fragmentation`
.. |Frag6| replace:: :ref:`mta06 fragmentation`
.. |Hcap| replace:: :ref:`h capping`
.. |Sc10| replace:: :ref:`SMF Screening 05`

+--------+-----------+-----------+--------+-----------+
| Name   | Fragments | Embedding | Caps   | Screening |
+========+===========+===========+========+===========+
| MTA 03 | |Frag3|   | N/A       | |Hcap| | N/A       |
+--------+-----------+-----------+--------+-----------+
| MTA 06 | |Frag6|   | N/A       | |Hcap| | N/A       |
+--------+-----------+-----------+--------+-----------+
| MTA 10 | Manual    | N/A       |  N/A   | |Sc10|    |
+--------+-----------+-----------+--------+-----------+



*****************
Other MTA Results
*****************

:cite:t:`Babu2004` used the MTA 03 variant of MTA (and possibly an early version
of the MTA 06 variant, but the description in the paper is too vague for me to
be certain) to approximate the density matrix of an ibuprofen crystal with the 
HF/STO-3G and HF/6-31G(d,p) levels of theory. Comparisons between the 
supersystem density matrices were made at the HF/STO-3G level of theory.

:cite:t:`Gadre2006a` provided additional details about the 
:ref:`mta06 fragmentation` procedure and saw the MTA 06 variant of CG-MTA be 
applied to additional studies of organic molecules. Calulations used the HF 
and B3LYP methods with the 6-31G(d) and 6-31G(d, p) basis sets.
Absolute energies, gradients, optimized geometries, and molecular electorstatic
potential surfaces were compared to the supersystem results.

:cite:t:`Elango_2008` applied the MTA 06 variant of CG-MTA to boric acid 
nanotubes and nanorings. Comparisons to B3LYP/3-21G supersystem energies and 
(partial) geometry optimizations. Additional results with CG-MTA approximated 
B3LYP and MP2 are reported (6-31+G(d,p) basis set). Of note BSSE calculations 
are foregone due to cost and an expectation that they will not change the 
results.

:cite:t:`JovanJoseK.2008` considered optimized structures of lithium clusters
using small basis DFT. Results for larger clusters relied on the MTA 06 variant
of CG-MTA (disclaimer it is possible that the fragments were manually defined,
but it is not clear from the presentation). Several properties were computed for 
each cluster including: the adiabatic ionization potential (which is notable as 
it requires computing the energy of the cationic cluster) and the 
polarizability.

:cite:t:`Rahalkar2008` used the MTA 06 variant of CG-MTA to computatethe Hessian 
matrix at the HF, B3LYP, and MP2 levels of theory (with small basis sets). 
Errors in computed vibrational frequencies were less than a wavenumber.

:cite:t:`Jose2009` used the MTA 06 variant of CG-MTA to study CO2 clusters with
DFT. Optimized geometries and vibrational frequencies were considered. For
vibrational frequencies, CG-MTA matched supersystem calculations to within about
a wavenumber.

:cite:t:`Rahalkar2010` paired the MTA 06 variant of CG-MTA with small basis 
IMS-MP2 and IMS-RI-MP2 (AFAIK IMS is a disk-based MP2 algoritm in the GAMESS 
package). Comparisons of CG-MTA energies to FMO energies were also presented. 
Overall the comparison shows that three-body FMO performs about as well as 
CG-MTA, although it is noted that the error in the FMO results tends to increase 
with basis set size.

***********
MTA Reviews
***********

:cite:t:`Gadre_2010` reviewed applications of CG-MTA geometry optimization, 
frequency calculations, as well as property computations to clusters.