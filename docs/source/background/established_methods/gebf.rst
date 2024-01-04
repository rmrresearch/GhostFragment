#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

.. |Frag7| replace:: :ref:`gebf07_fragmentation_method`
.. |Frag8| replace:: :ref:`gebf08_fragmentation_method`
.. |Frag10| replace:: :ref:`gebf10_fragmentation_method`
.. |Frag12| replace:: :ref:`gebf12_fragmentation_method`
.. |Frag14| replace:: :ref:`gebf14_fragmenation_method`
.. |Frag19| replace:: :ref:`gebf19_fragmentation_method`
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

In looking at host/guest complexes, :cite:t:`Li_2019` realized that GEBF14
often resulted in one fragment which contained all of, or most of, the 
pseudoatoms (presumably because of ties in pseudoatom distances?). Regardless,
to avoid this, :cite:t:`Li_2019` introduced |Frag19|. GEBF19 was applied to 10
systems from the S30L database (TODO: cite). At the M06-2X/def2-TZVP level of 
theory, GEBF19 was able to reproduce supersystem binding energies to better than 
1 kcal/mol; however, more careful analysis showed that this was a result of
error cancellation.

************
GEBF Summary
************

.. note::
    
    We need to verify that all of the embedding methods are truly the same. In
    particular I think some of the methods only do one iteration where others
    iterate to consistency every time. Another variation is in how the charges
    are computed, namely are they taken from a specific fragment, supersystem
    calculation, or some other way. 

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
| GEBF19 | |Frag19|  | |ItrPC|   | |stdH| | N/A       |
+--------+-----------+-----------+--------+-----------+

We suspect that originally the authors of the GEBF method felt that any 
fragment-method which relied on the GEBF energy equations is GEBF, *i.e.*, it is
the energy equation which determines whether a method is GEBF or not. However, 
the GEBF energy equation is nothing more than the inclusion-exclusion principle 
(accounting for the self-interaction of the point charges), so such a definition
would mean CG-MTA, or any other overlapping fragment-based method, should also 
be labeled as GEBF. Things get harrier, when you consider later studies like
that of :cite:t:`Yuan_2016` or :cite:t:`Li_2019`, which note that the GEBF 
energy equations are the IEP.

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

:cite:t:`Li_2014` describes the Linear Scaling Quantum Chemistry (LSQC) program.
LSQC is a program capable of running GEBF calculations and CIM calculations by
leveraging existing quantum chemistry packages. For GEBF calculations, LSQC can
leverage Gaussian and Molpro. For CIM, LSQC relies on a locally modified version
of GAMESS. Also presented were GEBF-M06-2X/6-31G* optimized structures and IR
spectra, GEBF-MP2/6-31G* optimized structures, and a scaling plot of 
GEBF-MP2/6-31G*.

:cite:t:`Liu_2014` modeled the conformation dynamics of three-station molecular
shuttles with DFT. To determine which DFT was most suitable, reference MP2 
binding energies were computed using the GEBF method. 

:cite:t:`Fang_2016` extended periodic GEBF14 calculations to include IR and
Raman spectra. Comparisons to conventional periodic DFT (PBE0-D2/6-311G(d,p))
on imidazole and CO2 demonstrated that PBC-GEBF could faithfully approximate
conventional supersystem calculations. For urea and ammonia borane crystals,
PBC-GEBF calculations at the MP2/6-311++G(d,p) level of theory were compared to
experiment. Discrepency between PBC-GEBF and experiment was worse, but the
results still overall match well.

:cite:t:`Zhang_2016` presented AIMD simulations of polypetides using GEBF11.
Simulations were performed at several levels of theory. Initial Comparisons
of energy differences for the polypetides showed a fairly large descrepancy
across the methods considered, notably GEBF-M06-2X/6-31G differed from
conventional M06-2X by about 10 kcal/mol. DFTB differed by almost 100 kcal/mol.
It was noted that GEBF approximated SCF/STO-3G and M06-2X/STO-3G simulations had
large energy drift (presumably because the gradients were too inaccurate 
from neglegting response terms).

