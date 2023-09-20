#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

.. |Frag7| replace:: :ref:`gebf07_fragmentation_method`
.. |Frag8| replace:: :ref:`gebf08_fragmentation_method`
.. |Frag10| replace:: :ref:`gebf10_fragmentation_method`
.. |Frag12| replace:: :ref:`gebf12_fragmentation_method`
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

Like other fragment-based methods, many of the studies which employ GEBF simply
refer to it as "GEBF" or "GEBF-XXX" where "XXX" is a method such as HF, MP2, or
DFT. As the table above shows there isn't just a GEBF method, but several
varieties of method. We suspect that the authors of the GEBF
method feel that any fragment-method which relies on the GEBF energy equations
is GEBF, *i.e.*, it is the energy equation which determines whether a method is
GEBF or not. However, the GEBF energy equation is nothing more than the
inclusion-exclusion principle (including the self-interaction of the
point charges), so such a definition would mean CG-MTA, or any other overlapping
fragment-based method would be labeled as GEBF. 

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

************
GEBF Reviews
************

:cite:t:`Li2008` provides a brief introduction to fragment-based methods 
primarily focusing on GEBF (including its earlier incarnations).