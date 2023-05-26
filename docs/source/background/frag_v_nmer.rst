########################################
Difference between fragments and n-mers?
########################################

.. |n| replace:: :math:`n`

There is a lot of terminology pertaining to the subsystems, *i.e.* monomers,
fragments, overlaps, |n|-mers, etc. At the same time, there is also the
realization that all of the methods boil down to running a series of
computations and then combining those results to approximate the results of
the target system. Natural questions then are: "Do we even need to discern
among these terms?", "Can we just ignore the origin of the subystems and treat
them in a unified manner?"

**************
The Hypothesis
**************

TODO: citations

Given a set of subsystems, we can use the inclusion-exclusion principle to 
determine the additional overlaps, and the weights of those overlaps, needed
to approximate the supersystem property. Notably, it does not matter if the
provided subsystems are:

- disjoint fragments,
- non-disjoint fragments,
- |n|-mers formed from disjoint fragments,
- |n|-mers formed from non-disjoint fragments,
- a mix of non-disjoint fragments and their overlaps,
- a mix of |n|-mers formed from disjoint fragments and the overlaps of 
  those |n|-mers, or
- a mix of |n|-mers formed from non-disjoint fragments and the overlaps of
  those |n|-mers.

***********************
Practical Distincitions
***********************

- Atoms in fragments are usually spatially close together
- n-mers may have spatially distant atoms
 