:cite:t:`Li_2016` extended GEBF to excited states (specifically the GEBF14 
flavor). In these calculations, the excitations were assumed localized to a set
of pseudoatoms. Fragments containing the active pseudoatoms were treated with
an excited state method. Fragments without active pseudoatoms are treated with
the ground state method. For a conjugated aldehyde, comparison of 
GEBF-:math:`\omega`\ B97XD to conventional TD-DFT results (for the 6-31G, 
6-311G(d,p), 6-311++G(d,p), and cc-pVTZ bases) showed errors less than 0.1 eV.
Solvatochromatic shifts of acetone in solvent (solvents of water, methanol,
acetonitrile, and carbon tetrachloride) computed with GEBF-:math:`\omega`\ B97XD
match experiment to about 0.1 eV. A similar analysis of pyridine and uracil in
water again showed GEBF-:math:`\omega`\ B97XD could match supersystem results
well.

:cite:t:`Yuan_2016` compares GEBF14 to the EE-MB method. The discussion focuses
on absolute energies of water clusters using M06-2X, HF, and MP2 (and several
basis sets). Consistent with Bettens (TODO: cite Bettens BSSE), the study finds
that the EE-MB method converges poorly (likely because of BSSE). One notable 
example is M06-2X/6-311++G** for clusters with 20 waters; here the maximum 
unsigned error exceeds 11 mH and does not seem to have converged by an 8-body 
MBE. EE-MB is also shown to have a fairly large sensitivity to the level of
theory. Interestingly, using loose n-mer screening rectifies these problems
somewhat.The study goes on to demonstrate that GEBF14 does not suffer from these
problems, and that using supersystem basis sets with GEBF14 does not appreciably
change the result. The authors attribute this to a BSSE cancellation effect
stemming from the IEP nature of GEBF.

:cite:t:`Tao_2016` used the GEBF14 approximated 
:math:`\omega`\ B97XD/6-311++G(d,p) model to analyze the properties of water
clusters containing 50 molecules. The study was primarily interested in
characterizing the different types of hydrogen bonds which are present and
explaining how the types of hydrogen bonds affect the freezing of water.

:cite:t:`Liu_2016` uses GEBF approximated M06-2X/6-31G(d) for computing the
energies and gradients needed for AIMD. The study looked at pseudorotaxane and
compared AIMD results to classical MD results. 

:cite:t:`Li_2017` used PBC-GEBF to optimize molecular crystal geometries for a
QM/MM calculation. Once the geometries were optimized QM/MM calculations were
run to compute excited states. The QM region contained dimers or trimers of 
and MM charges were taken from the PBC-GEBF calculation. 

:cite:t:`Wang_2017` undertook a joint experimental/theory study on crystals
of DNA bases. PBC-GEBF-PBE(D3B3)/6-311+G(d,p) was used to optimized the crystal
structures and to compute the IR vibrational spectra. Geometries and spectra
were compared to experiment and matched well.

:cite:t:`Zhang_2017` used GEBF14 and PBC-GBEF14 to establish benchmark 
energetics for water clusters containing 144 and 64 waters, respectively.
Benchmarks relied on the CCSD(T)-F12b/cc-pVDZ-F12 model. Relative energies and
binding energies are computed. The remainder of the study compares the 
performance of several flavors of DFT against the benchmarks.

:cite:t:`Yuan_2017` used GEBF14 to compute benchmark energetics for water 
clusters involving 32 and 64 water molecules. The benchmarks presente are
relative energies of different isomers, computed with the GEBF-CCSD(T)/CBS model. 
Calibration was done by comparing to supersystem MP2/cc-pVTZ results. For water 
32, restricting fragments to at most 6 waters resulted in unsigned errors of 
1.2 kcal/mol; this decreases to 0.2 kcal/mol if fragments may contain 8 waters.
For water 64, restricting to 8 waters resulted in mean unsigned errors of 1.4
kcal/mol; this reduces to 0.4 kcal/mol if the maximum is raised to 10 waters.
The remainder of the study considered how various density functional theory
approaches performed compared to the GEBF-CCSD(T)/CBS results.

