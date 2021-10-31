#############
GMBE Notation
#############

.. |m| replace:: :math:`m`
.. |I| replace:: :math:`I`
.. |monomers| replace:: :math:`\mathbb{F}^{\left(m,1\right)}`
.. |monomer_i| replace:: :math:`F^{\left(1\right)}_{I}`

Concise equations for the GMBE require specifying the relations among a variety
of sets. To that end, we assume that the system has been fragmented into |m|
initial pieces. These initial pieces are termed fragments, or more
systematically monomers. We assume that these |m| monomers are part of an
ordered set, we choose to denote the ordered set as: |monomers|, and denote the
|I|-th monomer in |monomers| as |monomer_i|.

.. |dimers| replace:: :math:`\mathbb{F}^{\left(m,2\right)}`
.. |dimer_i| replace:: :math:`F^{\left(2\right)}_{I}`
.. |mC2| replace:: :math:`{_m}C_{2}`
.. |n| replace:: :math:`n`
.. |nmers| replace:: :math:`\mathbb{F}^{\left(m,n\right)}`
.. |mCn| replace:: :math:`{_m}C_{n}`
.. |nmer_i| replace:: :math:`F^{\left(n\right)}_{I}`

Next we define dimers by taking pair-wise unions of monomers. There are |mC2|
(*i.e.*, "|m| choose 2") unique pairs of monomers which comprise the elements of
an ordered set |dimers|. Analogous to the monomers, we denote the |I|-th dimer
in |dimers| as |dimer_i|. This notation readily generalizes and we have that
|nmers| is the ordered set consisting of the |mCn| |n|-mers (an |n|-mer being
the union of |n| monomers) and the |I|-th |n|-mer in |nmers| is denoted as
|nmer_i|.

.. |nmers_1_I| replace:: :math:`\mathbb{F}^{\left(m,n\right)}[1:I]`

In its most general form, the GMBE will rely on contiguous partitionings of the
various |n|-mer sets. We denote the subset of |nmers| consisting of the first
|I| |n|-mers as |nmers_1_I|.

.. |k| replace:: :math:`k`
.. |sets| replace:: :math:`\mathbb{S}`
.. |powersets| replace:: :math:`\mathbb{P}\left(\mathbb{S}\right)`
.. |powersetsk| replace:: :math:`\mathbb{P}^{\left(k\right)}\left(\mathbb{S}\right)`

Given a set |sets|, the powerset of |sets| (the set of all combinations that can
be formed from |sets|), is denoted as |powersets|. Of more interest to us 
presently are the subsets of |powersets| which result from taking all 
combinations involving |k| elements of |sets|, which we denote as |powersetsk|.
Finally we define the short-hand notation for the intersection of all elements
in |sets|:

.. math::

   \bigcap \mathbb{S} \equiv \bigcap_{s\in \mathbb{S}} s  