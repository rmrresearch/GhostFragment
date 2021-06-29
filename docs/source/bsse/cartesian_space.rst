***********************
BSSE in Cartesian Space
***********************

.. |i| replace:: :math:`\mathbf{i}`
.. |j| replace:: :math:`\mathbf{j}`
.. |ij| replace:: :math:`\mathbf{ij}`
.. |k| replace:: :math:`\mathbf{k}`
.. |I| replace:: :math:`I`
.. |J| replace:: :math:`J`
.. |IJ| replace:: :math:`I\cup J`
.. |muI0| replace:: :math:`\mathbf{\mu^I_0}`
.. |muI1| replace:: :math:`\mathbf{\mu^I_1}`
.. |muJ0| replace:: :math:`\mathbf{\mu^J_0}`
.. |muJ1| replace:: :math:`\mathbf{\mu^J_1}`
.. |rIJ| replace:: :math:`\mathbf{r_{IJ}}`
.. |EIi| replace:: :math:`E_I\left(\mathbf{i}\right)`
.. |EJj| replace:: :math:`E_J\left(\mathbf{j}\right)`
.. |EIJij| replace:: :math:`E_{IJ}\left(\mathbf{ij}\right)`

To get a more intuitive feel for BSSE let's look at the role an incomplete basis
plays in a many-body interaction in three-dimensional Cartesian space. Following
usual conventions we label the basis functions as |i|, |j|, and |k|.

As a concrete example consider two rigid systems, |I|, and |J|, both of which
contain two static dipole moments. We opt to have two dipole moments in each
system, so that the systems have non-zero energy when infinitely far apart. We
label the dipole moments in |I| as |muI0| and |muI1|; and label the dipole
moments in |J| as |muJ0| and |muJ1|. We define the distance between |I| and |J|
as |R| and the interaction between dipole moments :math:`\mu_i` and
:math:`\mu_j` as :math:`V(\mu_1, \mu_2)`, which is given by:

.. math::
   \newcommand{\dipi}{\mathbf{\mu_i}}
   \newcommand{\dipj}{\mathbf{\mu_j}}
   \newcommand{\rij}{\mathbf{r_{ij}}}

   V\left(\dipi, \dipj\right)
     = \frac{1}{4\pi\epsilon_0 r_{ij}^3}\left[\dipi\cdot\dipj -
         3\frac{\left(\dipi\cdot\rij\right)\left(\rij\cdot\dipj\right)}{r_{ij}^2}
       \right]

BSSE arises in the traditional dimer computation because we use smaller basis
sets for the monomer calculations than the dimer. To that end we opt to
expand |I|'s internal dipole moments using only |i| and |J|'s internal dipole
moments using only |j|. Again, by analogy to the dimer computation we use the
union of the bases to compute the interaction of |I| with |J|. To that end we
define the projection of dipole :math:`\vec{\mu}^K_n` onto basis function
:math:`\vec{q}` as: :math:`\vec{\mu}^K_n\left(\vec{q}\right)` which is given by:

.. math::
   \newcommand{\dip}[3]{\vec{\mu}^{#1}_{#2}\left(#3\right)}

   \dip{K}{n}{\vec{q}} = \left(\vec{\mu}^K_n\dot\vec{q}\right)\vec{q}.

The total energy of |I| in the |i| basis, |EIi|, is given by:

.. math::
   \newcommand{\vi}{\vec{i}}
   \newccomand{\eI}[1]{E_I\left(#1\right)}
   \newcommand{\dipI}[2]{\dip{I}{#1}{#2}}
   \newcommand{\vI}[1]{V\left(\dipI{0}{#1}, \dipI{1}{#1}\right)}

   \eI{\vi} = \vI{\vi}


Similarly the energy of |J| in the |j| basis, |EJj|, is given by:

.. math::
   \newcommand{\vj}{\vec{j}}
   \newcommand{\eJ}[1]{E_J\left(#1\right)}
   \dipJ[2]{\dip{J}{#1}{#2}}
   \newcommand{\vJ}[1]{V\left(\dipJ{0}{#1}, \dipJ{1}{#1}\right)}

   \eJ{\vj} = \vJ{\vj}


At a separation |R| the energy of the dimer, |IJ|, in the union of the |i| and
|j| bases, |EIJij|, is given by:

.. math::
   \newcommand{\eIJ}{E_{IJ}\left(\vi, \vj\right)}
   \newcommand{\dipJp}[2]{\left[\vec{\mu}}'\right]^{J}_{#1}\left(#2\right)}
   \newcommand{\vIJ}[2]{V\left(\dipI{#1}{\vi,\vj}, \dipJp{#2}{\vi,\vj}\right)}

   \eIJ = \vI{\vi,\vj} + \vJ{\vi,vj} + \vIJ{0}{0} + \vIJ{0}{1}+\vIJ{1}{0} +
          \vIJ{1}{1}

where the prime indicates that the dipoles in |J| have been shifted by |R|.
