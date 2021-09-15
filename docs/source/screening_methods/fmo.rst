########################
FMO Screening Procedures
########################

.. |I| replace:: :math:`I`
.. |J| replace:: :math:`J`

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