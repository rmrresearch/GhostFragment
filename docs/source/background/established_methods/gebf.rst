#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

.. |Frag7| replace:: :ref:`gebf07_fragmentation_method`
.. |Frag8| replace:: :ref:`gebf08_fragmentation_method`
.. |Frag10| replace:: :ref:`gebf10_fragmentation_method`
.. |Frag12| replace:: :ref:`gebf12_fragmentation_method`
.. |Frag14| replace:: :ref:`_gebf14_fragmenation_method`
.. |ItrPC| replace:: :ref:`iterative_point_charge_embedding`
.. |PC|    replace:: :ref:`ee_mb_b`
.. |stdH|  replace:: :ref:`standard_distance_capping`
.. |smf06| replace:: :ref:`smf06_screening`

GEBF is the culmanation of the :ref:`DCLC` methods.

Development of GEBF was motivated by a need to treat large 
macromolecules/clusters that are charged or highly polar :cite:`Li2007`. The 
original GEBF method, which we term the GEBF07 method, consists of the |Frag7|, 
with |stdH| capping, a slight variation of |smf06|, and an |ItrPC|. GEBF's 
original presentation also includes an energy equation which is simply a one-
body GMBE corrected for the 
self-interaction of the point charges (*i.e.*, it is assumed that the energies
of the fragments include not only the interaction of the fragment with the point
charges, but also the interactions among the point charges). Initial 
applications of GEBF focused on peptides and water clusters with the HF and MP2 
methods. In addition to absolute energies this study also considered dipole 
moments and static polarizabilities.

:cite:t:`Hua_2008` introduced the GEBF08 method which differs from the GEBF07
method in nearly all regards. In particular GEBF08 uses the |Frag8| 
fragmentation method, |ItrPC| (I assume since the GEBF07 method is cited, but 
the article is not clear on this point), |stdH| capping, and no (?) screening. 
GEBF08 was applied to geometry optimizations and
vibrational frequency calculations. The GEBF08 energies, optimized geometries,
and vibrational frequencies were compared to the conventional results. Small
basis SCF (both HF and DFT) results, for several types of systems (clusters, 
peptides, and hydrogelators) are presented.

The next methodologic development came when :cite:t:`Hua2010` updated the
fragmentation method of the GEBF08 method. The resulting GEBF10 method uses the
|Frag10| fragmentation method which is similar to the original |Frag7| method
with a series of "extension rules". GEBF10 was applied to a series of large
organic molecules. Computed properties included absolute energies, relative
energies, and optimized geometries all with small basis HF or DFT. Compared to
the supersystem results GEB10 did well for geometries, but the errors in the 
energetics were often off by more than 1 kcal/mol. 

:cite:t:`Hua2012` noted that the GEBF10 method performed poorly for systems
containing important non-covalent interactions. To combat this, 
:cite:t:`Hua2012` introduced a new fragmentation method |Frag12|. |Frag12|
extends |Frag10| by augmenting the original set of fragments with additional
fragments formed from pairs of pseudoatoms (plus the pseudoatoms near that
pair). The resulting GEBF12 method was then applied to several peptides and
large molecules. GEBF12 performed better than GEBF10 (for example for binding
energies of the large molecules GEBF10 erred from supersystem results by about 
3.8 kcal/mol whereas GEBF10 only erred by about 0.5 kcal/mol). Of note the role
of BSSE corrections (as computed using the :ref:`distance_based_cp` correction)
was also considered.

In looking at explicitly correlated CCSD(T) energies of water clusters,
:cite:t:`Wang2014` introduced the GEBF14 method. GEBF14 differs from GEBF10 in
the fragmentation method, more specifically GEBF14 uses |Frag14| which is 
essentially |Frag8| combined with |Frag10|. By only applying GEBF to the
correlation energy, :cite:t:`Wang2014` were able to replicate supersystem
explicitly correlated MP2/CBS results to within about 0.3 kcal/mol (errors 
when GEBF was also applied to the SCF component of the energy were about 
1 kcal/mol). The authors attributed the better performance of only applying 
GEBF to the correlation energy to a better treatment of BSSE. 

************
GEBF Summary
************

+--------+-----------+-----------+--------+-----------+
| Name   | Fragments | Embedding | Caps   | Screening |
+========+===========+===========+========+===========+
| GEBF07 | |Frag7|   | |ItrPC|   | |stdH| | |smf06|   |
+--------+-----------+-----------+--------+-----------+
| GEBF08 | |Frag8|   | |ItrPC|   | |stdH| | N/A       |
+--------+-----------+-----------+--------+-----------+ 
| GEBF10 | |Frag10|  | |ItrPC|   | |stdH| | N/A       |
+--------+-----------+-----------+--------+-----------+
| GEBF11 | Manual    | |ItrPC|   | |stdH| | N/A       |
+--------+-----------+-----------+--------+-----------+
| GEBF12 | |Frag12|  | |ItrPC|   | |stdH| | N/A       |
+--------+-----------+-----------+--------+-----------+
| GEBF14 | |Frag14|  | |ItrPC|   | |stdH| | N/A       |
+--------+-----------+-----------+--------+-----------+

