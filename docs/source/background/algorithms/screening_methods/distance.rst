###################################
Distance Based Screening Procedures
###################################

.. |I| replace:: :math:`I`
.. |J| replace:: :math:`J`

Weak interactions die off quickly with respect to the separation distance 
between the interacting units. Perhaps unsurprisingly a number of groups have
proposed screening methods which are distance based.


***************
FMO00 Screening
***************

The orginal FMO procedure :cite:t:`Nakano_2000` for screening dimers involved 
distance cutoffs. If the shortest inter-atom distance between two monomers |I| 
and |J| is less than a threshold (default is 10 Bohr), then the dimer energy is
approximated by:

.. math::
   \newcommand{\vr}{\vec{r}}
   \newcommand{\vrp}{\vec{r}'}
   \newcommand{\density}[2]{rho_{#1}\left(#2\right)}

   E_{IJ} = E_{I} + E_{J} -
            \int d\vr\int\vrp \frac{\density{I}{\vr}\density{J}{\vrp}}
                               {\mid \vr -\vrp\mid}

***************
FMO04 Screening
***************

In the original formulation of three-body FMO :cite:t:`Fedorov_2004a`, the FMO00
screening procedure is extended to three-body terms. Instead of one shortest
inter-atomic distance we now have three, one for each pair of monomers. The 
FMO04 screening method screens out a trimer if the **second** smallest distance 
is greater than a threshold (default is 2.0, in units of van der Waal radii).

***************
SMF06 Screening
***************

.. |d| replace:: :math:`d`
.. |fij| replace:: :math:`f_{ij}`

:cite:t:`Collins2006` introduced a screening method which relies on a distance
cut-off, |d|, to separate the dimers into two groups. Defining |fij| to be the
shortest atom-atom distance between an atom in fragment :math:`i` and an atom in
fragment :math:`j`, the first group of dimers are those for which |fij| is less 
than or equal to |d|. The dimers in the first group are treated normally. The
dimers in the second group are those for which |fij| is greater than |d|. The
interactions of the dimers in the second group are approximated with a multipole
expansion. Based on the preliminary test set, :cite:t:`Collins2006` recommend a
value of |d| around 3 Angstroms. Conceptually this is just the FMO00 Screening
method with a multipole expansion.

The screening method introduced by :cite:t:`Li2007` is a variation on this which
truncates the multipole expansion at point charges. Li et al. recommended a
value of |d| of 10 Angstroms.