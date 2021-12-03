####################
SMF Screening Method
####################

.. |d| replace:: :math:`d`
.. |fij| replace:: :math:`f_{ij}`

`:cite:t:`Collins2006` introduced a screening method which relies on a distance
cut-off, |d|, to separate the dimers into two groups. Defining |fij| to be the
shortest atom-atom distance between an atom in fragment :math:`i` and an atom in
fragment :math:`j`, the first group of dimers are those for which |fij| is less 
than or equal to |d|. The dimers in the first group are treated normally. The
dimers in the second group are those for which |fij| is greater than |d|. The
interactions of the dimers in the second group are approximated with a multipole
expansion. Based on the preliminary test set, :cite:t:`Collins2006` recommend a
value of |d| around 3 Angstroms.