:cite:t:`Zhao_2017` applied GEBF14 to NMR shifts. Considered a number of systems
including a Trp-cage mini protein, CH3CN solvated in CHCl3, a oligoamide beta
sheet, and a supramolecular aggregate. The GEBF approximated NMR shifts are
compared with both supersystem results and experiment. Overall, the predicted
NMR shifts match well, with errors typically less than 1 ppm.

:cite:t:`Li_2018` applied GEBF14 to ionic liquids. Of particular note the
authors found that choosing neutral pseudoatoms (one cation and one anion
per pseudoatom) led to better results than simply letting each cation/anion be
a pseudoatom. GEBF based on one ion per pseudoatom fragments sometimes erred by
more than 20 kcal/mol! Also computed relative energies, optimized geometries,
IR spectra, and thermodynamic values. The authors considered the effect of
ensuring the same fragments throughout the optimization (as opposed to picking
the closest ion pairs in each step) and somewhat surprisingly found that this
had little affect on the geometry and spectra, but could lead to large errors
in the thermodynamic values.

:cite:t:`Yuan_2018` applied GEBF14 to supramolecular coordination complexes. In
doing so they stipulated that pseudoatom creation should avoid breaking metal-
ligand bonds. GEBF approximated DFT energies, relative energies, optimized
geometries, IR spectra, and NMR chermical shifts are compared to supersystem
calculations and found to match well. On this basis, GEBF approximated IR and
NMR spectra are then used to help assign experimental peaks.

:cite:t:`Fu_2019` applied GEBF14 and PBC-GEBF14 to studying the excited state
spectra of uracil. To this end GEBF14 was combined with QM/MM. The study looked
aqueous, amorphous, and crystalline uracil. GEBF approximated excited state
energies were computed using TD-:math:`\omega`\ B97X-D/6-311++G(d,p) and 
compared to experiment. For aqueous and crystalline uracil peak maximums were 
off by 10 nm. 

:cite:t:`Zhao_2020` introduced a variant of the PBC-GEBF method. More 
specifically, up to this point PBC-GEBF had been done on crystals formed from
small molecules. As such pseudoatoms were taken to be entire molecules. The
new "fragment-based" variant allowed the molecules in the crystal to be broken
into multiple pseudoatoms. The new method was applied to a series of systems
and with various flavors of DFT. Compared to experimental NMR parameters, both
flavors performed well.

:cite:t:`Li_2022` applied PBC-GEBF14 to ionic crystals. The study proposed two
mechanisms for forming pseudoatoms: one ion per pseudoatom or pairs of ions (one
cation and one anion). The results establish that defining pseudoatoms using
pairs of ions leads to much better resutls. The resulting methodology is then
used to predict optimized geometries, IR spectra, Raman spectra, and NMR
shifts. PBC-GEBF results are compared to experiment and conventional periodic
DFT. Generally speaking good agreement between PBC-GEBF and the benchmarks is
seen. 

:cite:t:`Hong_2023` updated the equations used for the gradients of PBC-GEBF to
use fractional coordinates instead of combinatorial coordinates. The revamped
gradients are compared directly to analytic gradients from conventional periodic
DFT calculations. The gradients are then used for geometry optimization (results
are compared to both conventional calculations and experiment). Finally IR
spectra are computed.

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

:cite:t:`Fang_2017` reviewed the progress of PBC-GEBF and presented new
comparisons to both periodic supersystem calculations as well as experiment.
Results provided included optimized geometries, lattice energies, vibrational
frequency shifts, and Raman spectra. Most results were obtained with the M06-2X
functional and/or MP2. Generally speaking agreement between PBC-GEBF and the
supersystem or experiment were good.

:cite:t:`Li_2020` was a follow up review to :cite:t:`Li2014`. In this review
advancements since the 2014 review were summarized. In particular, the 
PBC variant of GEBF and properties thereof. The majority of the review focuses
on select calculations from various types of systems including: ionic liquids,
molecular crystals, coordination compounds, and host-guest systems.