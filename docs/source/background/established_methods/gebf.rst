#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

.. |Frag7| replace:: :ref:`gebf07_fragmentation_method`
.. |Frag8| replace:: :ref:`gebf08_fragmentation_method`
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
fragmentation method, non-iterative point charge embedding (|PC|), |stdH|
capping, and no (?) screening. GEBF08 was applied to geometry optimizations and
vibrational frequency calculations. The GEBF08 energies, optimized geometries,
and vibrational frequencies were compared to the conventional results. Small
basis SCF (both HF and DFT) results, for several types of systems (clusters, 
peptides, and hydrogelators) are presented.

************
GEBF Summary
************

+--------+-----------+-----------+--------+-----------+
| Name   | Fragments | Embedding | Caps   | Screening |
+========+===========+===========+========+===========+
| GEBF07 | |Frag7|   | |ItrPC|   | |stdH| | |smf06|   |
+--------+-----------+-----------+--------+-----------+
| GEBF08 | |Frag8|   | |PC|      | |stdH| | ???       |
+--------+-----------+-----------+--------+-----------+ 

******************
Other GEBF Results
******************

:cite:t:`Li2008a` used GEBF07 (with manually specified fragments) 
as the QM part of a QM/MM calcualtion. This method was applied to
solvated polyethylene.

:cite:t:`Dong2009` uses a GEBF08 approximation to B3LYP (with van der Waals 
correctiosn) to model aromatic oglioamides. Of note this study included the 
:ref:`distance_based_cp` BSSE corrections.

************
GEBF Reviews
************

:cite:t:`Li2008` provides a brief introduction to fragment-based methods 
primarily focusing on GEBF (including its earlier incarnations).