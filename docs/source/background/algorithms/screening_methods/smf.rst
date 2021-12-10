####################
SMF Screening Method
####################

.. |d| replace:: :math:`d`
.. |fij| replace:: :math:`f_{ij}`
.. |F| replace:: :math:`\mathbb{F}`
.. |Fp| replace:: :math:`\mathbb{F}'`
.. |Fi| replace:: :math:`f_i`
.. |Fj| replace:: :math:`f_j`


****************
SMF Screening 05
****************

SMF as introduced by :cite:t:`Deev2005` can be thought of as a one-body GMBE.
In turn, there are interactions which are neglected by this expansion. Letting
|F| be the set of fragments used for the one-body expansion. "cite:t:`Deev2005`
suggest creating an auxiliary set of fragments |Fp|, such that if |Fi| and |Fj| 
are disjoint fragments in |Fp|, then their union, |fij|, must not appear in any 
fragment in |F|. Given such an |Fp|, then subtracting the energies of |Fi| and 
|Fj| from the energy of |fij| yields a two-body correction. 

In their arcticle :cite:t:`Deev2005` specifically stated that |Fp| should be
created by editing the fragments which result from a level one 
:ref:`SMF Fragmentation 05` fragmentation method. The editing process is what
ensures the fragments in |Fp| are disjoint and that their union does not appear
in |F|. The exact editing process appears to be somewhat ad hoc.

****************
SMF Screening 06
****************

:cite:t:`Collins2006` introduced a screening method which relies on a distance
cut-off, |d|, to separate the dimers into two groups. Defining |fij| to be the
shortest atom-atom distance between an atom in fragment :math:`i` and an atom in
fragment :math:`j`, the first group of dimers are those for which |fij| is less 
than or equal to |d|. The dimers in the first group are treated normally. The
dimers in the second group are those for which |fij| is greater than |d|. The
interactions of the dimers in the second group are approximated with a multipole
expansion. Based on the preliminary test set, :cite:t:`Collins2006` recommend a
value of |d| around 3 Angstroms.