Like other fragment-based methods, many of the studies which employ GEBF simply
refer to it as "GEBF" or "GEBF-XXX" where "XXX" is a method such as HF, MP2, or
DFT. As the table above shows there isn't just a GEBF method, but several
varieties of method. We suspect that the authors of the GEBF
method feel that any fragment-method which relies on the GEBF energy equations
is GEBF, *i.e.*, it is the energy equation which determines whether a method is
GEBF or not. However, the GEBF energy equation is nothing more than the
inclusion-exclusion principle (accounting for the self-interaction of the
point charges), so such a definition would mean CG-MTA, or any other overlapping
fragment-based method should also be labeled as GEBF. 

******************
Other GEBF Results
******************

:cite:t:`Li2008a` used GEBF07 with manually specified fragments (it's not 
immediately clear if the embedding was iterative) as the QM part of a QM/MM 
calcualtion. This method was applied to solvated polyethylene.

:cite:t:`Dong2009` uses a GEBF08 approximation to B3LYP (with van der Waals 
correctiosn) to model aromatic oglioamides. Of note this study included the 
:ref:`distance_based_cp` BSSE corrections which were found to be a good 
approximation to full counterpoise corrections.

:cite:t:`Yang_2010` applied GEBF08 to water clusters containing 20 to 30 water
molecules in order to search for low energy geometries. Results using B3LYP
and MP2 were optimized and corrected for ZPVE. Some comparison with supersystem 
results was presented (errors were around 1 kcal/mol), but the majority of 
conclusions relied on fragment-based methods alone.

:cite:t:`Jiang2011` applied GEBF11 (GEBF10 with user-defined fragments) to 
computing 
vibrational circular dichromism spectra at the DFT level of theory. The authors
report that the VCD spectra were in good agreement with supersystem spectra as
well as experimental.

:cite:t:`Hua_2011` applied GEB07 (presumably; the paper is not clear on the
exact details and instead presents references) to poly-alanine systems
containing up to 40 residues. Optimized structures, energies, and enthalpies
were computed using DFT (B3LYP and M06-2X). Errors in GEBF approximated
energies, relative to supersystem results, were about 2 kcal/mol; errors were
only computed for systems with 10 alanines.

:cite:t:`Yang_2011` looked at water clusters trapped in MOF pores using QM/MM. 
Two types of clusters were considered: neutral and protonated. The QM region of
the neutral cluster was too big for a conentional B3LYP calculation so the
authors relied on GEBF (presumably either GEBF07 or GEBF10). The geometries
were optimized using QM/MM and the cluster geometries agreed well with 
experiment. No comparison of GEBF to supersystem calculations was presented. 

:cite:t:`Li2013` applied GEBF10 to methanol disolved in water. Methanol 
dissolved in clusters containing up to 1115 water molecules were considered. To
reach the large cluster size an ONIOM was utilized where the highest level of
theory was GEBF approximated MP2-F12/aDZ, the middle layer was GEBF approximated
MP2/aDZ, and the lowest level was DFTB (presumably with no GEBF approximation).
As part of the calibration supersystem MP2-F12/aDZ results for a cluster with
12 water molecules were computed and compared to the GEBF approximated results;
errors were less than 1 kcal/mol. Of note this study also used the 
:ref:`distance_based_cp` method.

:cite:t:`Fang_2014` applied GEBF14 to periodic systems. In their approach, the
lattice energy of the unit cell is estimated by performing GEBF on all fragments
in a super cell that have at least one pseudoatom within the unit cell. the
supercell is then embedded in an infinite field of point charges which gives
rise to an Ewald term. There is then discussion of a compensation field to
correct for truncating the infinite field into a finite field; I admittedly am
unclear if this is in addition to the Ewald term or a replacement for it. Either
way the resulting method is calibrated for phase II ice against periodic 
BL3LYp/6-31G*. With the compensation field, and 5 waters per fragment, GEBF
matches the supersystem result to within 1 mH. :cite:t:`Fang_2014` then go on
to compute the lattice constants for 10 molecular crystals using either 
CCSD(T)-F12/aTZ or MP2-F12/aTZ plus a CCSD(T)/aDZ correction (depending on the 
size of the molecules). The GEBF-approximated lattice energies agree with 
experiment to within 6 kJ/mol.

************
GEBF Reviews
************

:cite:t:`Li2008` provides a brief introduction to fragment-based methods 
primarily focusing on GEBF (including its earlier incarnations).

:cite:t:`Li2014` reviewed the progress of GEBF to date. New results presented 
here included an analysis of the gradients for a hydrogelator with and without 
neglect of the response terms (results were at the HF/6-31G* level of theory) 
and ab initio molecular dynamic simulations of alanine peptides (using the
M06-2X/STO-3G level of theory). 