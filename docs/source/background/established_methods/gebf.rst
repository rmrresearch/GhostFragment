#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

.. |Frag7| replace:: :ref:`gebf07 fragmentation method`
.. |ItrPC| replace:: :ref:`iterative point charge embedding`
.. |stdH|  replace:: :ref:`standard distance`
.. |smf06| replace:: :ref:`smf06 screening`

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

************
GEBF Summary
************

+--------+-----------+-----------+--------+-----------+
| Name   | Fragments | Embedding | Caps   | Screening |
+========+===========+===========+========+===========+
| GEBF07 | |Frag7|   | |ItrPC|   | |stdH| | |smf06|   |
+--------+-----------+-----------+--------+-----------+

******************
Other GEBF Results
******************