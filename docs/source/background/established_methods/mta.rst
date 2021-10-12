##################################
Molecular Tailoring Approach (MTA)
##################################

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
:ref:`mta03 fragmentation` method. Like in the original MTA 
study:cite:`Gadre1994`, the density matrix of the supersystem is assembled from 
the density matrices of the fragments. Unlike, in the original manuscript an
algorithm for doing so is provided. Applications focused on three systems: 
5,7,8-trimethyltocol, zeolite, and a peptide using small basis SCF. Results
primarily focused on comparing the electorstatic potential computed by MTA to
that of the supersystem.
