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
.. |muI0| replace:: :math:`\mathbf{I_0}`
.. |muI1| replace:: :math:`\mathbf{I_1}`
.. |muJ0| replace:: :math:`\mathbf{J_0}`
.. |muJ1| replace:: :math:`\mathbf{J_1}`
.. |rIJ| replace:: :math:`\mathbf{r_{IJ}}`
.. |EIi| replace:: :math:`E_I\left(\mathbf{i}\right)`
.. |EJj| replace:: :math:`E_J\left(\mathbf{j}\right)`
.. |EIij| replace:: :math:`E_I\left(\mathbf{ij}\right)`
.. |EJij| replace:: :math:`E_J\left(\mathbf{ij}\right)`
.. |EIJij| replace:: :math:`E_{IJ}\left(\mathbf{ij}\right)`
.. |dEIJij| replace:: :math:`\Delta E_{IJ}\left(\mathbf{ij}\right)`

To get a more intuitive feel for BSSE let's look at the role an incomplete basis
plays in a many-body interaction in three-dimensional Cartesian space. Following
usual conventions we label the basis functions as |i|, |j|, and |k|. For the
purposes of this page we will be looking at the interactions of static dipole
moments. For two dipole moments, :math:`\mathbf{\mu_i}` and
:math:`\mathbf{\mu_j}`, which are separated by :math:`\mathbf{r_{ij}}` the
interaction :math:`V(\mathbf{\mu_i}, \mathbf{\mu_j})` is given by:

.. math::
   \newcommand{\dipi}{\mathbf{\mu_i}}
   \newcommand{\dipj}{\mathbf{\mu_j}}
   \newcommand{\rij}{\mathbf{r_{ij}}}

   V\left(\dipi, \dipj\right)
     = \frac{1}{4\pi\epsilon_0 r_{ij}^3}\left[\dipi\cdot\dipj -
         3\frac{\left(\dipi\cdot\rij\right)\left(\rij\cdot\dipj\right)}
               {r_{ij}^2}
       \right]

If we have more than two dipoles the total interaction is expressible as the
sum of the pairwise interactions, *i.e.*, there are no three-body terms.

Dimer Case
==========

We start our analysis by considering the interaction of two rigid systems, |I|
and |J|, both of which are taken to contain two static dipole moments. We opt to
have two dipole moments in each system, so that the systems have non-zero energy
when infinitely far apart. We label the :math:`n`-th dipole moment in system
:math:`N` as :math:`\mathbf{N_n}` and we define the distance between the
origin of |I| and the origin of |J| as |rIJ|.

BSSE arises in the traditional dimer computation because we use smaller basis
sets for the monomer calculations than the dimer. To that end we opt to
expand |I|'s internal dipole moments using only |i| and |J|'s internal dipole
moments using only |j|. By analogy to the traditional dimer computation we will
use the union of the bases, denoted |ij|, to compute the interaction of |I| with
|J|. The total energy of |I| in the |i| basis, |EIi|, is given by:

.. math::

   \newcommand{\dip}[3]{\mathbf{{#1}_{#2}}\left({#3}\right)}
   \newcommand{\vi}{\boldsymbol{i}}
   \newcommand{\dipI}[2]{\dip{I}{#1}{#2}}
   \newcommand{\vI}[1]{V\left(\dipI{0}{#1}, \dipI{1}{#1}\right)}
   \newcommand{\eI}[1]{E_I\left({#1}\right)} 	

   \eI{\vi} = \vI{\vi}


Similarly the energy of |J| in the |j| basis, |EJj|, is given by:

.. math::
   \newcommand{\vj}{\boldsymbol{j}}
   \newcommand{\dipJ}[2]{\dip{J}{#1}{#2}}
   \newcommand{\vJ}[1]{V\left(\dipJ{0}{#1}, \dipJ{1}{#1}\right)}
   \newcommand{\eJ}[1]{E_J\left({#1}\right)} 	

   \eJ{\vj} = \vJ{\vj}


At a separation |rIJ| the energy of the dimer, |IJ|, in the union of the |i| and
|j| bases, |EIJij|, is given by:

.. math::
   \newcommand{\vij}{\boldsymbol{ij}}
   \newcommand{\eIJ}[1]{E_{IJ}\left({#1}\right)}
   \newcommand{\dipJp}[2]{\dip{J'}{#1}{#2}}
   \newcommand{\vIJ}[2]{V\left(\dipI{#1}{\vij}, \dipJp{#2}{\vij}\right)}
   \newcommand{\deIJ}[1]{\Delta E_{IJ}\left(#1\right)}	

   \eIJ{\vij} =& \vI{\vij} + \vJ{\vij} + \left[\vIJ{0}{0} + \right.\\
               & \left.\vIJ{0}{1} + \vIJ{1}{0} + \vIJ{1}{1}\right]\\
              =& \eI{\vij} + \eJ{\vij} + \deIJ{\vij}

where the prime indicates that the dipoles in |J| have been shifted by |rIJ|.

If we wanted to compute the two-body interaction of |I| with |J| in the |ij| 
basis set, |dEIJij|, via a supersystem approach we need to do:

.. math::

   \deIJ{\vij} = \eIJ{\vij} - \eI{\vij} - \eJ{\vij}
   
however, if we do the naive thing and subtract out |EIi| and |EJj| (instead of 
|EIij| and |EJij|) we get:


.. math::
   \newcommand{\bsse}[3]{\theta_{#1}\left(#2, #3\right)}
   \newcommand{\bsseI}[2]{\bsse{I}{#1}{#2}}
   \newcommand{\bsseJ}[2]{\bsse{J}{#1}{#2}}

   \eIJ{\vij} - \eI{\vi} -\eJ{\vj} =& \deIJ{\vij} + \left[\eI{\vij} - 
                                      \eI{\vi}\right] + \left[\eJ{\vij}-\eJ{\vj}\right]\\
                                   =& \deIJ{\vij} + \bsseI{\vij}{\vi} + \bsseJ{\vij}{\vj}  
          
