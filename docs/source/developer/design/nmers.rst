.. _gf_interaction_class_design:

################################
Designing the Interactions Class
################################

.. |n| replace:: :math:`n`

*******************
What is an |n|-mer?
*******************

If we think of each fragment as a set of atoms, then an |n|-mer, simply put
is the set of atoms which results from taking the union of |n| fragments. The
``NMers`` class is envisioned as being a container which holds the |n|-mers.

************************
Why do we need |n|-mers?
************************

Fragments usually consist of spatially local atoms. Simply summing the energies
of the fragments would neglect the many-body interactions and would be a poor
approximation. To better approximate the energy we need to account for the
significant many-body interactions. One way to do this is through the so-called
supermolecular method, namely to compute the |n|-body interaction of |n|
fragments one takes the union of the |n| fragments, computes the energy, and
then subtracts out the energies of the fragments, the two-body interactions,
the three-body interactions, ..., and the :math:`(n-1)`-body interactions.
Thus we need |n|-mers to compute |n|-body interactions via the supermolecular
method.

**************************
NMers Class Considerations
**************************

.. _n_frags:

Fragments.
   The entire concept of an |n|-mer is predicated on the existence of the
   fragments. Depending on the application of the |n|-mers, we may need to
   record which fragments formed the |n|-mer. 

.. _screening:

Screening.
   If we always wanted to iterate over the entire set of |n|-mers we could
   use a generator (or something similar) to create the |n|-mers as needed,
   *i.e.*, there would be no need to store the fragments. In practice, the
   reason we need the NMers class is because we only want to store the
   |n|-mers which passed screening. Screening based on energy (or distance)
   requires us to have capped |n|-mers.

