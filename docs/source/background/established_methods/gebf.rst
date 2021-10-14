#############################################
Generalized Energy Based Fragmentation (GEBF)
#############################################

Development of GEBF was motivated by a need to treat large 
macromolecules/clusters that are charged or highly polar :cite:`Li2007`. The 
original GEBF method consists of a fragmentation method, a screening method, and
an embedding method. GEBF's original presentation also includes an energy 
equation which is simply a one-body GMBE corrected for the self-interaction of
the point charges (*i.e.*, it is assumed that the energies of the fragments
include not only the interaction of the fragment with the point charges, but
also the interactions among the point charges). Initial applications of GEBF
focused on peptides and water clusters with the HF and MP2 methods. In addition
to absolute energies this study also considered dipole moments and static
polarizabilities.